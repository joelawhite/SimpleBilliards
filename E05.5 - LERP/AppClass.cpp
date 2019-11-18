#include "AppClass.h"
void Application::InitVariables(void)
{
	//Set the position and target of the camera
	m_pCameraMngr->SetPositionTargetAndUpward(menuPos, vector3(0, -1, 0), AXIS_Y);


	//balls
	ball_1 = new PoolBall("Planets\\03_Earth.obj");
	ball_1->SetPosRotScale(vector3(), vector3(), vector3(.1f));


	//models
	table = new SceneObj("PoolTable\\PoolTable.obj");
	table->SetPosRotScale(vector3(0, -1, 0), vector3(), vector3(1));




	//Lights
	showLights = true;
	m_pLightMngr = LightManager::GetInstance();
	
	m_pLightMngr->SetPosition(vector3(0, -.9f, 0), 1);
	m_pLightMngr->SetIntensity(5, 1);
	lightCount++;
	
	
}
void Application::Update(void)
{
	//Update the system so it knows how much time has passed since the last call
	m_pSystem->Update();

	//Is the arcball active?
	ArcBall();

	//Is the first person camera active?
	CameraRotation();

	//balls
	ball_1->PhysicsUpdate();

	if (transitioning) {
		std::cout << perc << std::endl;
		perc += cameraSpeed;
		m_pCameraMngr->SetPositionTargetAndUpward(glm::lerp(menuPos, tablePos, perc), vector3(0, -1, 0), AXIS_Y);
	}
	if (perc >= 1.0f) {
		transitioning = false;
		inMenu = false;
		perc = 0.0f;
	}
	if (inMenu && !transitioning) {
		m_pCameraMngr->SetPositionTargetAndUpward(menuPos, vector3(0, -1, 0), AXIS_Y);
	}

}
void Application::Display(void)
{
	// Clear the screen
	ClearScreen();

	//draw light positions
	if (showLights) {
		for (size_t i = 1; i < lightCount; i++)
		{
			m_pMeshMngr->AddWireSphereToRenderList(glm::translate(m_pLightMngr->GetPosition(i)) * glm::scale(vector3(.1f)), C_YELLOW);
		}
	}

	//balls
	ball_1->Draw();

	//models
	table->Draw();
	







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
	SafeDelete(ball_1);
	SafeDelete(table);
	//release GUI
	ShutdownGUI();
}