#include "qoLabTurretScript.h"

namespace qo
{
	LabTurretScript::LabTurretScript()
		: mEnemy(nullptr)
	{
	}

	LabTurretScript::~LabTurretScript()
	{
	}

	void LabTurretScript::Initialize()
	{
	}

	void LabTurretScript::Update()
	{
		switch (mEnemy->GetStage())
		{
		case eStage::eSearch:
			mEnemy->Search();
			break;
		case eStage::eAttack:
			mEnemy->Attack();
			break;
		case eStage::eHit:
			//mEnemy->TakeHit();
			break;
		case eStage::eDead:
			mEnemy->Dead();
			break;
		default:
			break;
		}

		LabTurret* obj = dynamic_cast<LabTurret*>(GetOwner());

		if (obj != nullptr)
		{
			std::cout << "null";
		}

		Transform* tr = obj->GetComponent<Transform>();
		Vector3 pos = tr->GetPosition();
		pos.x -= 0.1f * Time::DeltaTime();
		tr->SetPosition(pos);
	}

	void LabTurretScript::LateUpdate()
	{
	}

	void LabTurretScript::Render()
	{
	}

}
