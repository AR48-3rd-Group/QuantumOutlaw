#include "qoElevator.h"
#include "qoPlayer.h"
#include "qoCollider.h"
#include "qoTransform.h"
#include "qoRigidbody.h"
#include "qoTime.h"
#include "qoApplication.h"

extern qo::Application application;

namespace qo
{
	Elevator::Elevator()
		: mDirection(evrDirection::VERTICAL)
		, mIsActive(false)
		, mTagNumber(0)
		, mMovementRange(100)
		, mTick(true)
		, mTimer(2.0f)
	{
	}

	Elevator::~Elevator()
	{
	}

	void Elevator::Initialize()
	{
	}

	void Elevator::Update()
	{
		GameObject::Update();

		Transform* ElevatorTransform = GetComponent<Transform>();
		Vector3 ElevatorPosition = ElevatorTransform->GetPosition();

		if (mIsActive)
		{
			if (mDirection == evrDirection::VERTICAL)
			{
				if (mTick)
				{
					ElevatorPosition.y += (1.0f / static_cast<float>(application.GetHeight())) * mMovementRange * Time::DeltaTime();
					mTimer -= Time::DeltaTime();
					if (mTimer < 0.0f)
					{
						ResetTimer();
						mTick = false;
					}
				}
				else 
				{
					ElevatorPosition.y -= (1.0f / static_cast<float>(application.GetHeight())) * mMovementRange * Time::DeltaTime();
					mTimer -= Time::DeltaTime();
					if (mTimer < 0.0f)
					{
						ResetTimer();
						mTick = true;
					}
				}
			}
			if (mDirection == evrDirection::HORIZONTAL)
			{
				if (mTick)
				{
					ElevatorPosition.x += (1.0f / static_cast<float>(application.GetWidth())) * mMovementRange * Time::DeltaTime();
					mTimer -= Time::DeltaTime();
					if (mTimer < 0.0f)
					{
						ResetTimer();
						mTick = false;
					}
				}
			}
			ElevatorTransform->SetPosition(ElevatorPosition);
		}
	}

	void Elevator::LateUpdate()
	{
		GameObject::LateUpdate();
	}

	void Elevator::Render()
	{
		GameObject::Render();
	}

	void Elevator::OnCollisionEnter(Collider* other)
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

	void Elevator::OnCollisionStay(Collider* other)
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

	void Elevator::OnCollisionExit(Collider* other)
	{
	}

	void Elevator::ResetTimer()
	{
		mTimer = mInitialTimerValue;
	}
}
