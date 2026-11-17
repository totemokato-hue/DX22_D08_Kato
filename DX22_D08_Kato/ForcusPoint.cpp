//CameraForcus.cpp
#include "ForcusPoint.h"

ForcusPoint::ForcusPoint()
	:m_pos(0.0f, 5.0f, 0.0f), m_tCamera(nullptr)
{
}

ForcusPoint::~ForcusPoint()
{

}

void ForcusPoint::Update(float cameraYaw)
{
	if (!m_tCamera)
	{
		return;
	}

	//カメラの平行移動
	float forward = 0.0f;
	float right = 0.0f;


	//上
	if (IsKeyPress('W'))
	{
		forward = 1.0f;
	}

	//左
	if (IsKeyPress('A'))
	{
		right = -1.0f;
	}

	//後ろ
	if (IsKeyPress('S'))
	{
		forward = -1.0f;
	}

	//右
	if (IsKeyPress('D'))
	{
		right = 1.0f;
	}

	//camearaYaw = ラジアン角
	float S = sinf(cameraYaw);
	float C = cosf(cameraYaw);

	//角度に合わせた移動距離の計算
	m_pos.x += (forward * S + right * C) * CAMERASPEED;
	m_pos.z += (forward * C - right * S) * CAMERASPEED;
}

void ForcusPoint::SetCamera(Camera* fCamera)
{
	m_tCamera = fCamera;
}

void ForcusPoint::Draw()
{
	//DirectX::XMMATRIX bT = DirectX::XMMatrixTranslation(m_pos.x, m_pos.y, m_pos.z);
	//DirectX::XMMATRIX bS = DirectX::XMMatrixScaling(0.4f, 0.4f, 0.4f);
	//DirectX::XMMATRIX bmat = bS * bT;

	////変換行列をGPUに渡すための前処理
	//bmat = DirectX::XMMatrixTranspose(bmat);
	//DirectX::XMFLOAT4X4 fbMat;
	//DirectX::XMStoreFloat4x4(&fbMat, bmat);

	////描画処理
	//Geometory::SetWorld(fbMat);
	//Geometory::DrawBox();
}

DirectX::XMFLOAT3 ForcusPoint::GetPos()
{
	return m_pos;
}
