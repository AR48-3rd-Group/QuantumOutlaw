#include "qoEntanglementGun.h"

namespace qo
{
	EntanglementGun::EntanglementGun(Player* owner, UINT bulletCount)
		: Gun(eGunType::Entanglement, owner, bulletCount)
	{
	}

	EntanglementGun::~EntanglementGun()
	{
	}

	void EntanglementGun::Initialize()
	{
		GameObject::Initialize();
	}

	void EntanglementGun::Update()
	{
		GameObject::Update();
	}

	void EntanglementGun::LateUpdate()
	{
		GameObject::LateUpdate();
	}

	void EntanglementGun::Render()
	{
		GameObject::Render();
	}
}