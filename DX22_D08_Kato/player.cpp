#include "Player.h"
#include "Geometory.h"
#include "Defines.h"
#include "ShaderList.h"
#include "Input.h"

enum eShotStep
{
	SHOT_IDLE = 0,
	SHOT_ANGLE,
	SHOT_POWER,
	SHOT_SHOT,
	SHOT_MOVE,
};

Player::Player()
	: m_pCamera(nullptr)
	, m_pModel(nullptr)
	, m_pos ( 0.0f,0.0f,0.0f )
	, m_move( 0.0f,0.0f,0.0f )
	, m_oldmove( 0.0f,0.0f,0.0f )
	, m_rotate( 0.0f,90.0f,0.0f )
	, basePos( 0.0f,0.0f,0.0f )
	, m_angle(0.0f)
	, m_time(0.0f)
	, m_isStop(true)
	, m_isGround(true)
	, m_shotStep(1)
	, m_shotPower(0.0f)
	, plus(true)
{
	m_pModel = new Model();

	if (!m_pModel->Load("Assets/Model/box1.fbx", 1.0f))
	{
		MessageBox(NULL, "error", "player model failed", MB_OK);
	}
}

Player::~Player()
{
	if (m_pModel)
	{
		delete m_pModel;
		m_pModel = nullptr;
	}
}

void Player::Update()
{

	//カメラが設定されていない場合は処理しない
	if (!m_pCamera) { return; }

	switch (m_shotStep)
	{
	case SHOT_IDLE:		UpdateIdle();	 break;
	case SHOT_ANGLE:	UpdateAngle();	 break;
	case SHOT_POWER:	UpdatePower(); break;
	case SHOT_SHOT:		UpdateShot(); break;
	case SHOT_MOVE:		UpdateMove(); break;
	}


}

void Player::Draw()
{
	if (m_pModel)
	{
		//モデル表示するためのワールド行列を計算
		DirectX::XMFLOAT4X4 fWorld;
		DirectX::XMMATRIX World;
		//変換行列の計算
		DirectX::XMMATRIX T = DirectX::XMMatrixTranslation(m_pos.x, m_pos.y, m_pos.z);
		DirectX::XMMATRIX Rx = DirectX::XMMatrixRotationX(DirectX::XMConvertToRadians(m_rotate.x));
		DirectX::XMMATRIX Ry = DirectX::XMMatrixRotationY(DirectX::XMConvertToRadians(m_rotate.y));
		DirectX::XMMATRIX Rz = DirectX::XMMatrixRotationZ(DirectX::XMConvertToRadians(m_rotate.z));
		DirectX::XMMATRIX R = Rx * Ry * Rz; //回転行列のみをかけ合わせて格納
		DirectX::XMMATRIX S = DirectX::XMMatrixScaling(1.0f, 2.0f, 1.0f);
		//DirectX::XMMATRIX mat = S * R * T;
		World = S * R * T;
		World = DirectX::XMMatrixTranspose(World);
		DirectX::XMStoreFloat4x4(&fWorld, World);

		//シェーダーに必要なデータを設定
		ShaderList::SetWorld(fWorld);
		

		//モデルに使用する各種シェーダーを設定
		m_pModel->SetVertexShader(ShaderList::GetVS(ShaderList::VS_WORLD));
		m_pModel->SetPixelShader(ShaderList::GetPS(ShaderList::PS_LAMBERT));

		//メッシュ別にモデルを表示
		for (int i = 0; i < m_pModel->GetMeshNum(); ++i) {

			//モデルメッシュを取得
			const Model::Mesh* mesh = m_pModel->GetMesh(i);

			//メッシュに割り当てられているマテリアルを取得
			Model::Material material = *m_pModel->GetMaterial(mesh->materialID);

			//シェーダーへマテリアルを設定
			ShaderList::SetMaterial(material);

			//モデルの描画(内部的に一括で行っていた描画処理をメッシュごとの描画処理に変更)
			m_pModel->Draw(i);
		}

		////変換行列をGPUに渡すための前処理
		//mat = DirectX::XMMatrixTranspose(mat);
		//DirectX::XMFLOAT4X4 fMat;
		//DirectX::XMStoreFloat4x4(&fMat, mat);

		////描画処理
		//Geometory::SetWorld(fMat);
		//Geometory::DrawBox();

	}

	DirectX::XMMATRIX bT = DirectX::XMMatrixTranslation(basePos.x, basePos.y, basePos.z);
	DirectX::XMMATRIX bRx = DirectX::XMMatrixRotationX(DirectX::XMConvertToRadians(m_rotate.x));
	DirectX::XMMATRIX bRy = DirectX::XMMatrixRotationY(DirectX::XMConvertToRadians(m_rotate.y));
	DirectX::XMMATRIX bRz = DirectX::XMMatrixRotationZ(DirectX::XMConvertToRadians(m_rotate.z));
	DirectX::XMMATRIX bR = bRx * bRy * bRz; //回転行列のみをかけ合わせて格納
	DirectX::XMMATRIX bS = DirectX::XMMatrixScaling(0.4f, 0.4f, 0.4f);
	DirectX::XMMATRIX bmat = bS * bR * bT;

	//変換行列をGPUに渡すための前処理
	bmat = DirectX::XMMatrixTranspose(bmat);
	DirectX::XMFLOAT4X4 fbMat;
	DirectX::XMStoreFloat4x4(&fbMat, bmat);

	//描画処理
	Geometory::SetWorld(fbMat);
	Geometory::DrawBox();


}

