#include "BallManager.h"

BallManager::BallManager()
{
}

BallManager::~BallManager()
{
	SafeDelete(model);
	SafeDelete(path);
	SafeDelete(cueBall);
}

BallManager::BallManager(BallManager & other)
{
}

BallManager & BallManager::operator=(BallManager & other)
{
	// TODO: insert return statement here
}

void BallManager::Init()
{
	for (size_t i = 0; i < 16; i++)
	{
		balls[i] = new PoolBall(path);
		balls[i]->SetPosRotScale(vector3((i/4.0f) - 1.8f, tableHeight, 0), vector3(), vector3(ballRadius));
		balls[i]->SetID(i);
		balls[i]->SetFriction(friction);
	}

	for (size_t i = 0; i < 6; i++)
	{
		tableColliders[i] = new	TableCollider();
	}

	tableColliders[0]->SetMinMax(0.135f, 2.08f, 1.12f, 2.0f);     //Top Left
	tableColliders[1]->SetMinMax(-2.08f, -0.135f, 1.12f, 2.0f);   //Top Right
	tableColliders[2]->SetMinMax(0.135f, 2.08f, -2.0f, -1.12f);   //Bottom Left
	tableColliders[3]->SetMinMax(-2.08f, -0.135f, -2.0f, -1.12f); //Bottom Right
	tableColliders[4]->SetMinMax(2.24f, 3.0f, -0.95f, 0.95f);     //Left
	tableColliders[5]->SetMinMax(-3.0f, -2.24f, -0.95f, 0.95f);   //Right

	pockets[0] = vector3(2.3f, tableHeight, 1.18f);	//Top Left
	pockets[1] = vector3(-2.3f, tableHeight, 1.18f);	//Top Right
	pockets[2] = vector3(2.3f, tableHeight, -1.18f);	//Bottom Left
	pockets[3] = vector3(-2.3f, tableHeight, -1.18f);	//Bottom Right
	pockets[4] = vector3(0.0f, tableHeight, 1.34f);	//Top
	pockets[5] = vector3(0.0f, tableHeight, -1.34f);	//Bottom


}

void BallManager::SetPath(char* p_path)
{
	path = p_path;
}

