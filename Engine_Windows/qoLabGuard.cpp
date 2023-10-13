#include "qoLabGuard.h"
#include "qoPlayer.h"
#include "qoCollider.h"
#include "qoRigidbody.h"
#include "qoScene.h"
#include "qoSceneManager.h"
#include "qoBullet.h"

namespace qo
{
    LabGuard::LabGuard()
        : mPlayer(nullptr)
        , AttackTime(0.f)
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

        // 공격하고 2초가 넘기면 0으로 초기화
        if (AttackTime > 2.f)
        {
            AttackTime = 0.f;
        }
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

    void LabGuard::OnCollisionEnter(Collider* other)
    {
        Bullet* bullet = dynamic_cast<Bullet*>(other->GetOwner());

        if (bullet != nullptr)
        {
            // 충돌한 bullet 객체의 포지션
            Vector3 first = bullet->GetComponent<Transform>()->GetPosition();

            Scene* ActiveScene = SceneManager::GetActiveScene();
            std::vector<GameObject*> bullets = ActiveScene->GetLayer((UINT)LAYER::BULLET)->GetGameObjects();
            long double min = 60.f;

            GameObject* target = nullptr;

            for (GameObject* bulletobj : bullets)
            {
                if (bullet == bulletobj)
                {
                    target = bulletobj;
                    continue;
                }

                //Vector3 compare = bulletobj->GetComponent<Transform>()->GetPosition();

                //long double Distance = sqrt(pow(static_cast<long double>(first.x) - static_cast<long double>(compare.x), 2) +
                //    pow(static_cast<long double>(first.x) - static_cast<long double>(compare.x), 2));

                //if (static_cast<long double>(min) > Distance)
                //{
                //    //min = Distance;
                //    target = bulletobj;
                //}
            }

            if (target != nullptr)
            {
                SetStage(eStage::eHit);
            }
        }
    }

    void LabGuard::OnCollisionStay(Collider* other)
    {
        Player* player = dynamic_cast<Player*>(other->GetOwner());
        AttackTime += Time::DeltaTime();

        if ((player != nullptr))
        {
            Vector3 PlayerPos = player->GetComponent<Transform>()->GetPosition();

            Scene* ActiveScene = SceneManager::GetActiveScene();
            std::vector<GameObject*> objects = ActiveScene->GetLayer((UINT)LAYER::PLAYER)->GetGameObjects();

            GameObject* target = nullptr;

            for (GameObject* playerobj : objects)
            {
                if (player == playerobj)
                {
                    target = playerobj;
                    continue;
                }
            }

            if (target != nullptr && (AttackTime >= 2.f))
            {
                // Damage 함수를 TakeHit로 바꿔서 공격당하면 밀리게 만들기
                player->Damaged(GetATK());
            }
        }
    }

    void LabGuard::OnCollisionExit(Collider* other)
    {
    }

    void LabGuard::TakeHit(int DamageAmount, math::Vector3 HitDir)
    {
        Damaged(DamageAmount);

        Rigidbody* rb = GetComponent<Rigidbody>();

        if (rb != nullptr)
        {
            rb->AddVelocity(HitDir * 0.25f);
        }
    }
}
