#pragma once

#include <DirectXMath.h>
#include "Shader.h"
#include "MeshBuffer.h"
#include "Model.h"
#include "camera.h"

class Player {
private:
	Model* m_pModel;//モデル情報
	Camera* m_pCamera;//ボールを追いかけるカメラの情報
	DirectX::XMFLOAT3 m_pos; //座標  
	DirectX::XMFLOAT3 m_move;//プレイヤー移動量
	DirectX::XMFLOAT3 m_oldmove;//プレイヤー過去移動量
	DirectX::XMFLOAT3 m_rotate;//プレイヤー回転量
	DirectX::XMFLOAT3 basePos;//プレイヤーを飛ばす場所の基準
	float				m_tilt;//プレイヤー傾き
	float				m_angle;//プレイヤー角度
	bool				m_isStop;//プレイヤーの停止判定
	bool				m_isGround;//地面接地判定
	int					m_shotStep;//プレイヤーの処理手順
	float				m_shotPower;//プレイヤーの打ち出し強さ
	/*float m_Scale[3];*/
	float m_time; //経過時間
	bool plus;
public:
	Player();
	~Player();

	//更新処理
	void Update();

	//描画処理
	void Draw();

	void initialize();

	void SetCamera(Camera* pCamera);
	DirectX::XMFLOAT3 GetPos() { return m_pos; }
	float GetPower() { return m_time; }

	void UpdateIdle();
	void UpdateAngle();
	void UpdatePower();
	void UpdateShot();
	void UpdateMove();

	//座標設定
	void SetPos(float x, float y, float z);
	/*void SetScale(float x, float y, float z);*/
};