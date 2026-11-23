#pragma once

//＝＝＝インクルード＝＝＝
#include "GameManager.h"
#include "SceneResult.h"
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
// 現在のシーン
enum class SceneType
{
	SCENE_TITLE,	// タイトル
	SCENE_GAME,		// ゲームプレイ
	SCENE_RESULT	// 結果
};

// シーン内の状態
enum SceneState
{
	F_CameraMode,
	R_CameraMode,
	L_CameraMode,
	ShotMode,
};

//＝＝＝クラス宣言＝＝＝
/**
* @brief	シーンの管理
*/
class SceneManeger
{
public:
	//==================================================
	// コンストラクタ・デストラクタ
	//==================================================
	SceneManeger();		// コンストラクタ
	~SceneManeger();	// デストラクタ

	//==================================================
	// メンバ関数
	//==================================================
	void InitManeger();						// 初期化
	void Destructor();						// 終了
	void UpdateManeger();					// 更新
	void DrawManeger();						// 描画
	void ChangeScene(SceneType nextScene);	// シーン遷移

private:
	//==================================================
	// メンバ変数
	//==================================================
	SceneType m_sceneType = SceneType::SCENE_GAME;	// 現在のシーン
	bool m_isFollowCamera = false;					// 追従カメラのフラグ
	int m_nScene = ShotMode;						// シーン
	GameManager* m_pGameManager;					// ゲームマネージャー
	SceneResult* m_pSceneResult;					// リザルトシーン
	Ground* m_pGround;								// 地面オブジェクト
	Goal* m_pGoal;									// ゴールオブジェクト
	Camera* m_pCamera;								// ゲーム中に動かすカメラ
	Player* m_pPlayer;								// プレイヤーオブジェクト
	Model* m_pModel;								// モデル
	ForcusPoint* fPoint;							// 注視点
	TopCamera* m_tCamera;							// カメラ
	CameraPlayer* m_pPlayerCamera;					// 発射前のカメラ
	CameraFollow* m_pFollowCamera;					// 発射後のカメラ
	PowerGauge* m_pPowerGauge;						// パワーゲージのポインタ
	ID3D11DepthStencilState* pUIDepthState;			// UI用深度テストの設定のポインタ
	Wall* m_pWall;									// 壁オブジェクト
	Enemy* m_pEnemy;								// 敵オブジェクト

	//==================================================
	// メンバ関数
	//==================================================
	void UIDepthInit();		// UI用深度テストの初期化
	void UIDraw();			// UIの表示
	void RestartGame();		// リスタート
};