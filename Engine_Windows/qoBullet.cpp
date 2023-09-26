#include "qoBullet.h"

namespace qo
{
	Bullet::Bullet(Vector3 Dir)
		: mDir(Dir)
	{
	}

	Bullet::~Bullet()
	{
	}

	void Bullet::Initialize()
	{
		GameObject::Initialize();
	}

	void Bullet::Update()
	{
		GameObject::Update();
	}

	void Bullet::LateUpdate()
	{
		GameObject::LateUpdate();
	}

	void Bullet::Render()
	{
		GameObject::Render();
	}
}