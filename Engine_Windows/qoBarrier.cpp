#include "qoBarrier.h"
#include "qoPlayer.h"
#include "qoCollider.h"
#include "qoTransform.h"
#include "qoRigidbody.h"

namespace qo
{
	Barrier::Barrier()
	{
	}

	Barrier::~Barrier()
	{
	}

	void Barrier::Initialize()
	{
	}

	void Barrier::Update()
	{
		GameObject::Update();
	}

	void Barrier::LateUpdate()
	{
		GameObject::LateUpdate();
	}

	void Barrier::Render()
	{
		GameObject::Render();
	}

	void Barrier::OnCollisionEnter(Collider* other)
	{
		Player* player = dynamic_cast<Player*>(other->GetOwner());

		if (player != nullptr)
		{
			Transform* PlayerTransform = player->GetComponent<Transform>();
			Transform* WallTransform = GetComponent<Transform>();

			Collider* PlayerCollider = player->GetComponent<Collider>();
			Collider* WallCollider = GetComponent<Collider>();

			if (player->GetComponent<Rigidbody>()->GetVelocity().y < 0)
			{
				player->GetComponent<Rigidbody>()->SetGround(true);


				float scale = fabs(PlayerCollider->GetScale().y / 2.f + WallCollider->GetScale().y / 2.f);
				float len = fabs(PlayerTransform->GetPosition().y + PlayerCollider->GetOffset().y + -WallTransform->GetPosition().y);

				if (len < scale)
				{
					math::Vector3 PlayerPosition = PlayerTransform->GetPosition();
					PlayerPosition.y += (scale - len) + 0.01f;
					PlayerTransform->SetPosition(PlayerPosition);
				}
			}
		}
	}

	void Barrier::OnCollisionStay(Collider* other)
	{
	}

	void Barrier::OnCollisionExit(Collider* other)
	{
	}
}
