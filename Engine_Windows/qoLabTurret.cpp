#include "qoLabTurret.h"
#include "qoPlayer.h"
#include "qoRigidbody.h"
#include "qoBullet.h"
#include "qoCollider.h"
#include "qoScene.h"
#include "qoSceneManager.h"

namespace qo
{
    LabTurret::LabTurret()
        : AttackTime(0.0f)
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

        // 공격하고 2초가 넘기면 0으로 초기화
        if (AttackTime > 2.f)
        {
            AttackTime = 0.f;
        }
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

    void LabTurret::OnCollisionEnter(Collider* other)
    {
  
    }

    void LabTurret::OnCollisionStay(Collider* other)
    {
    }

    void LabTurret::OnCollisionExit(Collider* other)
    {
    }

    void LabTurret::TakeHit(int DamageAmount, math::Vector3 HitDir)
    {
        Damaged(DamageAmount);

        if (GetHP() < 0)
        {
            SetStage(eStage::eDead);
        }
    }
}