void Player::initialize()
{
	m_pos = { 0.0f, 0.0f, 0.0f };
	m_move = { 0.0f, 0.0f, 0.0f };
	m_oldmove = { 0.0f, 0.0f, 0.0f };
	m_rotate = { 0.0f, 90.0f, 0.0f };
	basePos = { 0.0f, 0.0f, 0.0f };
	m_angle = 0.0f;
	m_time = 0.0f;
	m_isStop = true;
	m_isGround = true;
	m_shotStep = SHOT_ANGLE;
	m_shotPower = 0.0f;
	plus = true;
	Player::SetPos(0.0f, 1.0f, -6.0f);
}

void Player::SetCamera(Camera* pCamera)
{
	m_pCamera = pCamera;
}

void Player::UpdateIdle()
{
	if (IsKeyTrigger(VK_SPACE)) m_shotStep = SHOT_ANGLE;
}

void Player::UpdateAngle()
{
	if (IsKeyTrigger(VK_SPACE))
	{
		m_shotStep = SHOT_POWER;
		m_time = 0.0f;
	}
	if (IsKeyTrigger(VK_BACK)) m_shotStep = SHOT_IDLE;

	if (IsKeyPress('A'))//Aキーで左に回転
	{
		m_rotate.y -= 1.0f;
		if (m_rotate.y < 0.0f)//0°よりは下がらない
			m_rotate.y = 0.0f;
	}

	if (IsKeyPress('D'))//Dキーで右に回転
	{
		m_rotate.y += 1.0f;
		if (m_rotate.y > 180.0f)//180°以上にはならない
			m_rotate.y = 180.0f;
	}

	if (IsKeyPress('W'))//Wキーで上を向く
	{
		m_angle += 1.0f;
		if (m_angle > 90.0f)//90°以上にはならない
			m_angle = 90.0f;
	}

	if (IsKeyPress('S'))//Sキーで下を向く
	{
		m_angle -= 1.0f;
		if (m_angle < 0.0f)//0°以下にはならない
			m_angle = 0.0f;
	}
	//極座標の球
	basePos.x = (m_pos.x + sinf(DirectX::XMConvertToRadians(90.0f - m_angle)) * cosf(DirectX::XMConvertToRadians(m_rotate.y)) * 2.0f) * -1;
	basePos.y = m_pos.y + cosf(DirectX::XMConvertToRadians(90.0f - m_angle)) * 2.0f;
	basePos.z = m_pos.z + sinf(DirectX::XMConvertToRadians(90.0f - m_angle)) * sinf(DirectX::XMConvertToRadians(m_rotate.y)) * 2.0f;

}

void Player::UpdatePower()
{
	if (IsKeyTrigger(VK_SPACE)) m_shotStep = SHOT_SHOT;
	if (IsKeyTrigger(VK_BACK)) m_shotStep = SHOT_ANGLE;

	if (plus)	m_time++;
	else		m_time--;
	if (m_time > 60.0f)
	{
		plus = false;
	}
	if (m_time < 0.0f)
	{
		plus = true;
	}

	m_shotPower = (m_time / 10.0f) + 1.0f;//固定パワー１０＋ゲージ(一秒でマックス)の2倍

}

void Player::UpdateShot()
{
	DirectX::XMVECTOR vBasePos = DirectX::XMLoadFloat3(&basePos);
	DirectX::XMVECTOR vPos = DirectX::XMLoadFloat3(&m_pos);
	DirectX::XMVECTOR vec = DirectX::XMVectorSubtract(vBasePos, vPos);
	vec = DirectX::XMVector3Normalize(vec);
	vec = DirectX::XMVectorScale(vec, m_shotPower);
	DirectX::XMStoreFloat3(&m_move, vec);

	//打ち出し後の情報を設定
	m_isStop = false;		//移動するので停止状態解除
	m_isGround = false;		//飛ぶので一旦地面から離れたとみなす
	m_shotStep = SHOT_MOVE;	//キー入力待ちの手順に戻す

}

void Player::UpdateMove()
{
	//過去移動量を保存
	m_oldmove = m_move;

	//重力
	m_move.y -= GRAVITY * 0.1;
	//移動処理
	m_pos.x += m_move.x / 10.0f;
	m_pos.y += m_move.y / 10.0f;
	m_pos.z += m_move.z / 10.0f;

	if (m_move.y > 0.0f)
	{
		
	}
	else
	{
		
	}
	


	//地面接触判定
	if (m_pos.y < 1.0f)
	{
		m_pos.y = 1.0f;

		m_move = { 0.0f,0.0f,0.0f };
	}

	if (IsKeyTrigger(VK_ESCAPE))
	{
		Player::initialize();
	}
}

void Player::SetPos(float x, float y, float z)
{
	m_pos.x = x;
	m_pos.y = y;
	m_pos.z = z;
}
