/**
* @file     CameraFollow.h
* @brief    CameraFollowクラス
* @author   伊奈拓杜
* @date     2026/11/20 (金)
* 
* @details  発射時にプレイヤーに追従する専用カメラ
* 
* @note     視点をいじりたい場合はCPPのコンストラクタでいじってください
* 
*/

#pragma once

//＝＝＝インクルード＝＝＝
#include "Camera.h"
#include "Player.h"

//＝＝＝クラス宣言＝＝＝
/**
* @brief    追従カメラ
*/
class CameraFollow : public Camera
{
public:
    //==================================================
    // コンストラクタ・デストラクタ
    //==================================================
    CameraFollow();     // コンストラクタ
    ~CameraFollow();    // デストラクタ

    //==================================================
    // メンバー関数
    //==================================================
    /**
    * @brief    更新処理
    */
    void Update() override;

    /**
    * @brief    プレイヤーの設定
    * @param    Player* pPlayer - プレイヤー
    */
    void SetPlayer(Player* pPlayer);

private:
    //==================================================
    // メンバー変数
    //==================================================
    DirectX::XMFLOAT3 m_direction;  // カメラの水平方向
    float m_distance;               // プレイヤーからの距離
    float m_height;                 // プレイヤーからの高さ
    Player* m_pPlayer;              // プレイヤーのポインター
};
