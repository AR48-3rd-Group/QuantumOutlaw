#include "qoSuperpositionGun.h"
#include "qoGameObject.h"
#include "qoPlayer.h"

namespace qo
{
	SuperpositionGun::SuperpositionGun(Player* owner, UINT bulletCount)
		: Gun(eGunType::Superposition, owner, bulletCount)
	{
	}

	SuperpositionGun::~SuperpositionGun()
	{
	}

	void SuperpositionGun::Initialize()
	{
		GameObject::Initialize();
	}

	void SuperpositionGun::Update()
	{
		GameObject::Update();
	}

	void SuperpositionGun::LateUpdate()
	{
		GameObject::LateUpdate();
	}

	void SuperpositionGun::Render()
	{
		GameObject::Render();
	}
}