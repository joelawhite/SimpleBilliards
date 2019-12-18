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


void BallManager::Init()
{
	cameraManager = cameraManager->GetInstance();
	

	float spaceHori = ballRadius + 0.001f;
	float spaceVert = ballRadius * 2 - 0.03f;

	for (size_t i = 0; i < 16; i++)
	{
		vector3 pos = ZERO_V3;

		switch (i) {

		//que ball
		case 0:
			pos = vector3(-2, tableHeight, 0);
			break;

		case 1:
			pos = vector3(0, tableHeight, 0);
			break;


		case 2:
			pos = vector3(spaceVert, tableHeight, -spaceHori);
			break;
		case 3:
			pos = vector3(spaceVert, tableHeight, spaceHori);
			break;

			
		case 4:
			pos = vector3(spaceVert * 2, tableHeight, 0);
			break;
		case 5:
			pos = vector3(spaceVert * 2, tableHeight, -spaceHori * 2);
			break;
		case 6:
			pos = vector3(spaceVert * 2, tableHeight, spaceHori * 2);
			break;


		case 7:
			pos = vector3(spaceVert * 3, tableHeight, -spaceHori);
			break;
		case 8:
			pos = vector3(spaceVert * 3, tableHeight, spaceHori);
			break;
		case 9:
			pos = vector3(spaceVert * 3, tableHeight, -spaceHori * 3);
			break;
		case 10:
			pos = vector3(spaceVert * 3, tableHeight, spaceHori * 3);
			break;


		case 11:
			pos = vector3(spaceVert * 4, tableHeight, 0);
			break;
		case 12:
			pos = vector3(spaceVert * 4, tableHeight, -spaceHori * 2);
			break;
		case 13:
			pos = vector3(spaceVert * 4, tableHeight, spaceHori * 2);
			break;
		case 14:
			pos = vector3(spaceVert * 4, tableHeight, -spaceHori * 4);
			break;
		case 15:
			pos = vector3(spaceVert * 4, tableHeight, spaceHori * 4);
			break;


		default:
			pos = vector3(i, tableHeight, 0);
			break;
		}


		balls[i] = new PoolBall(path);
		balls[i]->SetPosRotScale(pos, vector3(), vector3(ballRadius));
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

void BallManager::ResetBalls() {

	float spaceHori = ballRadius + 0.001f;
	float spaceVert = ballRadius * 2 - 0.03f;

	float rackDistance = 1.3f;

	for (size_t i = 0; i < 16; i++)
	{
		vector3 pos = ZERO_V3;

		switch (i) {

			//que ball
		case 0:
			pos = vector3(-2, tableHeight, 0);
			break;

		case 1:
			pos = vector3(0, tableHeight, 0);
			break;


		case 2:
			pos = vector3(spaceVert, tableHeight, -spaceHori);
			break;
		case 3:
			pos = vector3(spaceVert, tableHeight, spaceHori);
			break;


		case 4:
			pos = vector3(spaceVert * 2, tableHeight, 0);
			break;
		case 5:
			pos = vector3(spaceVert * 2, tableHeight, -spaceHori * 2);
			break;
		case 6:
			pos = vector3(spaceVert * 2, tableHeight, spaceHori * 2);
			break;


		case 7:
			pos = vector3(spaceVert * 3, tableHeight, -spaceHori);
			break;
		case 8:
			pos = vector3(spaceVert * 3, tableHeight, spaceHori);
			break;
		case 9:
			pos = vector3(spaceVert * 3, tableHeight, -spaceHori * 3);
			break;
		case 10:
			pos = vector3(spaceVert * 3, tableHeight, spaceHori * 3);
			break;


		case 11:
			pos = vector3(spaceVert * 4, tableHeight, 0);
			break;
		case 12:
			pos = vector3(spaceVert * 4, tableHeight, -spaceHori * 2);
			break;
		case 13:
			pos = vector3(spaceVert * 4, tableHeight, spaceHori * 2);
			break;
		case 14:
			pos = vector3(spaceVert * 4, tableHeight, -spaceHori * 4);
			break;
		case 15:
			pos = vector3(spaceVert * 4, tableHeight, spaceHori * 4);
			break;


		default:
			pos = vector3(i, tableHeight, 0);
			break;
		}

		balls[i]->SetPosRotScale(pos + vector3(rackDistance, 0, 0), vector3(), vector3(ballRadius));
		balls[i]->SetID(i);
		balls[i]->SetFriction(friction);
	}

	balls[0]->SetPosition(-1.1f, tableHeight, 0);
}

void BallManager::SetPath(char* p_path)
{
	path = p_path;
}

void BallManager::Update(float deltaTime)
{		
	//move camera
	if (cameraMode == 1) {
		cameraManager->SetPosition(cameraManager->GetPosition() + (balls[0]->GetPosition() - oldBallPos));
		oldBallPos = balls[0]->GetPosition();
	}

	for (size_t i = 0; i < 16; i++)
	{
		balls[i]->PhysicsUpdate(deltaTime, gameSpeed);
	}

#pragma region WallCollision
	for (size_t i = 0; i < 6; i++)
	{
		for (size_t k = 0; k < 16; k++)
		{
			
			bool side = false;
			//~~~~~~~~~~~~~~Edges~~~~~~~~~~~~~~~
			//bottom side
			if (balls[k]->GetPosition().x > tableColliders[i]->minX && balls[k]->GetPosition().x < tableColliders[i]->maxX && balls[k]->GetPosition().z + ballRadius > tableColliders[i]->minY && balls[k]->GetPosition().z + ballRadius < tableColliders[i]->maxY) {
				std::cout << "bottom" << std::endl;
				balls[k]->SetPosition(balls[k]->GetPosition().x, balls[k]->GetPosition().y, tableColliders[i]->minY - ballRadius);
				balls[k]->SetVelocity(balls[k]->GetVelocity() * vector3(1.0f, 1.0f, -1.0f));
				side = true;
			} 
			//top side
			if (balls[k]->GetPosition().x > tableColliders[i]->minX && balls[k]->GetPosition().x < tableColliders[i]->maxX && balls[k]->GetPosition().z - ballRadius < tableColliders[i]->maxY && balls[k]->GetPosition().z - ballRadius > tableColliders[i]->minY) {
				std::cout << "top" << std::endl;
				balls[k]->SetPosition(balls[k]->GetPosition().x, balls[k]->GetPosition().y, tableColliders[i]->maxY + ballRadius);
				balls[k]->SetVelocity(balls[k]->GetVelocity() * vector3(1.0f, 1.0f, -1.0f));
				side = true;
			}
			//left side
			if (balls[k]->GetPosition().z > tableColliders[i]->minY && balls[k]->GetPosition().z < tableColliders[i]->maxY && balls[k]->GetPosition().x + ballRadius > tableColliders[i]->minX && balls[k]->GetPosition().x + ballRadius < tableColliders[i]->maxX) {
				std::cout << "left" << std::endl;
				balls[k]->SetPosition(tableColliders[i]->minX - ballRadius, balls[k]->GetPosition().y, balls[k]->GetPosition().z);
				balls[k]->SetVelocity(balls[k]->GetVelocity() * vector3(-1.0f, 1.0f, 1.0f));
				side = true;
			}
			//right side
			if (balls[k]->GetPosition().z > tableColliders[i]->minY && balls[k]->GetPosition().z < tableColliders[i]->maxY && balls[k]->GetPosition().x - ballRadius < tableColliders[i]->maxX && balls[k]->GetPosition().x - ballRadius > tableColliders[i]->minX) {
				std::cout << "right" << std::endl;
				balls[k]->SetPosition(tableColliders[i]->maxX + ballRadius, balls[k]->GetPosition().y, balls[k]->GetPosition().z);
				balls[k]->SetVelocity(balls[k]->GetVelocity() * vector3(-1.0f, 1.0f, 1.0f));
				side = true;
			}

			if (side) { continue; }
			
			






			//~~~~~~~~~~~~~Corners~~~~~~~~~~~~~~
			//Top left
			vector3 p1 = vector3(tableColliders[i]->minX, tableHeight, tableColliders[i]->maxY);
			if (Distance(balls[k]->GetPosition(), p1) < ballRadius) {
				//move ball back
				float dist = ballRadius - Distance(balls[k]->GetPosition(), p1);
				balls[k]->SetPosition(balls[k]->GetPosition() - glm::normalize(balls[k]->GetVelocity()) * dist);

				std::cout << "p1" << std::endl;
				vector3 bisectionNormal = glm::normalize(balls[k]->GetPosition() - p1);
				vector3 newVel = balls[k]->GetVelocity() - 2 * glm::dot(balls[k]->GetVelocity(), bisectionNormal) * bisectionNormal;
				balls[k]->SetVelocity(newVel);
			}
			//Top right
			vector3 p2 = vector3(tableColliders[i]->maxX, tableHeight, tableColliders[i]->maxY);
			if (Distance(balls[k]->GetPosition(), p2) < ballRadius) {
				//move ball back
				float dist = ballRadius - Distance(balls[k]->GetPosition(), p2);
				balls[k]->SetPosition(balls[k]->GetPosition() - glm::normalize(balls[k]->GetVelocity()) * dist);

				std::cout << "p2" << std::endl;
				vector3 bisectionNormal = glm::normalize(balls[k]->GetPosition() - p2);
				vector3 newVel = balls[k]->GetVelocity() - 2 * glm::dot(balls[k]->GetVelocity(), bisectionNormal) * bisectionNormal;
				balls[k]->SetVelocity(newVel);
			}
			//bottom left
			vector3 p3 = vector3(tableColliders[i]->minX, tableHeight, tableColliders[i]->minY);
			if (Distance(balls[k]->GetPosition(), p3) < ballRadius) {
				//move ball back
				float dist = ballRadius - Distance(balls[k]->GetPosition(), p3);
				balls[k]->SetPosition(balls[k]->GetPosition() - glm::normalize(balls[k]->GetVelocity()) * dist);

				std::cout << "p3" << std::endl;
				vector3 bisectionNormal = glm::normalize(balls[k]->GetPosition() - p3);
				vector3 newVel = balls[k]->GetVelocity() - 2 * glm::dot(balls[k]->GetVelocity(), bisectionNormal) * bisectionNormal;
				balls[k]->SetVelocity(newVel);
			}
			//bottom right
			vector3 p4 = vector3(tableColliders[i]->maxX, tableHeight, tableColliders[i]->minY);
			if (Distance(balls[k]->GetPosition(), p4) < ballRadius) {
				//move ball back
				float dist = ballRadius - Distance(balls[k]->GetPosition(), p4);
				balls[k]->SetPosition(balls[k]->GetPosition() - glm::normalize(balls[k]->GetVelocity()) * dist);

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

PoolBall* BallManager::GetCueBall()
{
	return balls[0];
}

void BallManager::SetGameSpeed(float n)
{
	gameSpeed = n;
}

void BallManager::Draw(MeshManager* mngr)
{
	mngr->AddLineToRenderList(glm::translate(balls[0]->GetPosition()) * glm::rotate(shootAngle, vector3(0, 1, 0)), ZERO_V3, vector3(0, 0, shootVelocity), C_GREEN, C_WHITE);

	for (size_t i = 0; i < 16; i++)
	{
		balls[i]->Draw(mngr);
	}

}

void BallManager::DrawDebug(MeshManager* mngr) {
	for (size_t i = 0; i < 6; i++)
	{
		tableColliders[i]->Draw(mngr);
		mngr->AddWireSphereToRenderList(glm::translate(pockets[i]) * glm::scale(vector3(pocketRadius)), C_WHITE);
	}
}

void BallManager::ChangeAngle(float amount)
{
	shootAngle += amount * 0.1f;
}

void BallManager::SetAngle(float amount)
{
	shootAngle = amount;
}

void BallManager::ChangeShootStrength(float amount)
{
	shootVelocity += amount * 0.1f;
}

void BallManager::SetShootStrength(float amount)
{
	shootVelocity = amount;
}

float BallManager::GetShootStrength()
{
	return shootVelocity;
}

uint BallManager::getCameraMode()
{
	return cameraMode;
}

void BallManager::SetCameraMode(uint n)
{
	cameraMode = n;
}

void BallManager::Shoot()
{
	balls[0]->SetVelocity(vector3(sin(shootAngle), 0, cos(shootAngle)) * shootVelocity * 0.02f);
}

float BallManager::Distance(vector3 v1, vector3 v2) {
	return glm::sqrt((v1.x - v2.x) * (v1.x - v2.x) +
		(v1.y - v2.y) * (v1.y - v2.y) +
		(v1.z - v2.z) * (v1.z - v2.z));
}