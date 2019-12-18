#pragma once
#include "Definitions.h"
#include "ControllerConfiguration.h"
#include "imgui\ImGuiObject.h"
class PoolBall
{
	Simplex::Model* model = nullptr;
	vector3 position;
	vector3 rotation;
	vector3 scale;

	int ID = -1;

	vector3 velocity;
	float friction = 0.004f;

public:
	bool hasCollided = false;
	PoolBall(const char* p_path);
	~PoolBall();
	PoolBall(PoolBall& other);

	void PhysicsUpdate(float deltaTime, float gameSpeed);
	void Draw(MeshManager* mngr);
	void SetPosRotScale(vector3 p_position, vector3 p_rotation, vector3 p_scale);

	void SetPosition(float x, float y, float z);
	void SetPosition(vector3 p_v3);
	vector3 GetPosition();
	void SetVelocity(vector3 p_v3);
	vector3 GetVelocity();
	void SetFriction(float n);

	void SetID(int ID);
	int GetID();

};

