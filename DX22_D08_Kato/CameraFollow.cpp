/**
* @file		CameraFollow.cpp
* @brief	プレイヤーに追従するカメラ
* @author	伊奈拓杜
* @date		2026/11/20 (金)
* 
* @details
* 
* @note
*
* @par      2026/11/20 (金) [伊奈]
*           ・ファイル新規作成
*           ・基本実装
*/

//＝＝＝インクルード＝＝＝
#include "CameraFollow.h"

#include <cmath>

CameraFollow::CameraFollow()
    : m_pPlayer(nullptr)
    , m_distance(4.0f)
    , m_height(2.0f)
    , m_direction(0.0f, 0.0f, 1.0f)
{
}

CameraFollow::~CameraFollow()
{
}

void CameraFollow::SetPlayer(Player* pPlayer)
{
    m_pPlayer = pPlayer;
}

void CameraFollow::Update()
{
    if (!m_pPlayer)
    {
        return;
    }

    // プレイヤーの位置と速度を取得
    DirectX::XMFLOAT3 pos = m_pPlayer->GetPos();
    DirectX::XMFLOAT3 velocity = m_pPlayer->GetVelocity();

    // 水平方向の移動速度を取得
    float length = sqrtf(
        velocity.x * velocity.x +
        velocity.z * velocity.z
    );

    // 移動している場合のみ方向を更新
    if (length > 0.0001f)
    {
        m_direction.x = velocity.x / length;
        m_direction.y = 0.0f;
        m_direction.z = velocity.z / length;
    }

    // プレイヤーの後ろにカメラを配置
    m_pos.x = pos.x - m_direction.x * m_distance;
    m_pos.y = pos.y + m_height;
    m_pos.z = pos.z - m_direction.z * m_distance;

    // プレイヤーを見る
    m_look = pos;
}