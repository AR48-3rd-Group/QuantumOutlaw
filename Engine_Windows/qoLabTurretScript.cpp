#include "qoLabTurretScript.h"
#include "qoLabTurret.h"
#include "qoTransform.h"
#include "qoRigidbody.h"
#include "qoPlayer.h"

namespace qo
{
	LabTurretScript::LabTurretScript()
		: mLabTurret(nullptr)
		, mTransform(nullptr)
		, mRigidbody(nullptr)
	{

	}

	LabTurretScript::~LabTurretScript()
	{
	}

	void LabTurretScript::Initialize()
	{
		mLabTurret = dynamic_cast<LabTurret*>(GetOwner());
		mTransform = mLabTurret->GetComponent<Transform>();
		mRigidbody = mLabTurret->GetComponent<Rigidbody>();
		LabTurretPos = mTransform->GetPosition();

		mPlayer = dynamic_cast<LabTurret*>(GetOwner())->mPlayer;
		mPlayerTr = mPlayer->GetComponent<Transform>();

		assert(mLabTurret);
	}

	void LabTurretScript::Update()
	{
		switch (mLabTurret->GetStage())
		{
		case eStage::eSearch:
			Search();
			break;
		case eStage::eFall:
			Fall();
			break;
		case eStage::eAttack:
			Attack();
			break;
		case eStage::eHit:
			//mEnemy->TakeHit();
			break;
		case eStage::eDead:
			Dead();
			break;
		default:
			break;
		}

		PlayerPos = mPlayerTr->GetPosition();

		LabTurret* obj = dynamic_cast<LabTurret*>(GetOwner());

		if (obj != nullptr)
		{
			std::cout << "null";
		}
	}

	void LabTurretScript::LateUpdate()
	{
	}

	void LabTurretScript::Render()
	{
	}

	void LabTurretScript::Search()
	{
		if (!mRigidbody->GetGround())
		{
			mLabTurret->SetStage(eStage::eFall);
		}

		// +-0.5 범위 내에 플레이어가 존재하면 attack 함수로
		if ((LabTurretPos.x - 0.5f <= PlayerPos.x) && (LabTurretPos.x + 0.5f >= PlayerPos.x))
		{
			mLabTurret->SetStage(eStage::eAttack);
		}
	}

	void LabTurretScript::Fall()
	{
		if (mRigidbody->GetGround())
		{
			mLabTurret->SetStage(eStage::eSearch);
		}
	}

	void LabTurretScript::Attack()
	{
		// 총알 만들기 (방향 정해주고)
		// +- 0.5 범위 내에 플레이어가 존재하면 공격한다
		if ((LabTurretPos.x - 0.5f <= PlayerPos.x) && (LabTurretPos.x + 0.5f >= PlayerPos.x))
		{

		}

		// +- 0.5 범위 내에 플레이어가 존재하지 않으면 search
		else
		{
			mLabTurret->SetStage(eStage::eSearch);
		}
	}

	void LabTurretScript::Hit()
	{
		// 근접몬스터 히트함수랑 똑같이
	}

	void LabTurretScript::Dead()
	{
	}

}
