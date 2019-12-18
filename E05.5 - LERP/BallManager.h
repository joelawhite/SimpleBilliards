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
	CameraManager* cameraManager = nullptr;
	

	uint cameraMode = 0; //0-tableview, 1-ballcam
	PoolBall* cueBall = nullptr;
	PoolBall* balls[16];
	TableCollider* tableColliders[6];
	vector3 pockets[6];


	float ballRadius = 0.07f;
	float pocketRadius = 0.11f;
	float shootAngle = 0.0f;
	float shootVelocity = 0.04f;
	float tableHeight = -0.9f;
	float friction = 0.008f;

	vector3 oldBallPos = ZERO_V3;
	
	float gameSpeed = 50.0f;

public:
	BallManager();
	~BallManager();
	BallManager(BallManager& other);

	void Init();
	void ResetBalls();
	void SetPath(char* p_path);
	void Update(float deltaTime);
	void Draw(MeshManager* mngr);
	void DrawDebug(MeshManager* mngr);
	void ChangeAngle(float amount);
	void SetAngle(float amount);
	void ChangeShootStrength(float amount);
	void SetShootStrength(float amount);
	float GetShootStrength();
	uint getCameraMode();
	void SetCameraMode(uint n);
	void Shoot();
	float Distance(vector3 v1, vector3 v2);
	void CalculateCollision(PoolBall* b1, PoolBall* b2);
	PoolBall* GetCueBall();
	void SetGameSpeed(float n);
};

