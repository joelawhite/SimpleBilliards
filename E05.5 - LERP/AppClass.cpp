#include "AppClass.h"
void Application::InitVariables(void)
{
	m_pMeshMngr->SetFont("Font_Andy.png");


	//balls
	ballManager = new BallManager();
	ballManager->SetPath("Planets\\03_Earth.obj");
	ballManager->Init();

	ballManager->SetGameSpeed(100.0f);
	ballManager->SetCameraMode(2);

	gameManager = new GameManager(ballManager);
	gameManager->Reset();


	//models
	table = new SceneObj("PoolTable\\Table.obj");
	table->SetPosRotScale(scenePos, vector3(0.0f), sceneScale);
	stools = new SceneObj("PoolTable\\Stools.obj");
	stools->SetPosRotScale(scenePos, vector3(0.0f), sceneScale);
	boothTables = new SceneObj("PoolTable\\BoothTables.obj");
	boothTables->SetPosRotScale(scenePos, vector3(0.0f), sceneScale);
	poolLight = new SceneObj("PoolTable\\PoolLightobj.obj");
	poolLight->SetPosRotScale(scenePos, vector3(0.0f), sceneScale);
	room = new SceneObj("PoolTable\\Room.obj");
	room->SetPosRotScale(scenePos, vector3(0.0f), sceneScale);
	booths = new SceneObj("PoolTable\\Booths.obj");
	booths->SetPosRotScale(scenePos, vector3(0.0f), sceneScale);
	bar = new SceneObj("PoolTable\\Bar.obj");
	bar->SetPosRotScale(scenePos, vector3(0.0f), sceneScale);
	smallLights = new SceneObj("PoolTable\\SmallLights.obj");
	smallLights->SetPosRotScale(scenePos, vector3(0.0f), sceneScale);
	shelf = new SceneObj("PoolTable\\Shelf.obj");
	shelf->SetPosRotScale(scenePos, vector3(0.0f), sceneScale);

	//Lights
	m_pLightMngr = LightManager::GetInstance();
	
	m_pLightMngr->SetPosition(vector3(0, 1.8f, 0), 1);
	m_pLightMngr->SetIntensity(2, 1);
	lightCount++;
	
	
}
void Application::Update(void)
{
	deltaTime = m_pSystem->GetDeltaTime(0);
	//cursor visibility
	if (!m_pWindow->hasFocus())
		ShowCursor(true);
	else
		ShowCursor(false);

	//Update the system so it knows how much time has passed since the last call
	m_pSystem->Update();

	//Is the arcball active?
	ArcBall();

	//Is the first person camera active?
	CameraRotation();

	//balls
	ballManager->Update(deltaTime);

	//game
	gameManager->Update();

	//camera
	vector3 pos = ZERO_V3;
	vector3 targ = ZERO_V3;
	vector3 v3 = ZERO_V3;
	
	switch (ballManager->getCameraMode()) {
	case 0: //table cam
		targ = vector3(0, -.9f, 0);
		v3 = vector3(sin(cameraRotationH) * cos(cameraRotationV), sin(cameraRotationV), cos(cameraRotationH) * cos(cameraRotationV));
		pos = targ + v3 * cameraDistance;

		m_pCameraMngr->SetPositionTargetAndUpward(pos, targ, AXIS_Y);
		break;

	case 1: //ball cam
		targ = ballManager->GetCueBall()->GetPosition();
		v3 = vector3(sin(cameraRotationH) * cos(cameraRotationV), sin(cameraRotationV), cos(cameraRotationH) * cos(cameraRotationV));
		pos = targ + v3 * cameraDistance;

		m_pCameraMngr->SetPositionTargetAndUpward(pos, targ, AXIS_Y);
		ballManager->SetAngle(cameraRotationH - PI);
		break;

	case 2: //menu
		targ = vector3(0, -.9f, 0);
		pos = menuPos;

		m_pCameraMngr->SetPositionTargetAndUpward(pos, targ, AXIS_Y);
		break;

	case 3://transition
		lerpAmt += deltaTime;
		v3 = vector3(sin(-PI / 2.0f) * cos(0.5f), sin(0.5f), cos(-PI / 2.0f) * cos(0.5f));

		pos = glm::lerp(m_pCameraMngr->GetPosition(), ballManager->GetCueBall()->GetPosition() + v3 * cameraDistance, deltaTime * 2.75f);
		targ = glm::lerp(vector3(0, -.9f, 0), ballManager->GetCueBall()->GetPosition(), lerpAmt/3.0f);

		m_pCameraMngr->SetPositionTargetAndUpward(pos, targ, AXIS_Y);
		
		if (lerpAmt >= 3.0f) {
			cameraRotationH = -PI / 2.0f;
			cameraRotationV = 0.5f;
			lerpAmt = 0.0f;
			ballManager->SetCameraMode(1);
			gameManager->SetState(0);
		}
		
		break;
	case 4: //pause

		break;
	default:
		break;
	}

	lastFrameMode = ballManager->getCameraMode();
}
void Application::Display(void)
{
	// Clear the screen
	ClearScreen();

	//draw light positions
	if (showDebug) {
		for (size_t i = 1; i < lightCount; i++)
		{
			m_pMeshMngr->AddWireSphereToRenderList(glm::translate(m_pLightMngr->GetPosition(i)) * glm::scale(vector3(.1f)), C_YELLOW);
		}

		ballManager->DrawDebug(m_pMeshMngr);
	}




	//balls
	ballManager->Draw(m_pMeshMngr);

	//models
	table->Draw();
	stools->Draw();
	boothTables->Draw();
	if(m_pCameraMngr->GetPosition().y < 1.5f || m_pCameraMngr->GetPosition().x > 3.1f || m_pCameraMngr->GetPosition().x < -3.1f || m_pCameraMngr->GetPosition().z > 2.1f || m_pCameraMngr->GetPosition().z < -2.1f)
		poolLight->Draw();
	room->Draw();
	booths->Draw();
	bar->Draw();
	smallLights->Draw();
	shelf->Draw();




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
	//SafeDelete(ball_1);
	SafeDelete(ballManager);
	SafeDelete(table);
	//release GUI
	ShutdownGUI();
}