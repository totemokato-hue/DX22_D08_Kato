#ifndef __SCENE_GAME_H__
#define __SCENE_GAME_H__
#include "Ground.h"
#include "Scene.h"
#include "Goal.h"
#include "camera.h"
#include "player.h"
#include "ShaderList.h"
#include "PowerGauge.h"
class SceneGame : public Scene
{
public:
	SceneGame();
	~SceneGame();
	void Update() final;
	void Draw() final;

private:
	//==================================================
	// メンバ変数
	//==================================================
	Ground* m_pGround;//地面オブジェクト
	Goal* m_pGoal;//ゴールオブジェクト
	Camera* m_pCamera;//ゲーム中に動かすカメラ
	Player* m_pPlayer;//プレイヤーオブジェクト
	Model* m_pModel;
	PowerGauge* m_pPowerGauge;				// パワーゲージのポインタ
	ID3D11DepthStencilState* pUIDepthState; // UI用深度テストの設定のポインタ

	//==================================================
	// メンバ関数
	//==================================================
	void UIDepthInit();		// UI用深度テストの初期化
	void UIDraw();			// UIの表示

};

#endif // __SCENE_GAME_H__