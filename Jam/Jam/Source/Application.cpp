
#include "Application.h"

//Include GLEW
#include <GL/glew.h>

//Include GLFW
#include <GLFW/glfw3.h>

//Include the standard C++ headers
#include <stdio.h>
#include <stdlib.h>

#include "SceneManager.h"
#include "DetectMemoryLeak.h"

#include "GlobalVariableManager.h"
#include "MeshList.h"
#include "Graphics.h"
#include "KeyboardController.h"
#include "MouseController.h"

#include "GameScene.h"
#include "Mainmenu.h"
#include "Options.h"

struct AtExit
{
	~AtExit() { _CrtDumpMemoryLeaks(); }
} doAtExit;


int Application::m_window_width = 0;
int Application::m_window_height = 0;
const unsigned char FPS = 60; // FPS of this game
const unsigned int frameTime = 1000 / FPS; // time for each frame

//Define an error callback
void error_callback(int error, const char* description)
{
	fputs(description, stderr);
	_fgetchar();
}

//Define the key input callback
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
}


void resize_callback(GLFWwindow* window, int w, int h)
{
	glViewport(0, 0, w, h);
	Application::GetInstance().SetWindowWidth(w);
	Application::GetInstance().SetWindowHeight(h);
}

//bool Application::IsKeyPressed(unsigned short key)
//{
//    return ((GetAsyncKeyState(key) & 0x8001) != 0); //DEFAULT
//}
//bool Application::IsMousePressed(unsigned short key) //0 - Left, 1 - Right, 2 - Middle
//{
//	return glfwGetMouseButton(m_window, key) != 0;
//}
//void Application::GetCursorPos(double *xpos, double *ypos)
//{
//	glfwGetCursorPos(m_window, xpos, ypos);
//}
int Application::GetWindowWidth()
{
	return m_window_width;
}
int Application::GetWindowHeight()
{
	return m_window_height;
}

void Application::SetWindowWidth(int window_width)
{
	this->m_window_width = window_width;
}

void Application::SetWindowHeight(int window_height)
{
	this->m_window_height = window_height;
}

Application::Application()
{
}

Application::~Application()
{
}

void Application::Init()
{
	//Set the error callback
	glfwSetErrorCallback(error_callback);

	//Initialize GLFW
	if (!glfwInit())
	{
		exit(EXIT_FAILURE);
	}

	//Set the GLFW window creation hints - these are optional
	glfwWindowHint(GLFW_SAMPLES, 4); //Request 4x antialiasing
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); //Request a specific OpenGL version
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); //Request a specific OpenGL version
	//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //We don't want the old OpenGL 


	//Create a window and create its OpenGL context
	m_window_width = 800;
	m_window_height = 600;
	//m_window = glfwCreateWindow(m_width, m_height, "Physics", glfwGetPrimaryMonitor(), NULL);
	m_window = glfwCreateWindow(m_window_width, m_window_height, "The Slother", NULL, NULL);

	//If the window couldn't be created
	if (!m_window)
	{
		fprintf( stderr, "Failed to open GLFW window.\n" );
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	//This function makes the context of the specified window current on the calling thread. 
	glfwMakeContextCurrent(m_window);

	//Sets the key callback
	//glfwSetKeyCallback(m_window, key_callback);
	glfwSetWindowSizeCallback(m_window, resize_callback);
	glfwSetMouseButtonCallback(m_window, &Application::MouseButtonCallbacks);
	glfwSetScrollCallback(m_window, &Application::MouseScrollCallbacks);

	glewExperimental = true; // Needed for core profile
	//Initialize GLEW
	GLenum err = glewInit();

	//If GLEW hasn't initialized
	if (err != GLEW_OK) 
	{
		fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
		//return -1;
	}
}

void Application::Run()
{
	//Main Loop
	SceneManager* SM = SceneManager::GetInstance();
	SM->addScene("GAME", new GameScene());
	SM->addScene("MAIN", new Mainmenu());
	SM->addScene("OPTIONS", new Options());
	SM->setCurrScene("GAME");


	m_timer.startTimer();    // Start timer to calculate how long it takes to render this frame
	while (!glfwWindowShouldClose(m_window) && !KeyboardController::GetInstance()->IsKeyPressed(VK_ESCAPE)&& !SM->checkShouldExit())
	{
		glfwPollEvents();
		UpdateInput();

		SM->update(m_timer.getElapsedTime());
		//Swap buffers
		glfwSwapBuffers(m_window);
		//Get and organize events, like keyboard and mouse input, window resizing, etc...
        m_timer.waitUntil(frameTime);       // Frame rate limiter. Limits each frame to a specified time in ms.   

		PostInputUpdate();

	} //Check if the ESC key had been pressed or if the window had been closed

	SceneManager::Destroy();
}
void Application::PostInputUpdate()
{
	// If mouse is centered, need to update the center position for next frame
	if (MouseController::GetInstance()->GetKeepMouseCentered())
	{
		double mouse_currX, mouse_currY;
		mouse_currX = m_window_width >> 1;
		mouse_currY = m_window_height >> 1;
		MouseController::GetInstance()->UpdateMousePosition(mouse_currX, mouse_currY);
		glfwSetCursorPos(m_window, mouse_currX, mouse_currY);
	}

	// Call input systems to update at end of frame
	MouseController::GetInstance()->EndFrameUpdate();
	KeyboardController::GetInstance()->EndFrameUpdate();
}
void Application::UpdateInput()
{
	// Update Mouse Position
	double mouse_currX, mouse_currY;
	glfwGetCursorPos(m_window, &mouse_currX, &mouse_currY);
	MouseController::GetInstance()->UpdateMousePosition(mouse_currX, mouse_currY);

	// Update Keyboard Input
	for (int i = 0; i < KeyboardController::MAX_KEYS; ++i)
		KeyboardController::GetInstance()->UpdateKeyboardStatus(i, (GetAsyncKeyState(i) & 0x8001) != 0);
}
void Application::MouseButtonCallbacks(GLFWwindow* window, int button, int action, int mods)
{
	// Send the callback to the mouse controller to handle
	if (action == GLFW_PRESS)
		MouseController::GetInstance()->UpdateMouseButtonPressed(button);
	else
		MouseController::GetInstance()->UpdateMouseButtonReleased(button);
}

void Application::MouseScrollCallbacks(GLFWwindow* window, double xoffset, double yoffset)
{
	MouseController::GetInstance()->UpdateMouseScroll(xoffset, yoffset);
}

void Application::Exit()
{
	//Close OpenGL window and terminate GLFW
	glfwDestroyWindow(m_window);
	//Finalize and clean up GLFW
	glfwTerminate();
}
