#include "qoGun.h"


namespace qo
{
	Gun::Gun(Player* owner, UINT bulletCount)
		: mPlayer(owner)
		, mBulletCount(bulletCount)
	{
	}

	Gun::~Gun()
	{
	}

	void Gun::Initialize()
	{
		GameObject::Initialize();
	}

	void Gun::Update()
	{
		GameObject::Update();
	}

	void Gun::LateUpdate()
	{
		GameObject::LateUpdate();
	}

	void Gun::Render()
	{
		GameObject::Render();
	}
}