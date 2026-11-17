//CameraForcus.h
#pragma once
#include"Input.h"
#include"DirectX.h"
#include"ShaderList.h"
#include"camera.h"
#include"Geometory.h"
class ForcusPoint
{
public:
	ForcusPoint();
	~ForcusPoint();

	
	void Update(float cameraYaw);
	void SetCamera(Camera* fCamera);
	void Draw();
	DirectX::XMFLOAT3 GetPos();

private:
	DirectX::XMFLOAT3 m_pos;  //	íçéãì_ÇÃà íu
	Camera* m_tCamera;
};
