
#include "Ground.h"
#include "Scene.h"
#include "Goal.h"
#include "camera.h"
#include "player.h"
#include "ShaderList.h"
#include "PowerGauge.h"
#include "ForcusPoint.h"
#include "TopCamera.h"
#include "CameraDebug.h"
#include "CameraPlayer.h"
#include "wall.h"
#pragma once
enum SceneState
{
	F_CameraMode,
	R_CameraMode,
	L_CameraMode,
	ShotMode,

};

class SceneManeger
{
public:

	SceneManeger();
	~SceneManeger();
	void InitManeger();
	void Destructor();
	void UpdateManeger();
	void DrawManeger();

private:
	//==================================================
	// メンバ変数
	//==================================================
	int m_nScene = ShotMode;
	Ground* m_pGround;//地面オブジェクト
	Goal* m_pGoal;//ゴールオブジェクト
	Camera* m_pCamera;//ゲーム中に動かすカメラ
	Player* m_pPlayer;//プレイヤーオブジェクト
	Model* m_pModel;
	ForcusPoint* fPoint;
	TopCamera* m_tCamera;
	PowerGauge* m_pPowerGauge;				// パワーゲージのポインタ
	ID3D11DepthStencilState* pUIDepthState; // UI用深度テストの設定のポインタ
	Wall* m_pWall;//壁オブジェクト

	//==================================================
	// メンバ関数
	//==================================================
	void UIDepthInit();		// UI用深度テストの初期化
	void UIDraw();			// UIの表示
};