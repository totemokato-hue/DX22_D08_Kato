//CameraDebug.h
#include"camera.h"
#include"Input.h"
#include"Defines.h"
#pragma once
//デバッグ用カメラ
class CameraDebug : public Camera {
public:

	//コンストラクタ
	CameraDebug();

	//デストラクタ
	~CameraDebug();

	//更新処理
	void Update() final;

private:
	float m_radXZ;
	float m_radY;
	float m_radius;
};