#include "Enemy.h"
#include "ShaderList.h"
#include "Geometory.h"

using namespace DirectX;

Enemy::Enemy()
    : m_pos(0.0f, 0.0f, 0.0f)
    , m_scale(1.0f, 1.0f, 1.0f)
    , m_collision{
        XMFLOAT3(0.0f, 0.0f, 0.0f),
        XMFLOAT3(1.0f, 1.0f, 1.0f)
    }
    , m_isAlive(true)
    , m_pModel(nullptr)
{

    m_pModel = new Model();

    if (!m_pModel->Load("Assets/Model/box1.fbx", 1.0f, Model::None))
    {
        MessageBox(NULL, "error", "player model failed", MB_OK);
    }
}

Enemy::~Enemy()
{
    if (m_pModel)
    {
        delete m_pModel;
        m_pModel = nullptr;
    }
}

void Enemy::Update()
{
    // 動かない敵なので更新処理は不要
}

void Enemy::Draw()
{
    // 敵が消えている、またはモデルがない場合は描画しない
    if (!m_isAlive || m_pModel == nullptr)
    {
        return;
    }

    // 拡大行列
    DirectX::XMMATRIX S = DirectX::XMMatrixScaling(
        m_scale.x,
        m_scale.y,
        m_scale.z
    );

    // 移動行列
    DirectX::XMMATRIX T = DirectX::XMMatrixTranslation(
        m_pos.x,
        m_pos.y,
        m_pos.z
    );

    // ワールド行列
    DirectX::XMMATRIX world = S * T;

    // XMMATRIXからXMFLOAT4X4に変換
    DirectX::XMFLOAT4X4 fworld;

    DirectX::XMStoreFloat4x4(
        &fworld,
        DirectX::XMMatrixTranspose(world)
    );

    // ワールド行列を設定
    ShaderList::SetWorld(fworld);

    // 頂点シェーダー
    m_pModel->SetVertexShader(
        ShaderList::GetVS(ShaderList::VS_WORLD)
    );

    // ピクセルシェーダー
    m_pModel->SetPixelShader(
        ShaderList::GetPS(ShaderList::PS_LAMBERT)
    );

    // モデルを描画
    for (int i = 0; i < m_pModel->GetMeshNum(); i++)
    {
        const Model::Mesh* mesh = m_pModel->GetMesh(i);

        Model::Material material =
            *m_pModel->GetMaterial(mesh->materialID);

        ShaderList::SetMaterial(material);

        m_pModel->Draw(i);
    }
}
void Enemy::SetPos(float x, float y, float z)
{
    m_pos = XMFLOAT3(x, y, z);
    m_collision.center = m_pos;
}

void Enemy::SetScale(float x, float y, float z)
{
    m_scale = XMFLOAT3(x, y, z);
    m_collision.size = m_scale;
}

void Enemy::Hit()
{
    // 衝突したら消える
    m_isAlive = false;
}

void Enemy::Reset()
{
    m_isAlive = true;
}
