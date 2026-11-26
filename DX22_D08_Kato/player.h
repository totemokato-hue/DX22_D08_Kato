#pragma once

#include <DirectXMath.h>
#include "Shader.h"
#include "MeshBuffer.h"
#include "Model.h"
#include "camera.h"
#include "Collision.h"

class Player {
private:
	Model* m_pModel;//モデル情報
	Camera* m_pCamera;//ボールを追いかけるカメラの情報
	DirectX::XMFLOAT3 m_pos; //座標  
	DirectX::XMFLOAT3 m_hitpos; //ヒット座標  
	DirectX::XMFLOAT3 m_move;//プレイヤー移動量
	DirectX::XMFLOAT3 m_oldmove;//プレイヤー過去移動量
	DirectX::XMFLOAT3 m_rotate;//プレイヤー回転量
	DirectX::XMFLOAT3 basePos;//プレイヤーを飛ばす場所の基準
	float				m_tilt;//プレイヤー傾き
	float				m_angle;//プレイヤー角度
	bool				m_isStop;//プレイヤーの停止判定
	bool				m_isHit;//地面接地判定
	int					m_shotStep;//プレイヤーの処理手順
	float				m_shotPower;//プレイヤーの打ち出し強さ
	/*float m_Scale[3];*/
	float m_time; //経過時間
	bool plus;
	Collision::Box m_collision;//ボックスの当たり判定

public:
	Player();
	~Player();

	//更新処理
	void Update();

	//描画処理
	void Draw();

	// 予測線の描画
	void DrawPrediction();

	//最大の予測線の描画
	void MaxDrawPrediction();

	void initialize();

	void SetCamera(Camera* pCamera);
	DirectX::XMFLOAT3 GetPos() { return m_pos; }
	float GetPower() { return m_time; }

	int GetScene();
	void UpdateIdle();
	void UpdateAngle();
	void UpdatePower();
	void UpdateShot();
	void UpdateMove();

	void Hit();

	//座標設定
	void SetPos(float x, float y, float z);

	//当たり判定の取得
	const Collision::Box& GetCollisionBox() { return m_collision; }

	bool IsFlying() const;
	DirectX::XMFLOAT3 GetVelocity() const;
	bool IsAiming() const;  // 発射前の状態か判定
	/*void SetScale(float x, float y, float z);*/
private:
	// 発射時の初速度を計算
	DirectX::XMFLOAT3 GetShotVelocity(float power) const;

	// 放物線の座標を計算
	std::vector<DirectX::XMFLOAT3> CalculatePredictionPoints(float power,bool toLanding = false) const;
};