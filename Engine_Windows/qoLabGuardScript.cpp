#include "qoLabGuardScript.h"
#include "qoTransform.h"
#include "qoRigidbody.h"
#include "qoTime.h"
#include "qoLabGuard.h"
#include "qoPlayer.h"

namespace qo
{
	LabGuardScript::LabGuardScript()
		: mPlayer(nullptr)
		, mLabGuard(nullptr)
		, mTransform(nullptr)
		, mRigidbody(nullptr)
		, mDamagedDlay(0.f)
	{

	}

	LabGuardScript::~LabGuardScript()
	{
	}

	void LabGuardScript::Initialize()
	{
		mLabGuard = dynamic_cast<LabGuard*>(GetOwner());
		mTransform = mLabGuard->GetComponent<Transform>();
		mRigidbody = mLabGuard->GetComponent<Rigidbody>();

		LabGuardPos = mTransform->GetPosition();
		mLabGuard->SetStatus(LabGuardPos);

		mPlayer = dynamic_cast<LabGuard*>(GetOwner())->mPlayer;
		mPlayerTr = mPlayer->GetComponent<Transform>();

		assert(mLabGuard);
	}

	void LabGuardScript::Update()
	{
		PlayerPos = mPlayerTr->GetPosition();
		LabGuardPos = mTransform->GetPosition();
	
		switch (mLabGuard->GetStage())
		{
		case eStage::eSearch:
			Search();
			break;
		case eStage::eChase:
			Chase();
			break;
		case eStage::eFall:
			Fall();
			break;
		case eStage::eAttack:
			Attack();
			break;
		case eStage::eHit:
			Hit();
			break;
		case eStage::eDead:
			Dead();
			break;
		default:
			break;
		}	

		LabGuard* obj = dynamic_cast<LabGuard*>(GetOwner());

		if (obj != nullptr)
		{
			std::cout << "null";
		}
	}

	void LabGuardScript::LateUpdate()
	{
	}

	void LabGuardScript::Render()
	{
	}

	void LabGuardScript::Search()
	{
		if (!mRigidbody->GetGround())
		{
			mLabGuard->SetStage(eStage::eFall);
		}
		
		// 일정 범위 내에 몬스터가 있으면 chase 함수로
		if ((LabGuardPos.x - 0.5f <= PlayerPos.x) && (LabGuardPos.x + 0.5f >= PlayerPos.x) 
			&& (LabGuardPos.y-0.1f<= PlayerPos.y) && (LabGuardPos.y + 0.1f >= PlayerPos.y))
		{
			mLabGuard->SetStage(eStage::eChase);
		}

		else
		{
			if (mLabGuard->GetDirection() == eDirection::LEFT)
			{
				LabGuardPos.x -= mLabGuard->GetMovementSpeed() * Time::DeltaTime();
			
				// 왼쪽으로 0.5만큼 이동하면 오른쪽으로 바꾸기
				if (mLabGuard->Pos.x - 0.5f > LabGuardPos.x)
				{
					mLabGuard->SetDirection(eDirection::RIGHT);
				}
			}

			else if (mLabGuard->GetDirection() == eDirection::RIGHT)
			{
				LabGuardPos.x += mLabGuard->GetMovementSpeed() * Time::DeltaTime();

				// 오른쪽으로 0.5만큼 이동하면 왼쪽으로 바꾸기
				if (mLabGuard->Pos.x + 0.5f < LabGuardPos.x)
				{
					mLabGuard->SetDirection(eDirection::LEFT);
				}
			}
		}

		mTransform->SetPosition(LabGuardPos);
	}

	void LabGuardScript::Chase()
	{
		if (!mRigidbody->GetGround())
		{
			mLabGuard->SetStage(eStage::eFall);
		}

		// 몬스터 좌표 +- 0.5f 범위 내에 플레이어가 있으면
		if ((LabGuardPos.x - 0.5f <= PlayerPos.x) && (LabGuardPos.x + 0.5f >= PlayerPos.x))
		{
			// 몬스터가 플레이어보다 오른쪽에 있으면
			if (LabGuardPos.x > PlayerPos.x)
			{
				LabGuardPos.x -= mLabGuard->GetMovementSpeed() * Time::DeltaTime();
				mLabGuard->SetDirection(eDirection::LEFT);
			}

			// 몬스터가 플레이어보다 왼쪽에 있으면
			else if (LabGuardPos.x < PlayerPos.x)
			{
				LabGuardPos.x += mLabGuard->GetMovementSpeed() * Time::DeltaTime();
				mLabGuard->SetDirection(eDirection::RIGHT);
			}

			// +- 0.1 범위에 플레이어가 있으면 attack
			else if ((LabGuardPos.x - 0.1f <= PlayerPos.x) && (LabGuardPos.x + 0.1f >= PlayerPos.x))
			{
				mLabGuard->SetStage(eStage::eAttack);
			}
		}

		// 몬스터 좌표 +-0.5f 범위 내에 플레이어가 없으면 search
		else
		{
			mLabGuard->SetStage(eStage::eSearch);
		}

		mTransform->SetPosition(LabGuardPos);
	}

	void LabGuardScript::Fall()
	{
		if (mRigidbody->GetGround())
		{
			mLabGuard->SetStage(eStage::eSearch);
		}
	}

	void LabGuardScript::Attack()
	{
		if (!mRigidbody->GetGround())
		{
			mLabGuard->SetStage(eStage::eFall);
		}

		// 몬스터 좌표 +- 0.1f 안에 플레이어 존재하면 공격하기
		if ((LabGuardPos.x - 0.1f <= PlayerPos.x) && (LabGuardPos.x + 0.1f >= PlayerPos.x))
		{
			mLabGuard->SetStage(eStage::eChase);
		}

		// 범위 내에 플레이어가 없으면 search
		else
		{
			mLabGuard->SetStage(eStage::eSearch);
		}
	}

	void LabGuardScript::Hit()
	{
		mDamagedDlay += Time::DeltaTime();

		if (mDamagedDlay > 1.f)
		{
			mLabGuard->SetStage(eStage::eSearch);
			mDamagedDlay = 0.f;
		}
	}

	void LabGuardScript::Dead()
	{
		Destroy(mLabGuard);
	}

}
