
#ifndef APPLICATION_H
#define APPLICATION_H

#include "timer.h"
class GLFWwindow;
class Application
{
public:
	static Application& GetInstance()
	{
		static Application app;
		return app;
	}
	void Init();
	void Run();
	void Exit();
	//static bool IsKeyPressed(unsigned short key);
	//static bool IsMousePressed(unsigned short key);
	//static void GetCursorPos(double *xpos, double *ypos);
	static int GetWindowWidth();
	static int GetWindowHeight();
	void SetWindowWidth(int window_width);
	void SetWindowHeight(int window_height);

	static void MouseButtonCallbacks(GLFWwindow* window, int button, int action, int mods);
	static void MouseScrollCallbacks(GLFWwindow* window, double xoffset, double yoffset);
private:
	Application();
	~Application();

	void PostInputUpdate();
	void UpdateInput();

	//Declare a window object
	GLFWwindow* m_window;
	static int m_window_width, m_window_height;

	StopWatch m_timer;

};

#endif