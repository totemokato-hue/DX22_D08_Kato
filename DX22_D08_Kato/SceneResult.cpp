/**
* @file		SceneResult.cpp
* @brief	リザルトシーンの実装
* @author	伊奈拓杜
* @date		2026/11/23 (月)
* 
* @details	
* 
* @note
* 
* @par		2026/11/23 (月) [伊奈]
*			・ファイル新規作成
*			・基本実装
*/

//＝＝＝インクルード＝＝＝
#include "SceneResult.h"

#include "Input.h"

// コンストラクタ
SceneResult::SceneResult()
{

}

// デストラクタ
SceneResult::~SceneResult()
{

}

// 更新処理
void SceneResult::Update()
{

}

// 描画処理
void SceneResult::Draw()
{

}

// リスタートキー入力の確認
bool SceneResult::IsRestart() const
{
	return IsKeyPress('R');
}