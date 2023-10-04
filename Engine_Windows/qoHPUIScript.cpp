#include "qoHPUIScript.h"
#include "qoTransform.h"
#include "qoGameObject.h"
#include "qoInput.h"
#include "qoHPUI.h"
#include "qoApplication.h"

extern qo::Application application;

namespace qo
{
	HPUIScript::HPUIScript()
		: mMaxHP(100)
		, mCurHP(100)
	{
		
	}

	HPUIScript::~HPUIScript()
	{
	}

	void HPUIScript::Initialize()
	{
	}

	void HPUIScript::Update()
	{
		if (Input::GetKeyState(KEY_CODE::O) == KEY_STATE::DOWN)
		{
			mCurHP -= 1;
		}
		
		if (Input::GetKeyState(KEY_CODE::P) == KEY_STATE::DOWN)
		{
			mCurHP += 1;
		}
	}

	void HPUIScript::LateUpdate()
	{
		Vector3 HPpos = GetOwner()->GetComponent<Transform>()->GetPosition();
		Vector3 HPscale = GetOwner()->GetComponent<Transform>()->GetScale();
		Vector3 HPfixedpos = dynamic_cast<HPUI*>(GetOwner())->GetFixedPosition();
		Vector3 HPfixedscale = dynamic_cast<HPUI*>(GetOwner())->GetFixedScale();

		Vector3 HPnormalizedfixedpos = Vector3(0.f, 0.f, 0.f);
		Vector3 HPnomalizedfixedscale = Vector3(0.f, 0.f, 0.f);

		HPnormalizedfixedpos.x = (2.0f * HPfixedpos.x) / static_cast<float>(application.GetWidth()) - 1.0f;
		HPnormalizedfixedpos.y = (2.0f * HPfixedpos.y) / static_cast<float>(application.GetHeight()) - 1.0f;

		HPnomalizedfixedscale.x = (2.0f * HPfixedscale.x) / static_cast<float>(application.GetWidth());
		HPnomalizedfixedscale.y = (2.0f * HPfixedscale.y) / static_cast<float>(application.GetHeight());

		float scale = HPnomalizedfixedscale.x * static_cast<float>(mCurHP) / static_cast<float>(mMaxHP);
		float pos = HPnormalizedfixedpos.x - ((HPnomalizedfixedscale.x - HPnomalizedfixedscale.x * (static_cast<float>(mCurHP) / static_cast<float>(mMaxHP))) / 2.f);

		HPscale.x = scale;
		HPpos.x = pos;

		GetOwner()->GetComponent<Transform>()->SetPosition(HPpos);
		GetOwner()->GetComponent<Transform>()->SetScale(HPscale);
	}

	void HPUIScript::Render()
	{
	}
}