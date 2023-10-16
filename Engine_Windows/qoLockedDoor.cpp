#include "qoLockedDoor.h"
#include "qoPlayer.h"
#include "qoEnemy.h"
#include "qoCollider.h"
#include "qoTransform.h"
#include "qoRigidbody.h"

namespace qo
{
	LockedDoor::LockedDoor()
		: mIsLocked(true)
		, mTagNumber(0)
	{
	}

	LockedDoor::~LockedDoor()
	{
	}

	void LockedDoor::Initialize()
	{
	}

	void LockedDoor::Update()
	{
		GameObject::Update();

		if (!mIsLocked)
		{
			Collider* WallCollider = GetComponent<Collider>();
		
			WallCollider->SetActive(false);

			GetComponent<Transform>()->SetColor(Vector4(1.f,0.8f,0.f,1.f));
		}
	}

	void LockedDoor::LateUpdate()
	{
		GameObject::LateUpdate();
	}

	void LockedDoor::Render()
	{
		GameObject::Render();
	}

	void LockedDoor::OnCollisionEnter(Collider* other)
	{
		Player* player = dynamic_cast<Player*>(other->GetOwner());
		Enemy* enemy = dynamic_cast<Enemy*>(other->GetOwner());

		if (player != nullptr)
		{
			Transform* PlayerTransform = player->GetComponent<Transform>();
			Transform* WallTransform = GetComponent<Transform>();

			Collider* PlayerCollider = player->GetComponent<Collider>();
			Collider* WallCollider = GetComponent<Collider>();

			Vector3 PlayerPosition = PlayerTransform->GetPosition();
			Vector3 WallPosition = WallTransform->GetPosition();

			// �÷��̾�� �� ��ü �簢�� ��輱 ���
			float PlayerLeft = PlayerPosition.x - PlayerCollider->GetScale().x / 2.0f;
			float PlayerTop = PlayerPosition.y + PlayerCollider->GetScale().y / 2.0f;
			float PlayerRight = PlayerPosition.x + PlayerCollider->GetScale().x / 2.0f;
			float PlayerBottom = PlayerPosition.y - PlayerCollider->GetScale().y / 2.0f;

			float WallLeft = WallPosition.x - WallCollider->GetScale().x / 2.0f;
			float WallTop = WallPosition.y + WallCollider->GetScale().y / 2.0f;
			float WallRight = WallPosition.x + WallCollider->GetScale().x / 2.0f;
			float WallBottom = WallPosition.y - WallCollider->GetScale().y / 2.0f;

			// �󸶳� ��ġ���� ���
			float overlapX = std::min(PlayerRight - WallLeft, WallRight - PlayerLeft);
			float overlapY = std::min(PlayerTop - WallBottom, WallTop - PlayerBottom);

			// Prevent movement into the wall based on the smaller overlap
			if (overlapX < overlapY)
			{
				if (PlayerRight - WallLeft < WallRight - PlayerLeft)
				{
					// �� ���� �浹
					PlayerTransform->SetPosition(WallLeft - (PlayerCollider->GetScale().x / 2.f), PlayerPosition.y, 0);
				}
				else
				{
					// �� ���� �浹
					PlayerTransform->SetPosition(WallRight + (PlayerCollider->GetScale().x / 2.f), PlayerPosition.y, 0);
				}
			}
			else
			{
				if (PlayerTop - WallBottom < WallTop - PlayerBottom)
				{
					// �� �ϴ� �浹
					PlayerTransform->SetPosition(PlayerPosition.x, (WallBottom - PlayerCollider->GetScale().y / 2.f), 0);
				}
				else
				{
					// �� ��� �浹
					Rigidbody* PlayerRigidbody = player->GetComponent<Rigidbody>();
					PlayerTransform->SetPosition(PlayerPosition.x, (WallTop + PlayerCollider->GetScale().y / 2.f), 0);
					PlayerRigidbody->SetGround(true);
				}
			}
		}

		if (enemy != nullptr)
		{
			Transform* EnemyTransform = enemy->GetComponent<Transform>();
			Transform* WallTransform = GetComponent<Transform>();

			Collider* EnemyCollider = enemy->GetComponent<Collider>();
			Collider* WallCollider = GetComponent<Collider>();

			Vector3 EnemyPosition = EnemyTransform->GetPosition();
			Vector3 WallPosition = WallTransform->GetPosition();

			// �÷��̾�� �� ��ü �簢�� ��輱 ���
			float EnemyLeft = EnemyPosition.x - EnemyCollider->GetScale().x / 2.0f;
			float EnemyTop = EnemyPosition.y + EnemyCollider->GetScale().y / 2.0f;
			float EnemyRight = EnemyPosition.x + EnemyCollider->GetScale().x / 2.0f;
			float EnemyBottom = EnemyPosition.y - EnemyCollider->GetScale().y / 2.0f;

			float WallLeft = WallPosition.x - WallCollider->GetScale().x / 2.0f;
			float WallTop = WallPosition.y + WallCollider->GetScale().y / 2.0f;
			float WallRight = WallPosition.x + WallCollider->GetScale().x / 2.0f;
			float WallBottom = WallPosition.y - WallCollider->GetScale().y / 2.0f;

			// �󸶳� ��ġ���� ���
			float overlapX = std::min(EnemyRight - WallLeft, WallRight - EnemyLeft);
			float overlapY = std::min(EnemyTop - WallBottom, WallTop - EnemyBottom);

			// Prevent movement into the wall based on the smaller overlap
			if (overlapX < overlapY)
			{
				if (EnemyRight - WallLeft < WallRight - EnemyLeft)
				{
					// �� ���� �浹
					EnemyTransform->SetPosition(WallLeft - (EnemyCollider->GetScale().x / 2.f), EnemyPosition.y, 0);
				}
				else
				{
					// �� ���� �浹
					EnemyTransform->SetPosition(WallRight + (EnemyCollider->GetScale().x / 2.f), EnemyPosition.y, 0);
				}
			}
			else
			{
				if (EnemyTop - WallBottom < WallTop - EnemyBottom)
				{
					// �� �ϴ� �浹
					EnemyTransform->SetPosition(EnemyPosition.x, (WallBottom - EnemyCollider->GetScale().y / 2.f), 0);
				}
				else
				{
					// �� ��� �浹
					Rigidbody* EnemyRigidbody = enemy->GetComponent<Rigidbody>();
					EnemyTransform->SetPosition(EnemyPosition.x, (WallTop + EnemyCollider->GetScale().y / 2.f), 0);
					EnemyRigidbody->SetGround(true);
				}
			}
		}
	}

