#ifndef _GRAPHICS_
#define _GRAPHICS_

#include "MatrixStack.h"
#include "GL\glew.h"
#include "Light.h"

#include "shader.hpp"
#include "SingletonTemplate.h"

class Graphics : public Singleton<Graphics>
{
	friend Singleton;
	Graphics() {

		glGenVertexArrays(1, &m_vertexArrayID);
		glBindVertexArray(m_vertexArrayID);
	}

public:
	~Graphics()
	{
		glDeleteProgram(m_programID);
		glDeleteVertexArrays(1, &m_vertexArrayID);

	}

	void init()
	{
		m_programID = LoadShaders("Shader//comg.vertexshader", "Shader//comg.fragmentshader");

		m_parameters[U_MVP] = glGetUniformLocation(m_programID, "MVP");
		m_parameters[U_MODELVIEW] = glGetUniformLocation(m_programID, "MV");
		m_parameters[U_MODELVIEW_INVERSE_TRANSPOSE] = glGetUniformLocation(m_programID, "MV_inverse_transpose");
		m_parameters[U_MATERIAL_AMBIENT] = glGetUniformLocation(m_programID, "material.kAmbient");
		m_parameters[U_MATERIAL_DIFFUSE] = glGetUniformLocation(m_programID, "material.kDiffuse");
		m_parameters[U_MATERIAL_SPECULAR] = glGetUniformLocation(m_programID, "material.kSpecular");
		m_parameters[U_MATERIAL_SHININESS] = glGetUniformLocation(m_programID, "material.kShininess");
		m_parameters[U_LIGHTENABLED] = glGetUniformLocation(m_programID, "lightEnabled");
		m_parameters[U_NUMLIGHTS] = glGetUniformLocation(m_programID, "numLights");
		m_parameters[U_LIGHT0_TYPE] = glGetUniformLocation(m_programID, "lights[0].type");
		m_parameters[U_LIGHT0_POSITION] = glGetUniformLocation(m_programID, "lights[0].position_cameraspace");
		m_parameters[U_LIGHT0_COLOR] = glGetUniformLocation(m_programID, "lights[0].color");
		m_parameters[U_LIGHT0_POWER] = glGetUniformLocation(m_programID, "lights[0].power");
		m_parameters[U_LIGHT0_KC] = glGetUniformLocation(m_programID, "lights[0].kC");
		m_parameters[U_LIGHT0_KL] = glGetUniformLocation(m_programID, "lights[0].kL");
		m_parameters[U_LIGHT0_KQ] = glGetUniformLocation(m_programID, "lights[0].kQ");
		m_parameters[U_LIGHT0_SPOTDIRECTION] = glGetUniformLocation(m_programID, "lights[0].spotDirection");
		m_parameters[U_LIGHT0_COSCUTOFF] = glGetUniformLocation(m_programID, "lights[0].cosCutoff");
		m_parameters[U_LIGHT0_COSINNER] = glGetUniformLocation(m_programID, "lights[0].cosInner");
		m_parameters[U_LIGHT0_EXPONENT] = glGetUniformLocation(m_programID, "lights[0].exponent");
		m_parameters[U_LIGHT1_TYPE] = glGetUniformLocation(m_programID, "lights[1].type");
		m_parameters[U_LIGHT1_POSITION] = glGetUniformLocation(m_programID, "lights[1].position_cameraspace");
		m_parameters[U_LIGHT1_COLOR] = glGetUniformLocation(m_programID, "lights[1].color");
		m_parameters[U_LIGHT1_POWER] = glGetUniformLocation(m_programID, "lights[1].power");
		m_parameters[U_LIGHT1_KC] = glGetUniformLocation(m_programID, "lights[1].kC");
		m_parameters[U_LIGHT1_KL] = glGetUniformLocation(m_programID, "lights[1].kL");
		m_parameters[U_LIGHT1_KQ] = glGetUniformLocation(m_programID, "lights[1].kQ");
		m_parameters[U_LIGHT1_SPOTDIRECTION] = glGetUniformLocation(m_programID, "lights[1].spotDirection");
		m_parameters[U_LIGHT1_COSCUTOFF] = glGetUniformLocation(m_programID, "lights[1].cosCutoff");
		m_parameters[U_LIGHT1_COSINNER] = glGetUniformLocation(m_programID, "lights[1].cosInner");
		m_parameters[U_LIGHT1_EXPONENT] = glGetUniformLocation(m_programID, "lights[1].exponent");

		m_parameters[U_COLOR_TEXTURE_ENABLED] = glGetUniformLocation(m_programID, "colorTextureEnabled");
		m_parameters[U_COLOR_TEXTURE] = glGetUniformLocation(m_programID, "colorTexture");

		// Get a handle for our "textColor" uniform
		m_parameters[U_TEXT_ENABLED] = glGetUniformLocation(m_programID, "textEnabled");
		m_parameters[U_TEXT_COLOR] = glGetUniformLocation(m_programID, "textColor");

		// Use our shader
		glUseProgram(m_programID);

		lights[0].type = Light::LIGHT_DIRECTIONAL;
		lights[0].position.Set(0, 20, 0);
		lights[0].color.Set(1, 1, 1);
		lights[0].power = 1;
		lights[0].kC = 1.f;
		lights[0].kL = 0.01f;
		lights[0].kQ = 0.001f;
		lights[0].cosCutoff = cos(Math::DegreeToRadian(45));
		lights[0].cosInner = cos(Math::DegreeToRadian(30));
		lights[0].exponent = 3.f;
		lights[0].spotDirection.Set(0.f, 1.f, 0.f);

		lights[1].type = Light::LIGHT_DIRECTIONAL;
		lights[1].position.Set(1, 1, 0);
		lights[1].color.Set(1, 1, 0.5f);
		lights[1].power = 0.4f;
		//lights[1].kC = 1.f;
		//lights[1].kL = 0.01f;
		//lights[1].kQ = 0.001f;
		//lights[1].cosCutoff = cos(Math::DegreeToRadian(45));
		//lights[1].cosInner = cos(Math::DegreeToRadian(30));
		//lights[1].exponent = 3.f;
		//lights[1].spotDirection.Set(0.f, 1.f, 0.f);

		glUniform1i(m_parameters[U_NUMLIGHTS], 1);
		glUniform1i(m_parameters[U_TEXT_ENABLED], 0);

		glUniform1i(m_parameters[U_LIGHT0_TYPE], lights[0].type);
		glUniform3fv(m_parameters[U_LIGHT0_COLOR], 1, &lights[0].color.r);
		glUniform1f(m_parameters[U_LIGHT0_POWER], lights[0].power);
		glUniform1f(m_parameters[U_LIGHT0_KC], lights[0].kC);
		glUniform1f(m_parameters[U_LIGHT0_KL], lights[0].kL);
		glUniform1f(m_parameters[U_LIGHT0_KQ], lights[0].kQ);
		glUniform1f(m_parameters[U_LIGHT0_COSCUTOFF], lights[0].cosCutoff);
		glUniform1f(m_parameters[U_LIGHT0_COSINNER], lights[0].cosInner);
		glUniform1f(m_parameters[U_LIGHT0_EXPONENT], lights[0].exponent);

		glUniform1i(m_parameters[U_LIGHT1_TYPE], lights[1].type);
		glUniform3fv(m_parameters[U_LIGHT1_COLOR], 1, &lights[1].color.r);
		glUniform1f(m_parameters[U_LIGHT1_POWER], lights[1].power);
		glUniform1f(m_parameters[U_LIGHT1_KC], lights[1].kC);
		glUniform1f(m_parameters[U_LIGHT1_KL], lights[1].kL);
		glUniform1f(m_parameters[U_LIGHT1_KQ], lights[1].kQ);
		glUniform1f(m_parameters[U_LIGHT1_COSCUTOFF], lights[1].cosCutoff);
		glUniform1f(m_parameters[U_LIGHT1_COSINNER], lights[1].cosInner);
		glUniform1f(m_parameters[U_LIGHT1_EXPONENT], lights[1].exponent);
	}

