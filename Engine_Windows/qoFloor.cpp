#include "qoFloor.h"
#include "qoPlayer.h"
#include "qoCollider.h"
#include "qoTransform.h"
#include "qoRigidbody.h"

namespace qo
{
	Floor::Floor()
	{
	}

	Floor::~Floor()
	{
	}

	void Floor::Initialize()
	{
	}

	void Floor::Update()
	{
		GameObject::Update();
	}

	void Floor::LateUpdate()
	{
		GameObject::LateUpdate();
	}

	void Floor::Render()
	{
		GameObject::Render();
	}

	void Floor::OnCollisionEnter(Collider* other)
	{
		Player* player = dynamic_cast<Player*>(other->GetOwner());

		if (player != nullptr)
		{
			Transform* PlayerTransform = player->GetComponent<Transform>();
			Transform* FloorTransform = GetComponent<Transform>();

			Collider* PlayerCollider = player->GetComponent<Collider>();
			Collider* FloorCollider = GetComponent<Collider>();

			if (player->GetComponent<Rigidbody>()->GetVelocity().y < 0)
			{
				player->GetComponent<Rigidbody>()->SetGround(true);


				float scale = fabs(PlayerCollider->GetScale().y / 2.f + FloorCollider->GetScale().y / 2.f);
				float len = fabs(PlayerTransform->GetPosition().y + PlayerCollider->GetOffset().y + -FloorTransform->GetPosition().y);

				if (len < scale)
				{
					math::Vector3 PlayerPosition = PlayerTransform->GetPosition();
					PlayerPosition.y += (scale - len) + 0.01f;
					PlayerTransform->SetPosition(PlayerPosition);
				}
			}
		}
	}

	void Floor::OnCollisionStay(Collider* other)
	{
	}

	void Floor::OnCollisionExit(Collider* other)
	{
	}
}
