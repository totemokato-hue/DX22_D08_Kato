#include "Defines.h"
#include <DirectXMath.h>
#include "Shader.h"
#include "MeshBuffer.h"
#pragma once
class Camera {
protected:
	DirectX::XMFLOAT3 m_pos; //座標
	DirectX::XMFLOAT3 m_look;//注視点
	DirectX::XMFLOAT3 m_up;  //上方ベクトル
	float m_fovy;    //画角
	float m_aspect;  //アスペクト比
	float m_near;    //ニアクリップ
	float m_far;     //ファークリップ
public:
	//コンストラクタ
	Camera();

	//デストラクタ
	virtual ~Camera();

	//ビュー変換行列の取得
	virtual void Update() = 0;
	DirectX::XMFLOAT4X4 GetViewMatrix(bool transpose = true);
	
	DirectX::XMFLOAT4X4 GetProjectionMatrix(bool transpose = true);
	DirectX::XMFLOAT3 GetPos();
	DirectX::XMFLOAT3 GetLook();


};