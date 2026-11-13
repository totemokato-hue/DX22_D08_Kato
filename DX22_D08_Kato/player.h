#pragma once

#include <DirectXMath.h>
#include "Shader.h"
#include "MeshBuffer.h"
class Player {
private:
	float m_pos[3]; //座標  
	/*float m_Scale[3];*/
	float m_time; //アニメーション経過時間
	float m_move[3];//プレイヤー移動量
public:
	Player();
	~Player();

	//更新処理
	void Update();

	//描画処理
	void Draw();

	//座標設定
	void SetPos(float x, float y, float z);
	/*void SetScale(float x, float y, float z);*/
};