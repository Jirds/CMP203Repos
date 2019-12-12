#pragma once
#include"Vector3.h"
class Camera
{

public:

	Camera();
	~Camera();
	void update();
	void viewRotate(float yawChange, float pitchChange, float rollChange);
	void moveForward(float);
	void moveBackward(float);
	void moveUp(float);
	void moveDown(float);

	Vector3 getPos();
	Vector3 getUp();
	Vector3 getLook();



private:

	Vector3 pos = Vector3(0.0, 0.0, 6.0);
	Vector3 forward = Vector3(0.0, 0.0, 5.0);
	Vector3 up = Vector3(0.0, 1.0, 0.0);

	float yaw = 0.00;
	float pitch = 0.00;
	float roll = 0.00;

	float speed = 15;
};