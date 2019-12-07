#pragma once
#include "Definitions.h"
#include "ControllerConfiguration.h"
#include "imgui\ImGuiObject.h"
class TableCollider
{

public:
	float minX;
	float maxX;
	float minY;
	float maxY;


	TableCollider();
	~TableCollider();

	void Draw(MeshManager* mngr);
	void SetMinMax(float minX, float maxX, float minY, float maxY);
};

