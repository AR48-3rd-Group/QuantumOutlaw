#include "qoLabGuardScript.h"
#include "qoTransform.h"
#include "qoTime.h"

namespace qo
{
	LabGuardScript::LabGuardScript()
		: mLabGuard(nullptr)
	{

	}

	LabGuardScript::~LabGuardScript()
	{
	}

	void LabGuardScript::Initialize()
	{
		mLabGuard = dynamic_cast<LabGuard*>(GetOwner());

		assert(mLabGuard);
	}

	void LabGuardScript::Update()
	{
		switch (mLabGuard->GetStage())
		{
		case eStage::eSearch:
			Search();
			break;
		case eStage::eChase:
			mLabGuard->Chase();
			break;
		case eStage::eAttack:
			mLabGuard->Attack();
			break;
		case eStage::eHit:
			//mLabGuard->TakeHit();
			break;
		case eStage::eDead:
			mLabGuard->Dead();
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
		Transform* tr = mLabGuard->GetComponent<Transform>();
		Vector3 LabGuardPos = tr->GetPosition();

		if (mLabGuard->Dir == -1)
		{
			LabGuardPos.x -= mLabGuard->GetMovementSpeed() * Time::DeltaTime();
			
			//if (mLabGuard->pos.x + 0.3f < LabGuardPos.x)
			//{
			//	mLabGuard->Dir *= -1;
			//}
		}

		else if (mLabGuard->Dir == 1)
		{
			LabGuardPos.x += mLabGuard->GetMovementSpeed() * Time::DeltaTime();
			//
			//if (mLabGuard->pos.x - 0.3f > LabGuardPos.x)
			//{
			//	mLabGuard->Dir *= -1;
			//}
		}

		tr->SetPosition(LabGuardPos);

		// monster랑 wall이랑 충돌처리되면 dir * -1 해서 방향 전환하기
	}

	void LabGuardScript::Chase()
	{
		// player 위치 받아서 따라가기
	}

	void LabGuardScript::Attack()
	{
		// 몬스터의 히트박스 안에 플레이어 존재하면 공격하기
	}

	void LabGuardScript::Hit()
	{
		// 플레이어가 공격하면 공격받음
	}

	void LabGuardScript::Dead()
	{
		// hp 0되면 dead
	}

}
