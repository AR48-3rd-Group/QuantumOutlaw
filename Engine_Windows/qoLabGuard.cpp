#include "qoLabGuard.h"
#include "qoPlayer.h"

namespace qo
{
    LabGuard::LabGuard()
        : mPlayer(nullptr)
    {
        SetType(eMelee);
        SetStage(eSearch);
        SetHP(50);
        SetMovementSpeed(0.3f);
        SetATK(10);
        SetDirection(eDirection::LEFT);
    }

    LabGuard::~LabGuard()
    {
    }

    void LabGuard::Initialize()
    {
        GameObject::Initialize();
    }

    void LabGuard::Update()
    {
        GameObject::Update();
    }

    void LabGuard::LateUpdate()
    {
        GameObject::LateUpdate();
    }

    void LabGuard::Render()
    {
        GameObject::Render();
    }

    void LabGuard::SetPlayer(GameObject* player)
    {
        mPlayer = dynamic_cast<Player*>(player);
    }

    void LabGuard::Search()
    {
        
    }

    void LabGuard::Chase()
    {
        // 肺流 累己
    }

    void LabGuard::Attack()
    {
        // 肺流 累己
    }

    void LabGuard::Dead()
    {
    }

    void LabGuard::TakeHit(int DamageAmount, math::Vector3 HitDir)
    {
    }
}
