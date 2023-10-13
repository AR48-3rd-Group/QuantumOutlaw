#include "qoLabTurret.h"
#include "qoPlayer.h"

namespace qo
{
    LabTurret::LabTurret()
    {
        SetType(eRanged);
        SetStage(eSearch);
        SetHP(80);
        SetMovementSpeed(0);
        SetATK(15);
    }

    LabTurret::~LabTurret()
    {
    }

    void LabTurret::Initialize()
    {
        GameObject::Initialize();
    }

    void LabTurret::Update()
    {
        GameObject::Update();
    }

    void LabTurret::LateUpdate()
    {
        GameObject::LateUpdate();
    }

    void LabTurret::Render()
    {
        GameObject::Render();
    }

    void LabTurret::SetPlayer(GameObject* player)
    {
        mPlayer = static_cast<Player*>(player);
    }

    //void LabTurret::TakeHit(int DamageAmount, math::Vector3 HitDir)
    //{
    //}
}
