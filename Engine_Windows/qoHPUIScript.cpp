#include "qoHPUIScript.h"
#include "qoTransform.h"
#include "qoGameObject.h"
#include "qoInput.h"

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

		float scale = 0.25f * static_cast<float>(mCurHP) / static_cast<float>(mMaxHP);
		float pos = -0.875f - ((0.25f - 0.25f * (static_cast<float>(mCurHP) / static_cast<float>(mMaxHP))) / 2.f);

		HPscale.x = scale;
		HPpos.x = pos;

		GetOwner()->GetComponent<Transform>()->SetPosition(HPpos);
		GetOwner()->GetComponent<Transform>()->SetScale(HPscale);
	}

	void HPUIScript::Render()
	{
	}
}