#include "qoLabGuardScript.h"

namespace qo
{
	LabGuardScript::LabGuardScript()
	{
	}

	LabGuardScript::~LabGuardScript()
	{
	}

	void LabGuardScript::Initialize()
	{
	}

	void LabGuardScript::Update()
	{
		LabGuard* obj = dynamic_cast<LabGuard*>(GetOwner());

		if (obj != nullptr)
		{
			std::cout << "null";
		}

		Transform* tr = obj->GetComponent<Transform>();
		Vector3 pos = tr->GetPosition();
		pos.x += 0.1f * Time::DeltaTime();
		tr->SetPosition(pos);
	}

	void LabGuardScript::LateUpdate()
	{
	}

	void LabGuardScript::Render()
	{
	}

}
