#pragma once
#include <DirectXMath.h>
#include "Model.h""
#include "Camera.h"

class Wall {
private:
	Model* m_pModel;    //モデル情報
	DirectX::XMFLOAT3 m_pos;        //座標
	DirectX::XMFLOAT3 m_scale;      //拡大率

public:
	Wall();
	~Wall();

	//更新処理
	void Update();

	//描画処理
	void Draw();

	//設定
	void SetPos(float x, float y, float z);
	void SetScale(float x, float y, float z);

	//座標取得
	DirectX::XMFLOAT3 GetPos();
};