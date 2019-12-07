#include "TableCollider.h"

TableCollider::TableCollider()
{
	minX = -1.0f;
	maxX = 1.0f;
	minY = -1.0f;
	maxY = 1.0f;
}

TableCollider::~TableCollider()
{
}

void TableCollider::Draw(MeshManager* mngr)
{
	float posX = (minX + maxX) / 2;
	float posZ = (minY + maxY) / 2;

	float scaleX = maxX - minX;
	float scaleZ = maxY - minY;

	mngr->AddWireCubeToRenderList(glm::translate(vector3(posX, -0.9f, posZ)) * glm::scale(vector3(scaleX, 0.2f, scaleZ)), C_YELLOW);
}

void TableCollider::SetMinMax(float p_minX, float p_maxX, float p_minY, float p_maxY)
{
	minX = p_minX;
	maxX = p_maxX;
	minY = p_minY;
	maxY = p_maxY;
}
