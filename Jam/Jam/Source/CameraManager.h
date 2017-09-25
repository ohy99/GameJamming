#ifndef CAMERAMANAGER_H
#define CAMERAMANAGER_H

#include "SingletonTemplate.h"
#include "MyTimer.h"

class Camera;
class CameraManager : public Singleton<CameraManager>
{
	friend Singleton;
public:
	enum SHAKE_TYPE
	{
		//choco shake, milk shake, strawberry shake, banana shake
		NONE,
		LIGHT,
		HEAVY
	};
private:
	Camera* camera;

	SHAKE_TYPE shake_type;
	MyTimer shake_timer;
	float shake_max_angle;
public:
	void attach_camera(Camera* cam);
	void update(double dt);
	
	void shake_cam(SHAKE_TYPE type = SHAKE_TYPE::LIGHT);
protected:
	CameraManager();
	~CameraManager();
};


#endif // !CAMERAMANAGER_H

