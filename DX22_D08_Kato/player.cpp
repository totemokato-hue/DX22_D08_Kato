#include "Player.h"
#include "Geometory.h"
#include "Defines.h"
#include "Input.h"

Player::Player()
	: m_pos{ 0.0f,0.0f,0.0f }
	, m_time(0.0f)
	, m_move{ 0.0f,0.0f,0.0f }
{
}

Player::~Player()
{
}

void Player::Update()
{
	m_time += 1.0 / FPS;


}

void Player::Draw()
{
	//変換行列の計算
	DirectX::XMMATRIX T = DirectX::XMMatrixTranslation(m_pos[0], m_pos[1], m_pos[2]);
	DirectX::XMMATRIX Rx = DirectX::XMMatrixRotationX(0.0f);
	DirectX::XMMATRIX Ry = DirectX::XMMatrixRotationY(0.0f);
	DirectX::XMMATRIX Rz = DirectX::XMMatrixRotationZ(0.0f);
	DirectX::XMMATRIX R = Rx * Ry * Rz; //回転行列のみをかけ合わせて格納
	DirectX::XMMATRIX S = DirectX::XMMatrixScaling(1.0f, 2.0f, 1.0f);
	DirectX::XMMATRIX mat = S * R * T;

	//変換行列をGPUに渡すための前処理
	mat = DirectX::XMMatrixTranspose(mat);
	DirectX::XMFLOAT4X4 fMat;
	DirectX::XMStoreFloat4x4(&fMat, mat);

	//描画処理
	Geometory::SetWorld(fMat);
	Geometory::DrawBox();
}

void Player::SetPos(float x, float y, float z)
{
	m_pos[0] = x;
	m_pos[1] = y;
	m_pos[2] = z;
}
