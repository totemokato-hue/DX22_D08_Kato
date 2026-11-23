/**
* @file		GameManager.cpp
* @brief	ゲームシステムの管理
* @author	伊奈拓杜
* @date		2026/11/22 (日)
* 
* @details
* 
* @note
*/

//＝＝＝インクルード＝＝＝
#include "GameManager.h"

// コンストラクタ
GameManager::GameManager()
    : m_gameState(GameState::PLAY)
{
}

// デストラクタ
GameManager::~GameManager()
{

}

// ゲームクリア
void GameManager::GameClear()
{
    if (m_gameState != GameState::PLAY)
        return;

    m_gameState = GameState::CLEAR;
}

// ゲームオーバー
void GameManager::GameOver()
{
    if (m_gameState != GameState::PLAY)
        return;

    m_gameState = GameState::OVER;
}

// 状態の初期化
void GameManager::Reset()
{
    m_gameState = GameState::PLAY;
}

// クリア確認
bool GameManager::IsGameClear() const
{
    return m_gameState == GameState::CLEAR;
}

// ゲームオーバー確認
bool GameManager::IsGameOver() const
{
    return m_gameState == GameState::OVER;
}