#include "qoGuard.h"

namespace qo
{
	Guard::Guard()
		: mState(eState::Serch)
	{
	}
	Guard::~Guard()
	{
	}
	void Guard::Initialize()
	{
		GameObject::Initialize();
	}
	void Guard::Update()
	{
		GameObject::Update();

		switch (mState)
		{
		case Guard::eState::Serch:
			break;
		case Guard::eState::Follow:
			break;
		case Guard::eState::Attack:
			break;
		case Guard::eState::Hit:
			break;
		case Guard::eState::Death:
			break;
		case Guard::eState::End:
			break;
		default:
			break;
		}
	}
	void Guard::LateUpdate()
	{
		GameObject::LateUpdate();
	}
	void Guard::Render()
	{
		GameObject::Render();
	}
}