void BallManager::Update()
{	
	std::cout << "NEW FRAME ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;

#pragma region WallCollision
	for (size_t i = 0; i < 6; i++)
	{
		for (size_t k = 0; k < 16; k++)
		{
			//~~~~~~~~~~~~~~Edges~~~~~~~~~~~~~~~
			//bottom side
			if (balls[k]->GetPosition().x > tableColliders[i]->minX && balls[k]->GetPosition().x < tableColliders[i]->maxX && balls[k]->GetPosition().z + ballRadius > tableColliders[i]->minY) {
				balls[k]->SetVelocity(balls[k]->GetVelocity() * vector3(1.0f, 1.0f, -1.0f));
			}
			//top side
			if (balls[k]->GetPosition().x > tableColliders[i]->minX && balls[k]->GetPosition().x < tableColliders[i]->maxX && balls[k]->GetPosition().z - ballRadius < tableColliders[i]->maxY) {
				balls[k]->SetVelocity(balls[k]->GetVelocity() * vector3(1.0f, 1.0f, -1.0f));
			}
			//left side
			if (balls[k]->GetPosition().z > tableColliders[i]->minY && balls[k]->GetPosition().z < tableColliders[i]->maxY && balls[k]->GetPosition().x + ballRadius < tableColliders[i]->minX) {
				balls[k]->SetVelocity(balls[k]->GetVelocity() * vector3(-1.0f, 1.0f, 1.0f));
			}
			//right side
			if (balls[k]->GetPosition().z > tableColliders[i]->minY && balls[k]->GetPosition().z < tableColliders[i]->maxY && balls[k]->GetPosition().x - ballRadius > tableColliders[i]->maxX) {
				balls[k]->SetVelocity(balls[k]->GetVelocity() * vector3(-1.0f, 1.0f, 1.0f));
			}
			
			//~~~~~~~~~~~~~Corners~~~~~~~~~~~~~~
			//Top left
			vector3 p1 = vector3(tableColliders[i]->minX, tableHeight, tableColliders[i]->maxY);
			if (Distance(balls[k]->GetPosition(), p1) < ballRadius) {
				std::cout << "p1" << std::endl;
				vector3 bisectionNormal = glm::normalize(balls[k]->GetPosition() - p1);
				vector3 newVel = balls[k]->GetVelocity() - 2 * glm::dot(balls[k]->GetVelocity(), bisectionNormal) * bisectionNormal;
				balls[k]->SetVelocity(newVel);
			}
			//Top right
			vector3 p2 = vector3(tableColliders[i]->maxX, tableHeight, tableColliders[i]->maxY);
			if (Distance(balls[k]->GetPosition(), p2) < ballRadius) {
				std::cout << "p2" << std::endl;
				vector3 bisectionNormal = glm::normalize(balls[k]->GetPosition() - p2);
				vector3 newVel = balls[k]->GetVelocity() - 2 * glm::dot(balls[k]->GetVelocity(), bisectionNormal) * bisectionNormal;
				balls[k]->SetVelocity(newVel);
			}
			//bottom left
			vector3 p3 = vector3(tableColliders[i]->minX, tableHeight, tableColliders[i]->minY);
			if (Distance(balls[k]->GetPosition(), p3) < ballRadius) {
				std::cout << "p3" << std::endl;
				vector3 bisectionNormal = glm::normalize(balls[k]->GetPosition() - p3);
				vector3 newVel = balls[k]->GetVelocity() - 2 * glm::dot(balls[k]->GetVelocity(), bisectionNormal) * bisectionNormal;
				balls[k]->SetVelocity(newVel);
			}
			//bottom right
			vector3 p4 = vector3(tableColliders[i]->maxX, tableHeight, tableColliders[i]->minY);
			if (Distance(balls[k]->GetPosition(), p4) < ballRadius) {
				std::cout << "p4" << std::endl;
				vector3 bisectionNormal = glm::normalize(balls[k]->GetPosition() - p4);
				vector3 newVel = balls[k]->GetVelocity() - 2 * glm::dot(balls[k]->GetVelocity(), bisectionNormal) * bisectionNormal;
				balls[k]->SetVelocity(newVel);
			}

		}
	}

#pragma endregion


#pragma region Ball Collision

	//get all collision pairs
	std::vector<std::vector<PoolBall*>> collisions;
	for (size_t i = 0; i < 16; i++)
	{
		balls[i]->PhysicsUpdate(); ///table bounce

		//collision
		for (size_t k = 0; k < 16; k++)
		{
			if (i == k) { continue; }

			if (Distance(balls[i]->GetPosition(), balls[k]->GetPosition()) < ballRadius * 1.94f) {

				std::vector<PoolBall*> c1{ balls[i], balls[k] };
				std::vector<PoolBall*> c1_inverse{ balls[k], balls[i] };

				//if inverse is not in list, add to list
				if(std::find(collisions.begin(), collisions.end(), c1_inverse) == collisions.end()){
					collisions.push_back(c1);
				}
				
			}
		}
	}

	//static collisions
	for (size_t i = 0; i < collisions.size(); i++)
	{
		PoolBall* ball1 = collisions[i][0];
		PoolBall* ball2 = collisions[i][1];

		// Distance between ball centers
		float fDistance = glm::sqrt((ball1->GetPosition().x - ball2->GetPosition().x) * (ball1->GetPosition().x - ball2->GetPosition().x) +
									(ball1->GetPosition().z - ball2->GetPosition().z) * (ball1->GetPosition().z - ball2->GetPosition().z));

		// Calculate displacement required
		float fOverlap = 0.5f * (fDistance - ballRadius * 2);

		// Displace Current Ball away from collision
		float px = ball1->GetPosition().x - (fOverlap * (ball1->GetPosition().x - ball2->GetPosition().x) / fDistance);
		float pz = ball1->GetPosition().z - (fOverlap * (ball1->GetPosition().z - ball2->GetPosition().z) / fDistance);
		ball1->SetPosition(px, -0.9f, pz);

		// Displace Target Ball away from collision
		px = ball2->GetPosition().x + (fOverlap * (ball1->GetPosition().x - ball2->GetPosition().x) / fDistance);
		pz = ball2->GetPosition().z + (fOverlap * (ball1->GetPosition().z - ball2->GetPosition().z) / fDistance);
		ball2->SetPosition(px, -0.9f, pz);
	}

	//dynamic collisions
	for (size_t i = 0; i < collisions.size(); i++)
	{
		std::cout << "Calculating collision for " << collisions[i][0]->GetID() << ", " << collisions[i][1]->GetID() << std::endl;
		CalculateCollision(collisions[i][0], collisions[i][1]);
	}

#pragma endregion


#pragma region Pockets

	for (size_t k = 0; k < 16; k++)
	{
		for (size_t i = 0; i < 6; i++)
		{
			if (Distance(balls[k]->GetPosition(), pockets[i]) < ballRadius + pocketRadius) {
				balls[k]->SetVelocity(ZERO_V3);
				balls[k]->SetPosition(pockets[i].x, pockets[i].y, pockets[i].z);
			}
		}
	}

#pragma endregion

}

