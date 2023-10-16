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
		
		// ���� ���� ���� ���Ͱ� ������ chase �Լ���
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
			
				// �������� 0.5��ŭ �̵��ϸ� ���������� �ٲٱ�
				if (mLabGuard->Pos.x - 0.5f > LabGuardPos.x)
				{
					mLabGuard->SetDirection(eDirection::RIGHT);
				}
			}

			else if (mLabGuard->GetDirection() == eDirection::RIGHT)
			{
				LabGuardPos.x += mLabGuard->GetMovementSpeed() * Time::DeltaTime();

				// ���������� 0.5��ŭ �̵��ϸ� �������� �ٲٱ�
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

		// ���� ��ǥ +- 0.5f ���� ���� �÷��̾ ������
		if ((LabGuardPos.x - 0.5f <= PlayerPos.x) && (LabGuardPos.x + 0.5f >= PlayerPos.x))
		{
			// ���Ͱ� �÷��̾�� �����ʿ� ������
			if (LabGuardPos.x > PlayerPos.x)
			{
				LabGuardPos.x -= mLabGuard->GetMovementSpeed() * Time::DeltaTime();
				mLabGuard->SetDirection(eDirection::LEFT);
			}

			// ���Ͱ� �÷��̾�� ���ʿ� ������
			else if (LabGuardPos.x < PlayerPos.x)
			{
				LabGuardPos.x += mLabGuard->GetMovementSpeed() * Time::DeltaTime();
				mLabGuard->SetDirection(eDirection::RIGHT);
			}

			// +- 0.1 ������ �÷��̾ ������ attack
			else if ((LabGuardPos.x - 0.1f <= PlayerPos.x) && (LabGuardPos.x + 0.1f >= PlayerPos.x))
			{
				mLabGuard->SetStage(eStage::eAttack);
			}
		}

		// ���� ��ǥ +-0.5f ���� ���� �÷��̾ ������ search
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

		// ���� ��ǥ +- 0.1f �ȿ� �÷��̾� �����ϸ� �����ϱ�
		if ((LabGuardPos.x - 0.1f <= PlayerPos.x) && (LabGuardPos.x + 0.1f >= PlayerPos.x))
		{
			mLabGuard->SetStage(eStage::eChase);
		}

		// ���� ���� �÷��̾ ������ search
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
