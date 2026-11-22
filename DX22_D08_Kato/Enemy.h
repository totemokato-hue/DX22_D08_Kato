#pragma once

#include <DirectXMath.h>
#include "Collision.h"
#include "Model.h"

class Enemy
{
private:
    Model* m_pModel;
    DirectX::XMFLOAT3 m_pos;
    DirectX::XMFLOAT3 m_scale;
    Collision::Box m_collision;

    bool m_isAlive;

public:
    Enemy();
    ~Enemy();

    void Update();
    void Draw();

    void SetPos(float x, float y, float z);
    void SetScale(float x, float y, float z);

    const Collision::Box& GetCollisionBox() const
    {
        return m_collision;
    }

    bool IsAlive() const
    {
        return m_isAlive;
    }

    void Hit();   //ƒvƒŒƒCƒ„[‚É“–‚½‚Á‚½‚©
    void Reset(); // “G‚ğ•œŠˆ‚³‚¹‚é
};

