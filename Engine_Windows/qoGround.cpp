#include "qoGround.h"
#include "qoPlayer.h"
#include "qoCollider.h"
#include "qoTransform.h"
#include "qoRigidbody.h"
#include "qoLabGuard.h"

namespace qo
{
    Ground::Ground()
    {
    }

    Ground::~Ground()
    {
    }

    void Ground::Initialize()
    {
    }

    void Ground::Update()
    {
        GameObject::Update();
    }

    void Ground::LateUpdate()
    {
        GameObject::LateUpdate();
    }

    void Ground::Render()
    {
        GameObject::Render();
    }

    void Ground::OnCollisionEnter(Collider* other)
    {
        Player* player = dynamic_cast<Player*>(other->GetOwner());
        if (player != nullptr)
        {
            Transform* playertr = player->GetComponent<Transform>();
            Transform* floortr = GetComponent<Transform>();

            Collider* playercol = player->GetComponent<Collider>();
            Collider* floorcol = GetComponent<Collider>();

            if (player->GetComponent<Rigidbody>()->GetVelocity().y < 0)
            {
                player->GetComponent<Rigidbody>()->SetGround(true);


                float scale = fabs(playercol->GetScale().y / 2.f + floorcol->GetScale().y / 2.f);
                float len = fabs(playertr->GetPosition().y + playercol->GetOffset().y + -floortr->GetPosition().y);

                if (len < scale)
                {
                    math::Vector3 playerPos = playertr->GetPosition();
                    playerPos.y += (scale - len) + 0.01f;
                    playertr->SetPosition(playerPos);
                }
            }
        }

        LabGuard* labguard = dynamic_cast<LabGuard*>(other->GetOwner());

        if (labguard != nullptr)
        {
            Transform* labguardtr = labguard->GetComponent<Transform>();
            Transform* floortr = GetComponent<Transform>();

            Collider* labguardcol = labguard->GetComponent<Collider>();
            Collider* floorcol = GetComponent<Collider>();

            if (labguard->GetComponent<Rigidbody>()->GetVelocity().y < 0)
            {
                labguard->GetComponent<Rigidbody>()->SetGround(true);

                float scale = fabs(labguardcol->GetScale().y / 2.f + floorcol->GetScale().y / 2.f);
                float len = fabs(labguardtr->GetPosition().y + labguardcol->GetOffset().y + - floortr->GetPosition().y);

                if (len < scale)
                {
                    math::Vector3 labguardPos = labguardtr->GetPosition();
                    labguardPos.y += (scale - len) + 0.01f;
                    labguardtr->SetPosition(labguardPos);
                }
            }
        }
    }

    void Ground::OnCollisionStay(Collider* other)
    {
    }

    void Ground::OnCollisionExit(Collider* other)
    {
    }
}