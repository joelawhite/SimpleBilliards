#pragma once
#include "Definitions.h"
#include "ControllerConfiguration.h"
#include "imgui\ImGuiObject.h"
#include "BallManager.h"
class GameManager
{
	BallManager* ballManager = nullptr;
	int playerTurn = 1;
	int gameState = -1;

public:
	GameManager(BallManager* bm);
	~GameManager();

	void Reset();
	void Update();
	int GetPlayerTurn();
	int GetState();
	void SetState(int n);

};

