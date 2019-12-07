#pragma once
#include "Definitions.h"
#include "ControllerConfiguration.h"
#include "imgui\ImGuiObject.h"
#include "PoolBall.h"
#include "TableCollider.h"

class BallManager
{
	Simplex::Model* model = nullptr;
	char* path = nullptr;

	PoolBall* cueBall = nullptr;
	PoolBall* balls[16];
	TableCollider* tableColliders[6];
	vector3 pockets[6];


	float ballRadius = 0.1f;
	float pocketRadius = 0.11f;
	float shootAngle = 0.0f;
	float shootVelocity = 0.02f;
	float tableHeight = -0.9f;
	float friction = 0.004f;

	

public:
	BallManager();
	~BallManager();
	BallManager(BallManager& other);
	BallManager& operator=(BallManager& other);

	void Init();
	void SetPath(char* p_path);
	void Update();
	void Draw(MeshManager* mngr);
	void ChangeAngle(float amount);
	void Shoot();
	float Distance(vector3 v1, vector3 v2);
	void CalculateCollision(PoolBall* b1, PoolBall* b2);
};

