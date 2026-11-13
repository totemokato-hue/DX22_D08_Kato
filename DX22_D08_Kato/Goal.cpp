#include "Goal.h"
#include "Geometory.h"
#include "Defines.h"
Goal::Goal()
	: m_time(0.0f)
	, m_pos{ 0.0f, 0.0f, 0.0f }
{
}

Goal::~Goal()
{
}

void Goal::Update()
{
	m_time += 1.0 / FPS;
}

void Goal::Draw()
{
	//•ÏŠ·s—ñ‚ÌŒvZ
	DirectX::XMMATRIX T = DirectX::XMMatrixTranslation(m_pos[0], m_pos[1], m_pos[2]);
	DirectX::XMMATRIX Rx = DirectX::XMMatrixRotationX(m_time);
	DirectX::XMMATRIX Ry = DirectX::XMMatrixRotationY(m_time);
	DirectX::XMMATRIX Rz = DirectX::XMMatrixRotationZ(m_time);
	DirectX::XMMATRIX R = Rx * Ry * Rz; //‰ñ“]s—ñ‚Ì‚İ‚ğ‚©‚¯‡‚í‚¹‚ÄŠi”[
	DirectX::XMMATRIX S = DirectX::XMMatrixScaling(0.5f, 0.5f, 0.5f);
	DirectX::XMMATRIX mat = S * R * T;

	//•ÏŠ·s—ñ‚ğGPU‚É“n‚·‚½‚ß‚Ì‘Oˆ—
	mat = DirectX::XMMatrixTranspose(mat);
	DirectX::XMFLOAT4X4 fMat;
	DirectX::XMStoreFloat4x4(&fMat, mat);

	//•`‰æˆ—
	Geometory::SetWorld(fMat);
	Geometory::DrawBox();
}

void Goal::SetPos(float x, float y, float z)
{
	m_pos[0] = x;
	m_pos[1] = y;
	m_pos[2] = z;
}

//void Goal::SetScale(float x, float y, float z)
//{
//	m_Scale[0];
//	m_Scale[1];
//	m_Scale[2];
//}

