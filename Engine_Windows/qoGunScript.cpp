#include "qoGunScript.h"
#include "qoGun.h"
#include "qoTransform.h"
#include "qoInput.h"

namespace qo
{
	GunScript::GunScript()
	{
	}

	GunScript::~GunScript()
	{
	}

	void GunScript::Initialize()
	{
	}

	void GunScript::Update()
	{
		// Gun의 위치를 플레이어 위치로 설정한다.
		Gun* owner = dynamic_cast<Gun*>(GetOwner());

		if (owner == nullptr)
			return;

		Transform* GunTransform = owner->GetComponent<Transform>();
		Transform* PlayerTransform = owner->GetPlayer()->GetComponent<Transform>();
		Vector3 GunPos = PlayerTransform->GetPosition();

		if(owner->GetPlayer()->GetDirection() == eDirection::LEFT)
		{
			GunPos -= Vector3(0.1f, 0.f, 0.f);
		}
		else if (owner->GetPlayer()->GetDirection() == eDirection::RIGHT)
		{
			GunPos += Vector3(0.1f, 0.f, 0.f);
		}		

		GunTransform->SetPosition(GunPos);

		// =======================
		// 탄알 전부 소모시 색상변경
		// =======================
		if (owner->GetCurBulletCount() <= 0)
		{
			GunTransform->SetColor(Vector4::Zero);
		}

		// =======================
		// 탄알 재장전
		// =======================
		if (Input::GetKeyState(KEY_CODE::R) == KEY_STATE::DOWN)
		{
			owner->ReLoad();
		}
	}

	void GunScript::LateUpdate()
	{
	}

	void GunScript::Render()
	{
	}
}