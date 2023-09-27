#include "qoPlayerScript.h"
#include "qoTransform.h"
#include "qoGameObject.h"
#include "qoTime.h"
#include "qoInput.h"

namespace qo
{
	PlayerScript::PlayerScript()
	{
	}

	PlayerScript::~PlayerScript()
	{
	}

	void PlayerScript::Initialize()
	{
	}

	void PlayerScript::Update()
	{
		GameObject* obj = GetOwner();
		Transform* tr = obj->GetComponent<Transform>();
		Vector3 pos = tr->GetPosition();

		if (Input::GetKeyState(KEY_CODE::A) == KEY_STATE::PRESSED)
		{
			pos.x -= 1.f * Time::DeltaTime();
		}

		if (Input::GetKeyState(KEY_CODE::D) == KEY_STATE::PRESSED)
		{
			pos.x += 1.f * Time::DeltaTime();
		}

		tr->SetPosition(pos);
	}

	void PlayerScript::LateUpdate()
	{
	}

	void PlayerScript::Render()
	{
	}

}
