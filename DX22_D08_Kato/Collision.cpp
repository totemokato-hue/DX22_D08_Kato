#include "Collision.h"

Collision::Result Collision::Hit(Box a, Box b)
{
	//結果を格納する変数を準備
	Result out = {};

	//計算用の型に変換
	DirectX::XMVECTOR vPosA = DirectX::XMLoadFloat3(&a.center);
	DirectX::XMVECTOR vPosB = DirectX::XMLoadFloat3(&b.center);
	DirectX::XMVECTOR vSizeA = DirectX::XMLoadFloat3(&a.size);
	DirectX::XMVECTOR vSizeB = DirectX::XMLoadFloat3(&b.size);

	//ボックスの半分のサイズを取得
	vSizeA = DirectX::XMVectorScale(vSizeA, 0.5f);
	vSizeB = DirectX::XMVectorScale(vSizeB, 0.5f);

	//ボックスの各軸の最大値、最小値を取得
	DirectX::XMVECTOR vMaxA = DirectX::XMVectorAdd(vPosA, vSizeA);
	DirectX::XMVECTOR vMinA = DirectX::XMVectorSubtract(vPosA, vSizeA);
	DirectX::XMVECTOR vMaxB = DirectX::XMVectorAdd(vPosB, vSizeB);
	DirectX::XMVECTOR vMinB = DirectX::XMVectorSubtract(vPosB, vSizeB);
	DirectX::XMFLOAT3 maxA, minA, maxB, minB;
	DirectX::XMStoreFloat3(&maxA, vMaxA);
	DirectX::XMStoreFloat3(&minA, vMinA);
	DirectX::XMStoreFloat3(&maxB, vMaxB);
	DirectX::XMStoreFloat3(&minB, vMinB);

	//判定前はヒットしていないとみなす
	out.isHit = false;

	//ボックスの各軸同士の関係から当たり判定を行う
	if (maxA.x >= minB.x && minA.x <= maxB.x) {
		if (maxA.y >= minB.y && minA.y <= maxB.y) {
			if (maxA.z >= minB.z && minA.z <= maxB.z) {
				//ヒット
				out.isHit = true;
			}
		}
	}

	return out;
}

Collision::Result Collision::Hit(Sphere a, Sphere b)
{
	//結果を格納する変数を準備
	Result out = {};

	//計算用の型に変換
	DirectX::XMVECTOR vPosA = DirectX::XMLoadFloat3(&a.center);
	DirectX::XMVECTOR vPosB = DirectX::XMLoadFloat3(&b.center);

	//２点の位置から距離からベクトルを計算
	DirectX::XMVECTOR vDist = DirectX::XMVectorSubtract(vPosA, vPosB);

	//距離ベクトルからの長さを取得
	DirectX::XMVECTOR vLen = DirectX::XMVector3Length(vDist);
	float length;
	DirectX::XMStoreFloat(&length, vLen);
	//球の半径と２点間の距離から球の当たり判定を計算
	out.isHit = length <= a.radius + b.radius;

	return out;
}
void Collision::Draw(Box box)
{
	//表示のための行列を計算
	DirectX::XMMATRIX S = DirectX::XMMatrixScaling(box.size.x, box.size.y, box.size.z);
	DirectX::XMMATRIX T = DirectX::XMMatrixTranslation(box.center.x, box.size.y, box.size.z);
}

