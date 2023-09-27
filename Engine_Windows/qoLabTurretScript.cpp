#include "qoLabTurretScript.h"

namespace qo
{
	LabTurretScript::LabTurretScript()
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
