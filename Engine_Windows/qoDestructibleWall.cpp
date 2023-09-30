#include "qoDestructibleWall.h"
#include "qoPlayer.h"
#include "qoBullet.h"
#include "qoCollider.h"
#include "qoTransform.h"
#include "qoRigidbody.h"

namespace qo
{
	DestuctibleWall::DestuctibleWall()
	{
	}

	DestuctibleWall::~DestuctibleWall()
	{
	}

	void DestuctibleWall::Initialize()
	{
	}

	void DestuctibleWall::Update()
	{
		GameObject::Update();
	}

	void DestuctibleWall::LateUpdate()
	{
		GameObject::LateUpdate();
	}

	void DestuctibleWall::Render()
	{
		GameObject::Render();
	}

	void DestuctibleWall::OnCollisionEnter(Collider* other)
	{
		Player* player = dynamic_cast<Player*>(other->GetOwner());
		Bullet* bullet = dynamic_cast<Bullet*>(other->GetOwner());

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
		if (bullet != nullptr)
		{
			Collider* WallCollider = GetComponent<Collider>();

			Destroy(bullet);
			WallCollider->SetActive(false);
		}
	}

	void DestuctibleWall::OnCollisionStay(Collider* other)
	{
	}

	void DestuctibleWall::OnCollisionExit(Collider* other)
	{
	}
}