void BallManager::CalculateCollision(PoolBall* b1, PoolBall* b2) {

	float b1px = b1->GetPosition().x;
	float b1py = b1->GetPosition().z;
	float b2px = b2->GetPosition().x;
	float b2py = b2->GetPosition().z;

	float b1vx = b1->GetVelocity().x;
	float b1vy = b1->GetVelocity().z;
	float b2vx = b2->GetVelocity().x;
	float b2vy = b2->GetVelocity().z;


	// Distance between balls
	float fDistance = sqrtf((b1px - b2px) * (b1px - b2px) + (b1py - b2py) * (b1py - b2py));

	// Normal
	float nx = (b2px - b1px) / fDistance;
	float ny = (b2py - b1py) / fDistance;

	// Tangent
	float tx = -ny;
	float ty = nx;

	// Dot Product Tangent
	float dpTan1 = b1vx * tx + b1vy * ty;
	float dpTan2 = b2vx * tx + b2vy * ty;

	// Dot Product Normal
	float dpNorm1 = b1vx * nx + b1vy * ny;
	float dpNorm2 = b2vx * nx + b2vy * ny;

	// Conservation of momentum in 1D
	float m1 = (dpNorm1 * (1 - 1) + 2.0f * 1 * dpNorm2) / (1 + 1);
	float m2 = (dpNorm2 * (1 - 1) + 2.0f * 1 * dpNorm1) / (1 + 1);

	// Update ball velocities
	b1vx = tx * dpTan1 + nx * m1;
	b1vy = ty * dpTan1 + ny * m1;
	b2vx = tx * dpTan2 + nx * m2;
	b2vy = ty * dpTan2 + ny * m2;

	b1->SetVelocity(vector3(b1vx, 0, b1vy));
	b2->SetVelocity(vector3(b2vx, 0, b2vy));

}

void BallManager::Draw(MeshManager* mngr)
{

	mngr->AddLineToRenderList(glm::translate(balls[0]->GetPosition()) * glm::rotate(shootAngle, vector3(0, 1, 0)), ZERO_V3, vector3(0, 0, 1), C_GREEN, C_WHITE);

	for (size_t i = 0; i < 16; i++)
	{
		balls[i]->Draw(mngr);
	}

	for (size_t i = 0; i < 6; i++)
	{
		tableColliders[i]->Draw(mngr);
		mngr->AddWireSphereToRenderList(glm::translate(pockets[i]) * glm::scale(vector3(pocketRadius)), C_WHITE);
	}
}

void BallManager::ChangeAngle(float amount)
{
	shootAngle += amount;
}

void BallManager::Shoot()
{
	balls[0]->SetVelocity(vector3(sin(shootAngle), 0, cos(shootAngle)) * shootVelocity);
}

float BallManager::Distance(vector3 v1, vector3 v2) {
	return glm::sqrt((v1.x - v2.x) * (v1.x - v2.x) +
		(v1.y - v2.y) * (v1.y - v2.y) +
		(v1.z - v2.z) * (v1.z - v2.z));
}