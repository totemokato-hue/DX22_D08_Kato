#include"CameraDebug.h"
#include "SceneGame.h"
#include "Geometory.h"
#include "CameraPlayer.h"


SceneGame::SceneGame()
	: m_pGround(nullptr)
	, m_pGoal(nullptr)
	, m_pCamera(nullptr)
	, m_pModel(nullptr)
	, m_pPlayer(nullptr)
	, m_pPowerGauge(nullptr)
{
	m_pGround = new Ground;
	m_pGround->SetPos(0.0f, -0.2f, 0.0f);
	m_pGround->SetScale(10.0f, 0.4f, 20.0f);
	m_pGoal = new Goal;
	m_pGoal->SetPos(0.0f, 1.0f, 6.0f);
	m_pCamera = new CameraDebug;
	m_pPlayer = new Player;
	m_pPlayer->SetPos(0.0f, 1.0f, -6.0f);
	m_pPowerGauge = new PowerGauge;
	CameraPlayer* pCamera = new CameraPlayer();
	m_pPlayer->SetCamera(pCamera);//球を打ち出すためのカメラを設定
	m_pGround->SetCamera(pCamera);
	pCamera->SetPlayer(m_pPlayer);

	m_pCamera = pCamera;

	// UI用深度テストを初期化
	UIDepthInit();


	//m_pModel = new Model();
	//if (!m_pModel->Load("Assets/Model/tree_forest.fbx",0.5))
	//{
	//	MessageBox(NULL, "エラー", "モデル表示に失敗", MB_OK);
	//}
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

	if (m_pPlayer)
	{
		delete m_pPlayer;
		m_pPlayer = nullptr;
	}

	if (m_pPowerGauge) {
		delete m_pPowerGauge;
		m_pPowerGauge = nullptr;
	}

	if (pUIDepthState)
	{
		pUIDepthState->Release();
		pUIDepthState = nullptr;
	}

	//if (m_pModel) {
	//	delete m_pModel;
	//	m_pModel = nullptr;
	//}
}

void SceneGame::Update()
{
	m_pGround->Update();
	m_pGoal->Update();
	m_pPlayer->Update();
	m_pCamera->Update();

	if (m_pPowerGauge)
	{
		m_pPowerGauge->Update();
	}
}

void SceneGame::Draw()
{
	SetDepthTest(DEPTH_ENABLE);
	Geometory::SetView(m_pCamera->GetViewMatrix(true));
	Geometory::SetProjection(m_pCamera->GetProjectionMatrix(true));
	ShaderList::SetView(m_pCamera->GetViewMatrix(true));
	ShaderList::SetProjection(m_pCamera->GetProjectionMatrix(true));
	//Geometory::DrawBox();
	m_pGround->Draw();
	m_pGoal->Draw();
	m_pPlayer->Draw();
	//if (m_pModel) {
	//	m_pModel->Draw();
	//}
	UIDraw();
}

/**
* @brief	UI用の深度テストを初期化する
*/
void SceneGame::UIDepthInit()
{
	// UI用深度ステートの設定
	D3D11_DEPTH_STENCIL_DESC desc = {};

	desc.DepthEnable = FALSE;
	desc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ZERO;
	desc.DepthFunc = D3D11_COMPARISON_ALWAYS;

	// 深度ステート生成
	HRESULT hr = GetDevice()->CreateDepthStencilState(
		&desc,
		&pUIDepthState
	);

	if (FAILED(hr))
	{
		MessageBox(
			NULL,
			"UI用深度ステートの生成に失敗しました",
			"エラー",
			MB_OK | MB_ICONERROR
		);
	}
}

/**
* @brief	UI用の描画処理
*/
void SceneGame::UIDraw()
{
	// 深度テスト変更
	ID3D11DeviceContext* context = GetContext();

	// 元の深度設定を保存
	ID3D11DepthStencilState* oldState = nullptr;
	UINT oldStencilRef = 0;

	context->OMGetDepthStencilState(
		&oldState,
		&oldStencilRef
	);

	// UI用の深度設定
	context->OMSetDepthStencilState(
		pUIDepthState,
		0
	);

	//--------------------------------------------------
	// 描画
	//--------------------------------------------------
	if (m_pPowerGauge)
	{
		m_pPowerGauge->Draw();
	}
	//--------------------------------------------------

	// 元の設定に戻す
	context->OMSetDepthStencilState(
		oldState,
		oldStencilRef
	);

	if (oldState)
		oldState->Release();
}