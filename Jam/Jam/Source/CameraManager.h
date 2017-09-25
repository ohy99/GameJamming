#ifndef CAMERAMANAGER_H
#define CAMERAMANAGER_H

#include "SingletonTemplate.h"

class Camera;
class CameraManager : public Singleton<CameraManager>
{
	friend Singleton;
public:
	enum SHAKE_TYPE
	{
		//choco shake, milk shake, strawberry shake, banana shake
		LIGHT,
		HEAVY
	};
private:
	Camera* camera;
public:
	void attach_camera(Camera* cam);
	
	void shake_cam(SHAKE_TYPE type = SHAKE_TYPE::LIGHT);
protected:
	CameraManager();
	~CameraManager();
};


#endif // !CAMERAMANAGER_H

