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
	, m_pos ( 0.0f,1.0f,0.0f )
	, m_move( 0.0f,0.0f,0.0f )
	, m_oldmove( 0.0f,0.0f,0.0f )
	, m_rotate( 0.0f,0.0f,0.0f )
	, m_tilt(0.0f)
	, basePos( 0.0f,0.0f,0.0f )
	, m_angle(20.0f)
	, m_time(0.0f)
	, m_isStop(true)
	, m_isGround(true)
	, m_shotStep(1)
	, m_shotPower(0.0f)
	, plus(true)
{
	m_pModel = new Model();

	if (!m_pModel->Load("Assets/Model/box 2.fbx", 1.0f,Model::None))
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
		DirectX::XMMATRIX Tilt = DirectX::XMMatrixRotationX(DirectX::XMConvertToRadians(m_tilt));

		R = Tilt * R;//プレイヤーを基準に傾ける

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
	//Geometory::DrawBox();


}

void Player::DrawPrediction()
{
	// 放物線上の座標を取得
	const auto points = CalculatePredictionPoints();

	// 描画できる座標がない場合
	if (points.size() < 2)
	{
		return;
	}

	// 予測線の色（水色）
	const DirectX::XMFLOAT4 lineColor(
		1.0f,
		0.0f,
		1.0f,
		1.0f
	);

	// 各座標を線でつなぐ
	for (std::size_t i = 1; i < points.size(); ++i)
	{
		Geometory::AddLine(
			points[i - 1],
			points[i],
			lineColor
		);
	}

	// 線をまとめて描画
	Geometory::DrawLines();
}

void Player::initialize()
{
	m_pos = { 0.0f, 1.0f, 0.0f };
	m_move = { 0.0f, 0.0f, 0.0f };
	m_oldmove = { 0.0f, 0.0f, 0.0f };
	m_rotate = { 0.0f, 0.0f, 0.0f };
	basePos = { 0.0f, 0.0f, 0.0f };
	m_tilt = 0.0f;
	m_angle = 20.0f;
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
		if (m_rotate.y < -90.0f)//-90°よりは下がらない
			m_rotate.y = -90.0f;
	}

	if (IsKeyPress('D'))//Dキーで右に回転
	{
		m_rotate.y += 1.0f;
		if (m_rotate.y > 90.0f)//90°以上にはならない
			m_rotate.y = 90.0f;
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
	basePos.x = (m_pos.x + sinf(DirectX::XMConvertToRadians(90.0f - m_angle)) * cosf(DirectX::XMConvertToRadians(m_rotate.y + 90.0f)) * 2.0f) * -1;
	basePos.y = m_pos.y + cosf(DirectX::XMConvertToRadians(90.0f - m_angle)) * 2.0f;
	basePos.z = m_pos.z + sinf(DirectX::XMConvertToRadians(90.0f - m_angle)) * sinf(DirectX::XMConvertToRadians(m_rotate.y + 90.0f)) * 2.0f;

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
	m_shotStep = SHOT_MOVE;	//ステートの変更

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
		m_tilt = 90.0f - m_angle;
	}
	else
	{
		m_tilt = m_angle - 90.0f;
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

DirectX::XMFLOAT3 Player::GetShotVelocity(float power) const
{
	using namespace DirectX;

	XMVECTOR start = XMLoadFloat3(&m_pos);
	XMVECTOR target = XMLoadFloat3(&basePos);
	XMVECTOR direction = XMVectorSubtract(target, start);

	if (XMVectorGetX(XMVector3LengthSq(direction)) < 0.000001f)
		return XMFLOAT3(0.0f, 0.0f, 0.0f);

	direction = XMVectorScale(XMVector3Normalize(direction), power);
	XMFLOAT3 velocity;
	XMStoreFloat3(&velocity, direction);
	return velocity;
}

std::vector<DirectX::XMFLOAT3> Player::CalculatePredictionPoints() const
{
	using namespace DirectX;

	std::vector<XMFLOAT3> points;

	// 角度調整中またはパワー調整中のみ表示
	if (m_shotStep != SHOT_ANGLE &&
		m_shotStep != SHOT_POWER)
	{
		return points;
	}

	// パワーを取得
	// 角度調整中は最小パワー1.0
	float power = 1.0f;

	if (m_shotStep == SHOT_ANGLE)
	{
		power = 2.0f;
	}
	else if (m_shotStep == SHOT_POWER)
	{
		power = m_shotPower;
	}

	// 発射速度を取得
	XMFLOAT3 velocity = GetShotVelocity(power);

	// 速度が0なら処理しない
	if (velocity.x * velocity.x +
		velocity.y * velocity.y +
		velocity.z * velocity.z < 0.000001f)
	{
		return points;
	}

	// 接地面の高さ
	constexpr float groundY = 1.0f;

	// UpdateMove()と同じ移動倍率
	constexpr float delta = 0.1f;

	// 予測線の最大フレーム数
	constexpr int maxPreviewSteps = 80;

	// パワーが強いほど表示する範囲を長くする
	int previewSteps =
		8 + static_cast<int>(power * 6.0f);

	if (previewSteps > maxPreviewSteps)
	{
		previewSteps = maxPreviewSteps;
	}

	// ---------------------------
	// 着地までのフレーム数を調べる
	// ---------------------------

	XMFLOAT3 testPos = m_pos;
	XMFLOAT3 testVel = velocity;

	int landingFrame = -1;

	for (int frame = 1; frame <= 300; ++frame)
	{
		// 重力
		testVel.y -= GRAVITY * delta;

		// 移動
		testPos.x += testVel.x * delta;
		testPos.y += testVel.y * delta;
		testPos.z += testVel.z * delta;

		// 着地判定
		if (testPos.y <= groundY)
		{
			landingFrame = frame;
			break;
		}
	}

	// 着地地点まで線を出さない
	if (landingFrame >= 0)
	{
		// 着地までの約2/3を上限にする
		int beforeLanding =
			(landingFrame - 1) * 2 / 3;

		if (beforeLanding < previewSteps)
		{
			previewSteps = beforeLanding;
		}
	}

	if (previewSteps <= 0)
	{
		return points;
	}

	// ---------------------------
	// 放物線上の座標を生成
	// ---------------------------

	points.reserve(previewSteps + 1);

	XMFLOAT3 pos = m_pos;

	// 最初の座標
	points.push_back(pos);

	for (int i = 0; i < previewSteps; ++i)
	{
		// 重力
		velocity.y -= GRAVITY * delta;

		// 座標更新
		pos.x += velocity.x * delta;
		pos.y += velocity.y * delta;
		pos.z += velocity.z * delta;

		// 接地面に達した場合は終了
		if (pos.y <= groundY)
		{
			break;
		}

		// 予測した座標を保存
		points.push_back(pos);
	}

	return points;
}
