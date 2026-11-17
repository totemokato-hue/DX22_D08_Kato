#include "Ground.h"
#include "Geometory.h"
#include "ShaderList.h"

//==== コンストラクタ ====
Ground::Ground()
	:m_pModel(nullptr)
	, m_pos(0.0f, 0.0f, 0.0f)
	, m_scale(1.0f, 1.0f, 1.0f)
{
	m_pModel = new Model();
	if (!m_pModel->Load("Assets/Model/tileLarge_desert.fbx", 0.5f)) {  //倍率と反転は省略可
		MessageBox(NULL, "モデルの読み込み失敗", "エラー", MB_OK);
	}

}

//==== デストラクタ ====
Ground::~Ground()
{
	if (m_pModel) {
		delete m_pModel;
		m_pModel = nullptr;
	}

}

//==== 更新処理 ====
void Ground::Update()
{

}

//==== 描画処理 ====
void Ground::Draw()
{
	if (m_pModel) {

		//モデルを表示するためのワールド行列を計算
		DirectX::XMFLOAT4X4 fworld;
		DirectX::XMMATRIX world;

		DirectX::XMMATRIX T = DirectX::XMMatrixTranslation(m_pos.x, m_pos.y, m_pos.z);
		DirectX::XMMATRIX S = DirectX::XMMatrixScaling(m_scale.x, m_scale.y, m_scale.z);
		world = S * T;
		world = DirectX::XMMatrixTranspose(world);
		DirectX::XMStoreFloat4x4(&fworld, world);

		//シェーダーに必要なデータを設定
		ShaderList::SetWorld(fworld);
		

		//モデルに使用する各種シェーダーを設定
		m_pModel->SetVertexShader(ShaderList::GetVS(ShaderList::VS_WORLD));
		m_pModel->SetPixelShader(ShaderList::GetPS(ShaderList::PS_LAMBERT));

		//メッシュ別にモデルを表示
		for (int i = 0; i < m_pModel->GetMeshNum(); ++i) {

			//モデルのメッシュを取得
			const Model::Mesh* mesh = m_pModel->GetMesh(i);

			//メッシュに割り当てられているマテリアルを取得
			Model::Material material = *m_pModel->GetMaterial(mesh->materialID);

			//環境光
			material.ambient.x = 0.7f;  //赤
			material.ambient.y = 0.7f;  //緑
			material.ambient.z = 0.7f;  //青

			//material.specular.x = 0.0f;
			//material.specular.y = 0.0f;
			//material.specular.z = 0.0f;

			//シェーダーへマテリアルを設定
			ShaderList::SetMaterial(material);

			//モデルの描画(内部的に一括で行っていた描画処理を、メッシュごとの描画処理に変更)
			m_pModel->Draw(i);
		}
	}

}

//==== 座標の設定 ====
void Ground::SetPos(float x, float y, float z)
{
	m_pos.x = x;
	m_pos.y = y;
	m_pos.z = z;
}

//==== 拡大率の設定 ====
void Ground::SetScale(float x, float y, float z)
{
	m_scale.x = x;
	m_scale.y = y;
	m_scale.z = z;
}

//==== 座標の受け渡し ====	
DirectX::XMFLOAT3 Ground::GetPos()
{
	return m_pos;
}
