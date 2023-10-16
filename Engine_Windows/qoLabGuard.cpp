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

        // �����ϰ� 2�ʰ� �ѱ�� 0���� �ʱ�ȭ
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
            Vector3 first = bullet->GetComponent<Transform>()->GetPosition();

            Scene* ActiveScene = SceneManager::GetActiveScene();
            std::vector<GameObject*> bullets = ActiveScene->GetLayer((UINT)LAYER::BULLET)->GetGameObjects();

            GameObject* target = nullptr;

            for (GameObject* bulletobj : bullets)
            {
                if (bullet == bulletobj)
                {
                    target = bulletobj;
                    continue;
                }
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
                // Damage �Լ��� TakeHit�� �ٲ㼭 ���ݴ��ϸ� �и��� �����
                //player->Damaged(GetATK());

                Vector3 dir = PlayerPos - GetComponent<Transform>()->GetPosition();
                dir.Normalize();
                player->TakeHit(GetATK(), dir);
            }
        }
    }

    void LabGuard::OnCollisionExit(Collider* other)
    {
    }

    void LabGuard::TakeHit(int DamageAmount, math::Vector3 HitDir)
    {
        Damaged(DamageAmount);

        if (GetHP() < 0)
        {
            SetStage(eStage::eDead);
        }

        Rigidbody* rb = GetComponent<Rigidbody>();

        if (rb != nullptr)
        {
            rb->AddVelocity(HitDir * 0.25f);
        }
    }
}
