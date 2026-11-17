//TopCamera.h
#include "TopCamera.h"


TopCamera::TopCamera()
    :m_radXZ(0.0f), m_radY(0.8f), m_radius(4.0f), m_Point(nullptr), m_mode(FRONT)
{

}

TopCamera::~TopCamera()
{
}


void TopCamera::Update()
{
    if (m_Point == nullptr)
    {
        return;
    }

    // 注視点の座標を取得
    m_look = m_Point->GetPos();


    switch (m_mode)
    {
    case FRONT:
        m_radXZ = 0.0f;
        m_radY = 0.8;
        m_radius = 4.0f;
        // 注視点を中心にカメラ位置を計算
        m_pos.x = cosf(m_radY) * -sinf(m_radXZ) * m_radius + m_look.x;
        m_pos.y = sinf(m_radY) * m_radius + m_look.y;
        m_pos.z = cosf(m_radY) * -cosf(m_radXZ) * m_radius + m_look.z;
        break;
    case RIGHT:

        // 注視点を中心にカメラ位置を計算
        m_radXZ = -DirectX::XM_PIDIV2;
        m_radY = 0.4;
        m_radius = 6.0f;
        m_pos.x = cosf(m_radY) * -sinf(m_radXZ) * m_radius + (m_look.x + 3.0);
        m_pos.y = sinf(m_radY) * m_radius + m_look.y;
        m_pos.z = cosf(m_radY) * -cosf(m_radXZ) * m_radius + m_look.z;
        break;

    case LEFT:
        m_radXZ = DirectX::XM_PIDIV2;
        m_radY = 0.4;
        m_radius = 6.0f;

        // 注視点を中心にカメラ位置を計算
        m_pos.x = cosf(m_radY) * -sinf(m_radXZ) * m_radius + (m_look.x - 3.0);
        m_pos.y = sinf(m_radY) * m_radius + m_look.y;
        m_pos.z = cosf(m_radY) * -cosf(m_radXZ) * m_radius + m_look.z;
        break;
    }




}
void TopCamera::SetForcus(ForcusPoint* point)
{
    m_Point = point;
}

void TopCamera::SetMode(ViewMode mode)
{
    m_mode = mode;
}


