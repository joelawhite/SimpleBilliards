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

	bool isCueBall = false;
	float shootAngle;
	vector3 velocity;
	float friction = 0.000f;

public:
	PoolBall(const char* p_path);
	~PoolBall();
	PoolBall(PoolBall& other);
	PoolBall& operator=(PoolBall& other);

	void PhysicsUpdate();
	void Draw(MeshManager* mngr);
	void SetPosRotScale(vector3 p_position, vector3 p_rotation, vector3 p_scale);
	void Shoot();
};

