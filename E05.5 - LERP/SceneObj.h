#pragma once
#include "Definitions.h"
#include "ControllerConfiguration.h"
#include "imgui\ImGuiObject.h"
class SceneObj
{
	Simplex::Model* model = nullptr;
	vector3 position;
	vector3 rotation;
	vector3 scale;


public:
	SceneObj(const char *p_path);
	~SceneObj();
	SceneObj(SceneObj& other);
	SceneObj& operator=(SceneObj& other);

	void Draw();
	void SetPosRotScale(vector3 p_position, vector3 p_rotation, vector3 p_scale);
};

