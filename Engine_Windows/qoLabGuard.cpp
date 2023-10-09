#include "qoLabGuard.h"

namespace qo
{
    LabGuard::LabGuard()
        : Dir(-1)
    {
        SetType(eMelee);
        SetStage(eSearch);
        SetHP(50);
        SetMovementSpeed(0.5f);
        SetATK(10);
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
