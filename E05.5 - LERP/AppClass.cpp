#include "AppClass.h"
void Application::InitVariables(void)
{
	//Change this to your name and email
	m_sProgrammer = "Joel White - jxw5738@rit.edu";

	//Set the position and target of the camera
	m_pCameraMngr->SetPositionTargetAndUpward(vector3(0.0f,0.0f,5.0f), vector3(0.0f,-2.0f,0.0f), AXIS_Y);

	m_pModel = new Simplex::Model();
	m_pModel->Load("PoolTable\\PoolTable.obj");
}
void Application::Update(void)
{
	//Update the system so it knows how much time has passed since the last call
	m_pSystem->Update();

	//Is the arcball active?
	ArcBall();

	//Is the first person camera active?
	CameraRotation();
}
void Application::Display(void)
{
	// Clear the screen
	ClearScreen();

	// Draw the model
	m_pModel->PlaySequence();


	vector3 v3CurrentPos = vector3(0.0f, -2.0f, 0.0f);
	matrix4 m4Model = glm::translate(v3CurrentPos);
	m4Model = glm::scale(m4Model, vector3(2));
	m_pModel->SetModelMatrix(m4Model);

	// draw a skybox
	m_pMeshMngr->AddSkyboxToRenderList();
	
	//render list call
	m_uRenderCallCount = m_pMeshMngr->Render();

	//clear the render list
	m_pMeshMngr->ClearRenderList();
	
	//draw gui
	DrawGUI();
	
	//end the current frame (internally swaps the front and back buffers)
	m_pWindow->display();
}
void Application::Release(void)
{
	SafeDelete(m_pModel);
	//release GUI
	ShutdownGUI();
}