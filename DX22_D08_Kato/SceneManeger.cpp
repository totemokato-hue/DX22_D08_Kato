#include "SceneManeger.h"

SceneManeger::SceneManeger()
	: m_pGround(nullptr)
	, m_pGoal(nullptr)
	, m_pCamera(nullptr)
	, m_pModel(nullptr)
	, m_pPlayer(nullptr)
	, m_pPowerGauge(nullptr)
	, fPoint(nullptr)
	, m_tCamera(nullptr)
	, m_pPlayerCamera(nullptr)
	, m_pFollowCamera(nullptr)
	, pUIDepthState(nullptr)
	, m_pWall(nullptr)
	, m_pEnemy(nullptr)
{

}

SceneManeger::~SceneManeger()
{
}

// 初期化
void SceneManeger::InitManeger()
{
	m_pGround = new Ground;
	m_pGround->SetPos(0.0f, -0.2f, 0.0f);
	m_pGround->SetScale(10.0f, 0.4f, 20.0f);

	m_pGoal = new Goal;
	m_pGoal->SetPos(0.0f, 1.0f, 6.0f);

	m_pPlayer = new Player;
	m_pPlayer->SetPos(0.0f, 1.0f, -6.0f);

	m_pPowerGauge = new PowerGauge;
	m_pPowerGauge->SetPlayer(m_pPlayer);
	CameraPlayer* pCamera = new CameraPlayer();
	m_pPlayer->SetCamera(pCamera);//球を打ち出すためのカメラを設定
	pCamera->SetPlayer(m_pPlayer);
	TopCamera* tCamera = new TopCamera();
	fPoint = new ForcusPoint();

	fPoint->SetCamera(tCamera);
	tCamera->SetForcus(fPoint);
	m_tCamera = tCamera;

	//==================================================
	// 壁
	//==================================================
	m_pWall = new Wall();
	m_pWall->SetPos(0.0f, 0.0f, 0.0f);
	m_pWall->SetScale(10.0f, 4.0f, 1.0f);

	// UI用深度テストを初期化
	UIDepthInit();
}

void SceneManeger::Destructor()
{
	if (m_pGround) 
	{
		delete m_pGround;
		m_pGround = nullptr;
	}

	if (m_pGoal) 
	{
		delete m_pGoal;
		m_pGoal = nullptr;
	}

	if (m_pCamera) {
		delete m_pCamera;
		m_pCamera = nullptr;
	}

	// 現在使用中のカメラ
	m_pCamera = nullptr;

	if (m_pPlayer)
	{
		delete m_pPlayer;
		m_pPlayer = nullptr;
	}

	if (m_pPowerGauge) 
	{
		delete m_pPowerGauge;
		m_pPowerGauge = nullptr;
	}

	if (pUIDepthState)
	{
		pUIDepthState->Release();
		pUIDepthState = nullptr;
	}

	if (m_tCamera) 
	{
		delete m_tCamera;
		m_tCamera = nullptr;
	}

	if (fPoint) 
	{
		delete fPoint;
		fPoint = nullptr;
	}

	if (m_pWall)
	{
		delete m_pWall;
		m_pWall = nullptr;
	}

	if (m_pEnemy)
	{
		delete m_pEnemy;
		m_pEnemy = nullptr;
	}
}

