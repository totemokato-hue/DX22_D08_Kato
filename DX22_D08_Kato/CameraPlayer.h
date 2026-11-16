#pragma once
#include "camera.h"
#include "player.h"

class CameraPlayer : public Camera {
private:
	float m_radXZ;
	float m_radY;
	float m_radius;
	Player* m_pPlayer;//追いかけるプレイヤー

public:
	//基本の処理
	CameraPlayer();
	~CameraPlayer();

	void Update() final;

	void SetPlayer(Player* player) { m_pPlayer = player; }
};