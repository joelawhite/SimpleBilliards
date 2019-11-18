#include "PoolBall.h"

PoolBall::PoolBall(const char* p_path)
{
	model = new Simplex::Model();
	model->Load(p_path);
	position = vector3(0.0f);
	rotation = vector3(0.0f);
	scale = vector3(1.0f);
	SetPosRotScale(position, rotation, scale);



	velocity = vector3(.01f, 0, .012f);
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
	if (position.x > 1 || position.x < -1) {
		velocity.x *= -1;
	}
	if (position.z > 1 || position.z < -1) {
		velocity.z *= -1;
	}


	//drag
	velocity *= .998f;

	velocity.y = 0;
	position += velocity;

	SetPosRotScale(position, rotation, scale);
}

void PoolBall::Draw()
{
	model->AddToRenderList();
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
