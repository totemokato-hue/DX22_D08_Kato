#include "CameraDebug.h"

CameraDebug::CameraDebug()
	:m_radXZ(0.0f),m_radY(0.0f),m_radius(20.0f)
{

}

CameraDebug::~CameraDebug()
{
}

void CameraDebug::Update()
{
	//前
	if (IsKeyPress(VK_UP))
	{
		m_look.z += 0.3;
	}

	//後ろ
	if (IsKeyPress(VK_DOWN))
	{
		m_look.z -= 0.3;
	}

	//右
	if (IsKeyPress(VK_RIGHT))
	{
		m_look.x += 0.3;
	}

	//左
	if (IsKeyPress(VK_LEFT))
	{
		m_look.x -= 0.3;
	}

	//上
	if (IsKeyPress(VK_SHIFT))
	{
		m_look.y += 0.1;
	}

	//下
	if (IsKeyPress(VK_CONTROL))
	{
		m_look.y -= 0.1;
	}

	//カメラ位置の移動
	//回り込みの処理
	if (IsKeyPress('A'))
	{
		m_radXZ += 0.5;
    }
	if (IsKeyPress('D'))
	{
		m_radXZ -= 0.5;
	}
	if (IsKeyPress('W'))
	{
		m_radY += 0.5;
	}
	if (IsKeyPress('S'))
	{
		m_radY -= 0.5;
	}
	//if (IsKeyPress(VK_SPACE))
	//{
	//	m_radXZ = 0;
	//}

	//カメラの距離を変える処理
	if (IsKeyPress('Q')) { m_radius += 0.5; }
	if (IsKeyPress('E')) { m_radius -= 0.5; }
	m_pos.x = cosf(DirectX::XMConvertToRadians(m_radY)) * -sinf(DirectX::XMConvertToRadians(m_radXZ)) * m_radius + m_look.x;
	m_pos.y = sinf(DirectX::XMConvertToRadians(m_radY)) * m_radius + m_look.y;
	m_pos.z = cosf(DirectX::XMConvertToRadians(m_radY)) * -cosf(DirectX::XMConvertToRadians(m_radXZ)) * m_radius + m_look.z;
}
