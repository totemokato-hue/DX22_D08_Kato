#pragma once

//＝＝＝インクルード＝＝＝
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
#include "CameraFollow.h"
#include "wall.h"
#include "Enemy.h"

//＝＝＝列挙型＝＝＝
// 操作モード
enum SceneState
{
	F_CameraMode,
	R_CameraMode,
	L_CameraMode,
	ShotMode,

};

// シーン
enum SceneType
{
	TITLE,	// タイトル
	GAME,	// ゲーム
	CLEAR,	// ゲームクリア（リザルト）
	OVER	// ゲームオーバー
};

//＝＝＝クラス定義＝＝＝
class SceneManeger
{
public:
	//==================================================
	// コンストラクタ・デストラクタ
	//==================================================
	SceneManeger();
	~SceneManeger();

	//==================================================
	// メンバー関数
	//==================================================
	void InitManeger();		// 初期化
	void Destructor();		// デストラクタ（実質）
	void UpdateManeger();	// 更新処理
	void DrawManeger();		// 描画

private:
	//==================================================
	// メンバー変数
	//==================================================
	bool m_isFollowCamera = false;			// 追従カメラのフラグ
	int m_nScene = ShotMode;				// シーン
	Ground* m_pGround;						// 地面オブジェクト
	Goal* m_pGoal;							// ゴールオブジェクト
	Camera* m_pCamera;						// ゲーム中に動かすカメラ
	Player* m_pPlayer;						// プレイヤーオブジェクト
	Model* m_pModel;						// モデル
	ForcusPoint* fPoint;					// 注視点
	TopCamera* m_tCamera;					// カメラ
	CameraPlayer* m_pPlayerCamera;			// 発射前のカメラ
	CameraFollow* m_pFollowCamera;			// 発射後のカメラ
	PowerGauge* m_pPowerGauge;				// パワーゲージのポインタ
	ID3D11DepthStencilState* pUIDepthState; // UI用深度テストの設定のポインタ
	Wall* m_pWall;							// 壁オブジェクト
	Enemy* m_pEnemy;						// 敵オブジェクト

	//==================================================
	// メンバ関数
	//==================================================
	void UIDepthInit();		// UI用深度テストの初期化
	void UIDraw();			// UIの表示
};