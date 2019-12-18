#include "SceneObj.h"

SceneObj::SceneObj(const char* path)
{
	model = new Simplex::Model();
	model->Load(path);
	SetPosRotScale(vector3(0.0f), vector3(0.0f), vector3(1.0f));
}

SceneObj::SceneObj(SceneObj& other)
{
	
}


SceneObj::~SceneObj()
{
	SafeDelete(model);
}


void SceneObj::Draw()
{
	//model->PlaySequence();
	model->AddToRenderList();
}

void SceneObj::SetPosRotScale(vector3 p_position, vector3 p_rotation, vector3 p_scale)
{
	matrix4 m4Model = IDENTITY_M4;
	m4Model = glm::translate(m4Model, p_position);

	//m4Model = glm::rotation(vector3(), p_rotation);
	m4Model = glm::rotate(m4Model, p_rotation.z, vector3(0, 0, 1));
	m4Model = glm::rotate(m4Model, p_rotation.y, vector3(0, 1, 0));
	m4Model = glm::rotate(m4Model, p_rotation.x, vector3(1, 0, 0));

	m4Model = glm::scale(m4Model, p_scale);

	model->SetModelMatrix(m4Model);
}