	void LockedDoor::OnCollisionStay(Collider* other)
	{
		Player* player = dynamic_cast<Player*>(other->GetOwner());
		Enemy* enemy = dynamic_cast<Enemy*>(other->GetOwner());

		if (player != nullptr)
		{
			Transform* PlayerTransform = player->GetComponent<Transform>();
			Transform* WallTransform = GetComponent<Transform>();

			Collider* PlayerCollider = player->GetComponent<Collider>();
			Collider* WallCollider = GetComponent<Collider>();

			Vector3 PlayerPosition = PlayerTransform->GetPosition();
			Vector3 WallPosition = WallTransform->GetPosition();

			// �÷��̾�� �� ��ü �簢�� ��輱 ���
			float PlayerLeft = PlayerPosition.x - PlayerCollider->GetScale().x / 2.0f;
			float PlayerTop = PlayerPosition.y + PlayerCollider->GetScale().y / 2.0f;
			float PlayerRight = PlayerPosition.x + PlayerCollider->GetScale().x / 2.0f;
			float PlayerBottom = PlayerPosition.y - PlayerCollider->GetScale().y / 2.0f;

			float WallLeft = WallPosition.x - WallCollider->GetScale().x / 2.0f;
			float WallTop = WallPosition.y + WallCollider->GetScale().y / 2.0f;
			float WallRight = WallPosition.x + WallCollider->GetScale().x / 2.0f;
			float WallBottom = WallPosition.y - WallCollider->GetScale().y / 2.0f;

			// �󸶳� ��ġ���� ���
			float overlapX = std::min(PlayerRight - WallLeft, WallRight - PlayerLeft);
			float overlapY = std::min(PlayerTop - WallBottom, WallTop - PlayerBottom);

			// Prevent movement into the wall based on the smaller overlap
			if (overlapX < overlapY)
			{
				if (PlayerRight - WallLeft < WallRight - PlayerLeft)
				{
					// �� ���� �浹
					PlayerTransform->SetPosition(WallLeft - (PlayerCollider->GetScale().x / 2.f), PlayerPosition.y, 0);
				}
				else
				{
					// �� ���� �浹
					PlayerTransform->SetPosition(WallRight + (PlayerCollider->GetScale().x / 2.f), PlayerPosition.y, 0);
				}
			}
			else
			{
				if (PlayerTop - WallBottom < WallTop - PlayerBottom)
				{
					// �� �ϴ� �浹
					PlayerTransform->SetPosition(PlayerPosition.x, (WallBottom - PlayerCollider->GetScale().y / 2.f), 0);
				}
				else
				{
					// �� ��� �浹
					Rigidbody* PlayerRigidbody = player->GetComponent<Rigidbody>();
					PlayerTransform->SetPosition(PlayerPosition.x, (WallTop + PlayerCollider->GetScale().y / 2.f), 0);
					PlayerRigidbody->SetGround(true);
				}
			}
		}

		if (enemy != nullptr)
		{
			Transform* EnemyTransform = enemy->GetComponent<Transform>();
			Transform* WallTransform = GetComponent<Transform>();

			Collider* EnemyCollider = enemy->GetComponent<Collider>();
			Collider* WallCollider = GetComponent<Collider>();

			Vector3 EnemyPosition = EnemyTransform->GetPosition();
			Vector3 WallPosition = WallTransform->GetPosition();

			// �÷��̾�� �� ��ü �簢�� ��輱 ���
			float EnemyLeft = EnemyPosition.x - EnemyCollider->GetScale().x / 2.0f;
			float EnemyTop = EnemyPosition.y + EnemyCollider->GetScale().y / 2.0f;
			float EnemyRight = EnemyPosition.x + EnemyCollider->GetScale().x / 2.0f;
			float EnemyBottom = EnemyPosition.y - EnemyCollider->GetScale().y / 2.0f;

			float WallLeft = WallPosition.x - WallCollider->GetScale().x / 2.0f;
			float WallTop = WallPosition.y + WallCollider->GetScale().y / 2.0f;
			float WallRight = WallPosition.x + WallCollider->GetScale().x / 2.0f;
			float WallBottom = WallPosition.y - WallCollider->GetScale().y / 2.0f;

			// �󸶳� ��ġ���� ���
			float overlapX = std::min(EnemyRight - WallLeft, WallRight - EnemyLeft);
			float overlapY = std::min(EnemyTop - WallBottom, WallTop - EnemyBottom);

			// Prevent movement into the wall based on the smaller overlap
			if (overlapX < overlapY)
			{
				if (EnemyRight - WallLeft < WallRight - EnemyLeft)
				{
					// �� ���� �浹
					EnemyTransform->SetPosition(WallLeft - (EnemyCollider->GetScale().x / 2.f), EnemyPosition.y, 0);
				}
				else
				{
					// �� ���� �浹
					EnemyTransform->SetPosition(WallRight + (EnemyCollider->GetScale().x / 2.f), EnemyPosition.y, 0);
				}
			}
			else
			{
				if (EnemyTop - WallBottom < WallTop - EnemyBottom)
				{
					// �� �ϴ� �浹
					EnemyTransform->SetPosition(EnemyPosition.x, (WallBottom - EnemyCollider->GetScale().y / 2.f), 0);
				}
				else
				{
					// �� ��� �浹
					Rigidbody* EnemyRigidbody = enemy->GetComponent<Rigidbody>();
					EnemyTransform->SetPosition(EnemyPosition.x, (WallTop + EnemyCollider->GetScale().y / 2.f), 0);
					EnemyRigidbody->SetGround(true);
				}
			}
		}
	}

	void LockedDoor::OnCollisionExit(Collider* other)
	{
		Player* player = dynamic_cast<Player*>(other->GetOwner());
		Enemy* enemy = dynamic_cast<Enemy*>(other->GetOwner());

		if (player != nullptr)
		{
			Rigidbody* PlayerRigidbody = player->GetComponent<Rigidbody>();
			PlayerRigidbody->SetGround(false);
		}

		if (enemy != nullptr)
		{
			Rigidbody* EnemyRigidbody = enemy->GetComponent<Rigidbody>();
			EnemyRigidbody->SetGround(false);
		}
	}
}