void SceneManeger::UpdateManeger()
{
	//射撃モードとカメラモードの切り替え
	if (IsKeyTrigger('M'))
	{
		if (m_nScene == ShotMode)
		{
			m_nScene = F_CameraMode;
		}
		else
		{
			m_nScene = ShotMode;
		}
	}
	//シーン切り替え
	switch (m_nScene)
	{

		//正面のトップカメラ
	case F_CameraMode:
		m_tCamera->SetMode(TopCamera::FRONT);
		fPoint->Update(0.0f,false);
		m_pGoal->Update();
		break;

	case R_CameraMode:
		m_tCamera->SetMode(TopCamera::RIGHT);
		fPoint->Update(-DirectX::XM_PIDIV2,true);
		m_pGoal->Update();
		break;

	case L_CameraMode:
		m_tCamera->SetMode(TopCamera::LEFT);
		fPoint->Update(DirectX::XM_PIDIV2,true);
		m_pGoal->Update();
		break;


		//射撃モード
	case ShotMode:
		m_pGround->Update();
		m_pGoal->Update();
		m_pPlayer->Update();

		// 発射後は追従カメラに切り替える
		if (m_pPlayer->IsFlying())
		{
			m_isFollowCamera = true;
		}

		// 発射前の状態に戻ったら通常カメラに戻す
		if (m_pPlayer->IsAiming())
		{
			m_isFollowCamera = false;
		}

		// 使用するカメラを選択
		if (m_isFollowCamera)
		{
			m_pCamera = m_pFollowCamera;
		}
		else
		{
			m_pCamera = m_pPlayerCamera;
		}

		// 選択したカメラを更新
		m_pCamera->Update();

		m_pWall->Update();
		break;
		
	}

	// 敵の更新
	if (m_pEnemy && m_pEnemy->IsAlive())
	{
		m_pEnemy->Update();

		// プレイヤーと敵の当たり判定
		Collision::Box playerCollision =
			m_pPlayer->GetCollisionBox();

		Collision::Box enemyCollision =
			m_pEnemy->GetCollisionBox();

		Collision::Result result =
			Collision::Hit(playerCollision, enemyCollision);

		if (result.isHit)
		{
			// 敵を消す
			m_pEnemy->Hit();
		}
	}
	
	//トップカメラの切り替え
	if (m_nScene != ShotMode)
	{
		m_tCamera->Update();
		if (IsKeyTrigger(VK_RIGHT))
		{
			m_nScene = R_CameraMode;
		}
		if (IsKeyTrigger(VK_LEFT))
		{
			m_nScene = L_CameraMode;
		}
		if (IsKeyTrigger(VK_DOWN))
		{
			m_nScene = F_CameraMode;
		}
	}
	if (m_pPowerGauge)
	{
		m_pPowerGauge->Update();
	}

	//それぞれの当たり判定を取得
	Collision::Box playerCollision = m_pPlayer->GetCollisionBox();
	Collision::Box wallCollision = m_pWall->GetCollisionBox();

	//当たり判定をもとに衝突判定を実施
	Collision::Result result = Collision::Hit(playerCollision, wallCollision);

	if (result.isHit) {
		m_pPlayer->Hit();
	}


}

void SceneManeger::DrawManeger()
{
	SetDepthTest(DEPTH_ENABLE);

	switch (m_nScene)
	{

		//正面のトップカメラ
	case F_CameraMode:
		Geometory::SetView(m_tCamera->GetViewMatrix(true));
		Geometory::SetProjection(m_tCamera->GetProjectionMatrix(true));
		ShaderList::SetView(m_tCamera->GetViewMatrix(true));
		ShaderList::SetProjection(m_tCamera->GetProjectionMatrix(true));
		fPoint->Draw();
		break;

		//右サイドカメラ
	case R_CameraMode:
		Geometory::SetView(m_tCamera->GetViewMatrix(true));
		Geometory::SetProjection(m_tCamera->GetProjectionMatrix(true));
		ShaderList::SetView(m_tCamera->GetViewMatrix(true));
		ShaderList::SetProjection(m_tCamera->GetProjectionMatrix(true));
		fPoint->Draw();
		break;
		//左サイドカメラ
	case L_CameraMode:
		Geometory::SetView(m_tCamera->GetViewMatrix(true));
		Geometory::SetProjection(m_tCamera->GetProjectionMatrix(true));
		ShaderList::SetView(m_tCamera->GetViewMatrix(true));
		ShaderList::SetProjection(m_tCamera->GetProjectionMatrix(true));
		fPoint->Draw();
		break;
		//射撃モード
	case ShotMode:
		Geometory::SetView(m_pCamera->GetViewMatrix(true));
		Geometory::SetProjection(m_pCamera->GetProjectionMatrix(true));
		ShaderList::SetView(m_pCamera->GetViewMatrix(true));
		ShaderList::SetProjection(m_pCamera->GetProjectionMatrix(true));
		break;
	}
	//常に表示するもの
	m_pGround->Draw();
	m_pGoal->Draw();
	m_pPlayer->Draw();
	m_pWall->Draw();

	//当たったら消えるもの
	if (m_pEnemy)
	{
		m_pEnemy->Draw();
	}

	// 射撃モード中のみ予測線を表示
	if (m_nScene == ShotMode)
	{
		m_pPlayer->DrawPrediction();
	}
	//UIは最後に表示する
	if (m_nScene == ShotMode)
	{
		UIDraw();
	}

	// リセット
	if (IsKeyTrigger(VK_ESCAPE))
	{
		if (m_pEnemy)
		{
			m_pEnemy->Reset();
		}
	}
}

void SceneManeger::UIDepthInit()
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

void SceneManeger::UIDraw()
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
