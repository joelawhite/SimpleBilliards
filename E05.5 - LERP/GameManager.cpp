#include "GameManager.h"

GameManager::GameManager(BallManager* bm)
{
	ballManager = bm;
	Reset();
}

GameManager::~GameManager()
{
}

void GameManager::Reset()
{
	playerTurn = 1;
	ballManager->ResetBalls();
}

void GameManager::Update()
{
	switch (gameState) {
	case 0: //game start

		break;
	default:
		break;
	}
}

int GameManager::GetPlayerTurn() 
{
	return playerTurn;
}

int GameManager::GetState()
{
	return gameState;
}

void GameManager::SetState(int n)
{
	gameState = n;
}
