#include "PoolBall.h"

PoolBall::PoolBall(const char* p_path)
{
	model = new Simplex::Model();
	model->Load(p_path);
	position = vector3(0.0f);
	rotation = vector3(0.0f);
	scale = vector3(1.0f);
	SetPosRotScale(position, rotation, scale);



	velocity = vector3(.002f, 0, .004f);
}

PoolBall::~PoolBall()
{
	SafeDelete(model);
}

PoolBall::PoolBall(PoolBall& other)
{

}

PoolBall& PoolBall::operator=(PoolBall& other)
{
	// TODO: insert return statement here
}

void PoolBall::PhysicsUpdate()
{
	/*
	bool onTable = false;
	float pocketWidth = .8f;
	bool insidePocket = false;

	if (position.x < 1 && position.x > -1 && position.z < 1 && position.z > -1) {
		onTable = true;
	}

	if (position.x < pocketWidth / 2.0f && position.x > -pocketWidth / 2.0f && !onTable) {
		insidePocket = true;
		velocity = vector3(0, -0.02f, 0);
	}

	//bounce  
	if (!insidePocket){
		if (position.x > 1 || position.x < -1) {
			velocity.x *= -1;
		}
		if (position.z > 1 || position.z < -1) {
		velocity.z *= -1;
	}
	}
	*/
	
	float radius = 0.1f;

	//box1
	float minX = 0.112f + radius;
	float maxX = 2.07f - radius;
	float posZ = 1.12f - radius;
	
	//sides
	if(position.z > posZ && position.x > minX && position.x < maxX){
		velocity.z *= -1;
	}
	if (position.z < -posZ && position.x > minX && position.x < maxX) {
		velocity.z *= -1;
	}

	if (position.z > posZ && position.x < -minX && position.x > -maxX) {
		velocity.z *= -1;
	}
	if (position.z < -posZ && position.x < -minX && position.x > -maxX) {
		velocity.z *= -1;
	}

	float posX = 2.24f - radius;
	float maxZ = 0.95f - radius;

	if (position.x < posX && position.z < maxZ && position.z > -maxZ) {
		velocity.x *= -1;
	}
	if (position.x > -posX && position.z < maxZ && position.z > -maxZ) {
		velocity.x *= -1;
	}

	

	//drag
	velocity *= 1.0f - friction;

	//velocity.y = 0;
	position += velocity;

	SetPosRotScale(position, rotation, scale);
}

void PoolBall::Draw(MeshManager *mngr)
{
	shootAngle += .1f;
	model->AddToRenderList();
	//mngr->AddWireCubeToRenderList(glm::translate(position) * glm::rotate(shootAngle, vector3(0, 1, 0)) * glm::scale(vector3(5.0f, 0.0f, 0.0f)), C_YELLOW);
	mngr->AddLineToRenderList(glm::translate(position) * glm::rotate(shootAngle, vector3(0, 1, 0)), ZERO_V3, vector3(0,0,1), C_YELLOW, C_YELLOW);
}

void PoolBall::SetPosRotScale(vector3 p_position, vector3 p_rotation, vector3 p_scale)
{
	position = p_position;
	rotation = p_rotation;
	scale = p_scale;

	matrix4 m4Model = IDENTITY_M4;
	m4Model = glm::translate(m4Model, position);

	//m4Model = glm::rotation(vector3(), p_rotation);
	m4Model = glm::rotate(m4Model, rotation.z, vector3(0, 0, 1));
	m4Model = glm::rotate(m4Model, rotation.y, vector3(0, 1, 0));
	m4Model = glm::rotate(m4Model, rotation.x, vector3(1, 0, 0));

	m4Model = glm::scale(m4Model, scale);

	model->SetModelMatrix(m4Model);
}

void PoolBall::Shoot()
{
}
