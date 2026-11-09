#include"CameraDebug.h"
#include "SceneGame.h"
#include "Geometory.h"

SceneGame::SceneGame()
{
	m_pGround = new Ground;
	m_pGround->SetPos(0.0f, -0.5f, 0.0f);
	m_pGround->SetScale(3.0f, 0.4f, 3.0f);
	m_pGoal = new Goal;
	m_pGoal->SetPos(1.0f, 1.0f, 0.0f);
	m_pCamera = new CameraDebug;
	m_pModel = new Model();
	if (!m_pModel->Load("Assets/Model/tree_forest.fbx",0.5))
	{
		MessageBox(NULL, "エラー", "モデル表示に失敗", MB_OK);
	}
	/*m_pGoal->SetScale(0.5f, 0.5f, 0.5f);*/
}

SceneGame::~SceneGame()
{
	if (m_pGround) {
		delete m_pGround;
		m_pGround = nullptr;
	}

	if (m_pGoal) {
		delete m_pGoal;
		m_pGoal = nullptr;
	}

	if (m_pCamera) {
		delete m_pCamera;
		m_pCamera = nullptr;
	}

	if (m_pModel) {
		delete m_pModel;
		m_pModel = nullptr;
	}
}

void SceneGame::Update()
{
	m_pGround->Update();
	m_pGoal->Update();
	m_pCamera->Update();
}

void SceneGame::Draw()
{
	Geometory::SetView(m_pCamera->GetViewMatrix(true));
	Geometory::SetProjection(m_pCamera->GetProjectionMatrix(true));
	Geometory::DrawBox();
	m_pGround->Draw();
	m_pGoal->Draw();
	if (m_pModel) {
		m_pModel->Draw();
	}
}
