#include "CameraManager.h"

#include "Camera.h"
#include "Mtx44.h"
#include "GlobalVariableManager.h"

void CameraManager::attach_camera(Camera * cam)
{
	this->camera = cam;
}

void CameraManager::update(double dt)
{
	if (!camera)
		return;

	camera->up.Set(0, 1, 0);
	shake_timer.update_timer(dt);

	switch (shake_type)
	{
	case LIGHT:
	case HEAVY:
	{
		float current_angle = shake_max_angle * sin(shake_timer.get_current_percent() * Math::TWO_PI);
		Mtx44 rotation;
		rotation.SetToRotation(current_angle, 0, 0, 1);
		this->camera->up = rotation * this->camera->up;
		this->camera->up.Normalize();
		break;
	}
	default:
		break;
	}
}

void CameraManager::shake_cam(SHAKE_TYPE type)
{
	//this func here inits the values
	shake_type = type;
	switch (type)
	{
	case NONE:
		shake_timer.set_duration(0.0);
		shake_timer.reset_timer();
		shake_max_angle = 0.f;
		break;
	case LIGHT:
		shake_timer.set_duration(0.1);
		shake_timer.reset_timer();
		shake_max_angle = 0.1f;
		break;
	case HEAVY:
		shake_timer.set_duration(0.1);
		shake_timer.reset_timer();
		shake_max_angle = 0.15f;
		break;
	}
}

CameraManager::CameraManager() : camera(nullptr), 
	shake_type(SHAKE_TYPE::NONE), shake_max_angle(0.f)
{
}

CameraManager::~CameraManager()
{
}
