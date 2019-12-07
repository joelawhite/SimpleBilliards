#include "PoolBall.h"

PoolBall::PoolBall(const char* p_path)
{
	model = new Simplex::Model();
	model->Load(p_path);
	position = vector3(0.0f);
	rotation = vector3(0.0f);
	scale = vector3(1.0f);
	SetPosRotScale(position, rotation, scale);



	velocity = vector3(0, 0, 0);
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

	//drag
	velocity *= 1.0f - friction;

	//velocity.y = 0;
	position += velocity;

	SetPosRotScale(position, rotation, scale);
}

void PoolBall::Draw(MeshManager *mngr)
{
	//shootAngle += .1f;
	model->AddToRenderList();
	//mngr->AddWireCubeToRenderList(glm::translate(position) * glm::rotate(shootAngle, vector3(0, 1, 0)) * glm::scale(vector3(5.0f, 0.0f, 0.0f)), C_YELLOW);
	//mngr->AddLineToRenderList(glm::translate(position) * glm::rotate(shootAngle, vector3(0, 1, 0)), ZERO_V3, vector3(0,0,1), C_YELLOW, C_YELLOW);
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

void PoolBall::SetPosition(float x, float y, float z) {
	position = vector3(x,y,z);

	matrix4 m4Model = IDENTITY_M4;
	m4Model = glm::translate(m4Model, position);

	//m4Model = glm::rotation(vector3(), p_rotation);
	m4Model = glm::rotate(m4Model, rotation.z, vector3(0, 0, 1));
	m4Model = glm::rotate(m4Model, rotation.y, vector3(0, 1, 0));
	m4Model = glm::rotate(m4Model, rotation.x, vector3(1, 0, 0));

	m4Model = glm::scale(m4Model, scale);

	model->SetModelMatrix(m4Model);
}

vector3 PoolBall::GetPosition()
{
	return position;
}

void PoolBall::SetVelocity(vector3 p_v3)
{
	velocity = p_v3;
}

vector3 PoolBall::GetVelocity()
{
	return velocity;
}

void PoolBall::SetID(int p_ID)
{
	ID = p_ID;
}

int PoolBall::GetID()
{
	return ID;
}

void PoolBall::SetFriction(float n) {
	friction = n;
}
