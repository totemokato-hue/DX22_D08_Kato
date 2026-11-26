#include "CameraPlayer.h"
#include "Input.h"

CameraPlayer::CameraPlayer()
	: m_radXZ(0.0f), m_radY(0.4f), m_radius(10.0f), m_pPlayer(nullptr)
{
}

CameraPlayer::~CameraPlayer()
{
}

void CameraPlayer::Update()
{
	//プレイヤーの位置を中止店として設定
	m_look = m_pPlayer->GetPos();

	if (IsKeyPress(VK_LEFT))
	{
		m_radXZ += 0.01;
	}
	if (IsKeyPress(VK_RIGHT))
	{
		m_radXZ -= 0.01;
	}
	//if (IsKeyPress('W'))
	//{
	//	m_radY += 0.1;
	//}
	//if (IsKeyPress('S'))
	//{
	//	m_radY -= 0.1;
	//}
	
	m_pos.x = cos(m_radY) * -sin(m_radXZ) * m_radius + m_look.x;
	m_pos.y = sin(m_radY) * m_radius + m_look.y;
	m_pos.z = cos(m_radY) * -cos(m_radXZ) * m_radius + m_look.z;

}
