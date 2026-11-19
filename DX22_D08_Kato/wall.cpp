#include "wall.h"
#include "Geometory.h"
#include "ShaderList.h"

Wall::Wall()
	:m_pModel(nullptr)
	, m_pos(0.0f, 0.0f, 0.0f)
	, m_scale(1.0f, 1.0f, 1.0f)
{
}

Wall::~Wall()
{
}

void Wall::Update()
{
}

void Wall::Draw()
{
	//変換行列の計算
	DirectX::XMMATRIX T = DirectX::XMMatrixTranslation(m_pos.x, m_pos.y, m_pos.z);
	DirectX::XMMATRIX S = DirectX::XMMatrixScaling(m_scale.x, m_scale.y, m_scale.z);
	DirectX::XMMATRIX mat = S * T;

	//変換行列をGPUに渡すための前処理
	mat = DirectX::XMMatrixTranspose(mat);
	DirectX::XMFLOAT4X4 fMat;
	DirectX::XMStoreFloat4x4(&fMat, mat);

	//描画処理
	Geometory::SetWorld(fMat);
	Geometory::DrawBox();
}

void Wall::SetPos(float x, float y, float z)
{
	m_pos.x = x;
	m_pos.y = y;
	m_pos.z = z;
}

void Wall::SetScale(float x, float y, float z)
{
	m_scale.x = x;
	m_scale.y = y;
	m_scale.z = z;
}
