/**
* @file		PowerGauge.h
* @brief	パワーゲージクラスの実装
* @author	伊奈　拓杜
* @date		2026/11/16 (月)
* 
* @details	・パワークラス
* 
* @note		・必ずSprite.hが必要
*			・constexprで定数を変更可能
*
* @par		編集履歴
*			2026/11/16 (月) [伊奈]
			・基本的な実装
*/

#pragma once

//＝＝＝インクルード＝＝＝
#include "Sprite.h"
#include "player.h"


class PowerGauge
{
public:
	//==================================================
	// コンストラクタ・デストラクタ
	//==================================================
	PowerGauge();
	~PowerGauge();

	//==================================================
	// メンバ関数
	//==================================================
	void Init();
	void Update();
	void Draw();
	void DisplayOn();
	void DisplayOff();
	void Stop();
	float GetPower();
	void SetPlayer(Player* player) { m_pPlayer = player; }


private:
	//==================================================
	// 定数定義
	//==================================================
	static constexpr float MAX_POWER = 60.0f;	// 最大パワー
	static constexpr float CHARGE_POWER = 1.0f;	// パワーの変動量

	//==================================================
	// メンバ変数
	//==================================================
	bool m_bPowerSign;			// パワー変動の符号
	bool m_bGaugeDisplay;		// ゲージの表示フラグ
	bool m_bGaugeMove;			// ゲージの移動フラグ
	float m_fPower;				// パワー
	Texture* m_pGaugeTexture;	// ゲージのテクスチャのポインタ
	Texture* m_pNeedleTexture;	// 矢印のテクスチャのポインタ
	Player* m_pPlayer;			//パワーを決めるプレイヤー


	//==================================================
	// メンバ関数
	//==================================================

};