#include "qoTeleportationGun.h"

namespace qo
{
	TeleportationGun::TeleportationGun(Player* owner, UINT bulletCount)
		: Gun(eGunType::Teleportation, owner, bulletCount)
		, mTargetBullet(nullptr)
	{
	}

	TeleportationGun::~TeleportationGun()
	{
	}

	void TeleportationGun::Initialize()
	{
		GameObject::Initialize();
	}

	void TeleportationGun::Update()
	{
		GameObject::Update();
	}

	void TeleportationGun::LateUpdate()
	{
		GameObject::LateUpdate();
	}

	void TeleportationGun::Render()
	{
		GameObject::Render();
	}
}