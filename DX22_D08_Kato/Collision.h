#pragma once
#include <DirectXMath.h>
#include "Shader.h"
#include "MeshBuffer.h"

class Collision {
public:
	//当たり判定の形状
	//立方体
	struct Box {
		DirectX::XMFLOAT3	center;	//中心座標
		DirectX::XMFLOAT3	size;	//サイズ
	};

	//球
	struct Sphere {
		DirectX::XMFLOAT3	center;	//中心座標
		float				radius;	//半径
	};

	//当たり判定の結果
	struct Result {
		bool				isHit;	//当たったかどうか
		DirectX::XMFLOAT3	pos;	//ヒット位置
		DirectX::XMFLOAT3	dir;	//ヒット方向
	};

public:
	//立方体同士の当たり判定
	static Result Hit(Box a, Box b);

	//球同士の当たり判定
	static Result Hit(Sphere a, Sphere b);

	//ボックスのデバッグ表示
	static void Draw(Box box);
};
