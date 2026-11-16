
//TopCamera/h
#pragma once
#include"camera.h"
#include"Input.h"
#include"Defines.h"
#include"ForcusPoint.h"
class TopCamera : public Camera
{
public:

	enum ViewMode
	{
		FRONT,
		RIGHT,
		LEFT
	};
	TopCamera();
	~TopCamera();

	void Update() final;
	void SetForcus(ForcusPoint* point);

	void SetMode(ViewMode mode);


private:
	ForcusPoint* m_Point;
	float m_radXZ;
	float m_radY;
	float m_radius;
	ViewMode m_mode;
};