	enum UNIFORM_TYPE
	{
		U_MVP = 0,
		U_MODELVIEW,
		U_MODELVIEW_INVERSE_TRANSPOSE,
		U_MATERIAL_AMBIENT,
		U_MATERIAL_DIFFUSE,
		U_MATERIAL_SPECULAR,
		U_MATERIAL_SHININESS,
		U_LIGHTENABLED,
		U_NUMLIGHTS,
		U_LIGHT0_TYPE,
		U_LIGHT0_POSITION,
		U_LIGHT0_COLOR,
		U_LIGHT0_POWER,
		U_LIGHT0_KC,
		U_LIGHT0_KL,
		U_LIGHT0_KQ,
		U_LIGHT0_SPOTDIRECTION,
		U_LIGHT0_COSCUTOFF,
		U_LIGHT0_COSINNER,
		U_LIGHT0_EXPONENT,
		U_LIGHT1_TYPE,
		U_LIGHT1_POSITION,
		U_LIGHT1_COLOR,
		U_LIGHT1_POWER,
		U_LIGHT1_KC,
		U_LIGHT1_KL,
		U_LIGHT1_KQ,
		U_LIGHT1_SPOTDIRECTION,
		U_LIGHT1_COSCUTOFF,
		U_LIGHT1_COSINNER,
		U_LIGHT1_EXPONENT,

		U_COLOR_TEXTURE_ENABLED,
		U_COLOR_TEXTURE_ENABLED1,
		U_COLOR_TEXTURE_ENABLED2,
		U_COLOR_TEXTURE_ENABLED3,
		U_COLOR_TEXTURE_ENABLED4,
		U_COLOR_TEXTURE_ENABLED5,
		U_COLOR_TEXTURE_ENABLED6,
		U_COLOR_TEXTURE_ENABLED7,

		U_COLOR_TEXTURE,
		U_COLOR_TEXTURE1,
		U_COLOR_TEXTURE2,
		U_COLOR_TEXTURE3,
		U_COLOR_TEXTURE4,
		U_COLOR_TEXTURE5,
		U_COLOR_TEXTURE6,
		U_COLOR_TEXTURE7,

		U_TEXT_ENABLED,
		U_TEXT_COLOR,
		U_TOTAL,
	};

	unsigned m_vertexArrayID;
	unsigned m_programID;
	unsigned m_parameters[U_TOTAL];

	MS modelStack;
	MS viewStack;
	MS projectionStack;

	Light lights[2];
	bool bLightEnabled = false;
};


#endif