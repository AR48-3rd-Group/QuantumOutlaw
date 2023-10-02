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

			Vector3 PlayerPosition = PlayerTransform->GetPosition();
			Vector3 WallPosition = WallTransform->GetPosition();

			// 플레이어랑 벽 개체 사각형 경계선 계산
			float PlayerLeft = PlayerPosition.x - PlayerCollider->GetScale().x / 2.0f;
			float PlayerTop = PlayerPosition.y + PlayerCollider->GetScale().y / 2.0f;
			float PlayerRight = PlayerPosition.x + PlayerCollider->GetScale().x / 2.0f;
			float PlayerBottom = PlayerPosition.y - PlayerCollider->GetScale().y / 2.0f;

			float WallLeft = WallPosition.x - WallCollider->GetScale().x / 2.0f;
			float WallTop = WallPosition.y + WallCollider->GetScale().y / 2.0f;
			float WallRight = WallPosition.x + WallCollider->GetScale().x / 2.0f;
			float WallBottom = WallPosition.y - WallCollider->GetScale().y / 2.0f;

			// 얼마나 겹치는지 계산
			float overlapX = std::min(PlayerRight - WallLeft, WallRight - PlayerLeft);
			float overlapY = std::min(PlayerTop - WallBottom, WallTop - PlayerBottom);

			// Prevent movement into the wall based on the smaller overlap
			if (overlapX < overlapY)
			{
				if (PlayerRight - WallLeft < WallRight - PlayerLeft)
				{
					// 벽 좌측 충돌
					PlayerTransform->SetPosition(WallLeft - (PlayerCollider->GetScale().x / 2.f), PlayerPosition.y, 0);
				}
				else
				{
					// 벽 우측 충돌
					PlayerTransform->SetPosition(WallRight + (PlayerCollider->GetScale().x / 2.f), PlayerPosition.y, 0);
				}
			}
			else
			{
				if (PlayerTop - WallBottom < WallTop - PlayerBottom)
				{
					// 벽 하단 충돌
					PlayerTransform->SetPosition(PlayerPosition.x, (WallBottom - PlayerCollider->GetScale().y / 2.f), 0);
				}
				else
				{
					// 벽 상단 충돌
					Rigidbody* PlayerRigidbody = player->GetComponent<Rigidbody>();
					PlayerTransform->SetPosition(PlayerPosition.x, (WallTop + PlayerCollider->GetScale().y / 2.f), 0);
					PlayerRigidbody->SetGround(true);
				}
			}
		}
	}

	void Barrier::OnCollisionStay(Collider* other)
	{
		Player* player = dynamic_cast<Player*>(other->GetOwner());

		if (player != nullptr)
		{
			Transform* PlayerTransform = player->GetComponent<Transform>();
			Transform* WallTransform = GetComponent<Transform>();

			Collider* PlayerCollider = player->GetComponent<Collider>();
			Collider* WallCollider = GetComponent<Collider>();

			Vector3 PlayerPosition = PlayerTransform->GetPosition();
			Vector3 WallPosition = WallTransform->GetPosition();

			// 플레이어랑 벽 개체 사각형 경계선 계산
			float PlayerLeft = PlayerPosition.x - PlayerCollider->GetScale().x / 2.0f;
			float PlayerTop = PlayerPosition.y + PlayerCollider->GetScale().y / 2.0f;
			float PlayerRight = PlayerPosition.x + PlayerCollider->GetScale().x / 2.0f;
			float PlayerBottom = PlayerPosition.y - PlayerCollider->GetScale().y / 2.0f;

			float WallLeft = WallPosition.x - WallCollider->GetScale().x / 2.0f;
			float WallTop = WallPosition.y + WallCollider->GetScale().y / 2.0f;
			float WallRight = WallPosition.x + WallCollider->GetScale().x / 2.0f;
			float WallBottom = WallPosition.y - WallCollider->GetScale().y / 2.0f;

			// 얼마나 겹치는지 계산
			float overlapX = std::min(PlayerRight - WallLeft, WallRight - PlayerLeft);
			float overlapY = std::min(PlayerTop - WallBottom, WallTop - PlayerBottom);

			// Prevent movement into the wall based on the smaller overlap
			if (overlapX < overlapY)
			{
				if (PlayerRight - WallLeft < WallRight - PlayerLeft)
				{
					// 벽 좌측 충돌
					PlayerTransform->SetPosition(WallLeft - (PlayerCollider->GetScale().x / 2.f), PlayerPosition.y, 0);
				}
				else
				{
					// 벽 우측 충돌
					PlayerTransform->SetPosition(WallRight + (PlayerCollider->GetScale().x / 2.f), PlayerPosition.y, 0);
				}
			}
			else
			{
				if (PlayerTop - WallBottom < WallTop - PlayerBottom)
				{
					// 벽 하단 충돌
					PlayerTransform->SetPosition(PlayerPosition.x, (WallBottom - PlayerCollider->GetScale().y / 2.f), 0);
				}
				else
				{
					// 벽 상단 충돌
					Rigidbody* PlayerRigidbody = player->GetComponent<Rigidbody>();
					PlayerTransform->SetPosition(PlayerPosition.x, (WallTop + PlayerCollider->GetScale().y / 2.f), 0);
					PlayerRigidbody->SetGround(true);
				}
			}
		}
	}

	void Barrier::OnCollisionExit(Collider* other)
	{
		Player* player = dynamic_cast<Player*>(other->GetOwner());

		if (player != nullptr)
		{
			Rigidbody* PlayerRigidbody = player->GetComponent<Rigidbody>();
			PlayerRigidbody->SetGround(false);
		}
	}
}
