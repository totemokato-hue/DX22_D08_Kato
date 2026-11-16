/**
* @file		PoewrGauge.cpp
* @brief	パワーゲージの実装
* @author	伊奈　拓杜
* @date		2026/11/16 (月)
* 
* @details	・パワーゲージの往復
*			・パワーゲージの初期化
*			・パワーゲージの表示、非表示、停止
			・パワーのゲッター
* 
* @note		・Input.hを必ずおいておく事
*			・カメラをインクルードしておくこと
*			・コンストラクタに画像のパスを設定すること
*			・DRAWするときは必ず震度テストを一時的に無効化すること
*			
* @par		編集履歴
*			2026/11/16 (月) [伊奈]
			・基本的な実装
*/

//＝＝＝インクルード＝＝＝
#include "PowerGauge.h"

#include "Input.h"

//＝＝＝定数・マクロ定義＝＝＝



/**
* @brief	コンストラクタ
*/
PowerGauge::PowerGauge()
	:m_bPowerSign(true),
	m_bGaugeDisplay(true),
	m_bGaugeMove(true),
	m_fPower(0.0f),
	m_pGaugeTexture(nullptr),
	m_pNeedleTexture(nullptr)
{
	// テクスチャ生成
	m_pGaugeTexture = new Texture();
	m_pNeedleTexture = new Texture();

	// 画像読み込み
	HRESULT ghr = m_pGaugeTexture->Create(
		"Assets/Texture/Gauge.png"
	);

	HRESULT nhr = m_pNeedleTexture->Create(
		"Assets/Texture/Needle.png"
	);

	if (FAILED(ghr))
	{
		delete m_pGaugeTexture;
		m_pGaugeTexture = nullptr;

		MessageBox(
			NULL,
			"ゲージ画像の読み込みに失敗しました",
			"エラー",
			MB_OK | MB_ICONERROR
		);
	}

	if (FAILED(nhr))
	{
		delete m_pNeedleTexture;
		m_pNeedleTexture = nullptr;

		MessageBox(
			NULL,
			"針画像の読み込みに失敗しました",
			"エラー",
			MB_OK | MB_ICONERROR
		);
	}
}

/**
* @brief	デストラクタ
*/
PowerGauge::~PowerGauge()
{
	delete m_pGaugeTexture;
	delete m_pNeedleTexture;
	m_pGaugeTexture = nullptr;
	m_pNeedleTexture = nullptr;
}

/**
* @brief	初期化
*/
void PowerGauge::Init()
{

}

/**
* @brief	更新処理
*/
void PowerGauge::Update()
{
	// ゲージの移動フラグが有効なら現在の符号に応じてパワーを増減
	if (m_bGaugeMove)
	{
		if (m_bPowerSign)
			m_fPower += CHARGE_POWER;
		else
			m_fPower -= CHARGE_POWER;
	}

	// 範囲を超えていたら調整し符号を反転
	// 最大
	if (m_fPower >= MAX_POWER)
	{
		m_fPower = MAX_POWER;
		m_bPowerSign = false;
	}
	// 最小
	if (m_fPower <= 0)
	{
		m_fPower = 0;
		m_bPowerSign = true;
	}
}

/**
* @brief	描画処理
*/
void PowerGauge::Draw()
{
	// 表示フラグが有効な間のみ表示する
	if (!m_bGaugeDisplay || !m_pGaugeTexture || !m_pNeedleTexture) return;

	// ワールド行列
	DirectX::XMMATRIX world = DirectX::XMMatrixIdentity();

	// ビュー行列
	DirectX::XMMATRIX view = DirectX::XMMatrixIdentity();

	// 射影行列
	DirectX::XMMATRIX projection =DirectX::XMMatrixOrthographicOffCenterLH(0.0f, 1280.0f,0.0f, 720.0f,0.0f, 1.0f);

	// 行列を格納するための変数
	DirectX::XMFLOAT4X4 matWorld;
	DirectX::XMFLOAT4X4 matView;
	DirectX::XMFLOAT4X4 matProjection;

	// 行列を格納
	DirectX::XMStoreFloat4x4(
		&matWorld,
		DirectX::XMMatrixTranspose(world)
	);

	DirectX::XMStoreFloat4x4(
		&matView,
		DirectX::XMMatrixTranspose(view)
	);

	DirectX::XMStoreFloat4x4(
		&matProjection,
		DirectX::XMMatrixTranspose(projection)
	);

	// Spriteに設定
	Sprite::SetWorld(matWorld);
	Sprite::SetView(matView);
	Sprite::SetProjection(matProjection);

	// 共通設定
	Sprite::SetUVPos({ 0.0f, 0.0f });
	Sprite::SetUVScale({ 1.0f, 1.0f });
	Sprite::SetColor({ 1.0f, 1.0f, 1.0f, 1.0f });

	// 背景ゲージ
	Sprite::SetTexture(m_pGaugeTexture);
	Sprite::SetOffset({ 640.0f, 100.0f });
	Sprite::SetSize({ 300.0f, 30.0f });
	Sprite::Draw();

	// パワーの割合
	float rate = m_fPower / MAX_POWER;

	// 針のX座標
	float needleX = 490.0f + 300.0f * rate;

	// 針を描画
	Sprite::SetTexture(m_pNeedleTexture);
	Sprite::SetOffset({ needleX, 100.0f });
	Sprite::SetSize({ 5.0f, 45.0f });
	Sprite::Draw();
}

/**
* @brief	ゲージの表示
*/
void PowerGauge::DisplayOn()
{
	m_bGaugeDisplay = true;
	m_bGaugeMove = true;
}

/**
* @brief	ゲージの非表示
*/
void PowerGauge::DisplayOff()
{
	m_bGaugeDisplay = false;
}

/**
* @brief	ゲージのストップ
*/
void PowerGauge::Stop()
{
	m_bGaugeMove = false;
}

/**
* @brief	現在のゲージの取得
* @return	float 現在のパワー
*/
float PowerGauge::GetPower()
{
	return m_fPower;
}