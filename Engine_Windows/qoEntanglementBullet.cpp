#include "qoEntanglementBullet.h"

namespace qo
{
	EntanglementBullet::EntanglementBullet(Vector3 Dir)
		: Bullet(Dir)
	{
	}

	EntanglementBullet::~EntanglementBullet()
	{
	}

	void EntanglementBullet::Initialize()
	{
		GameObject::Initialize();
	}

	void EntanglementBullet::Update()
	{
		GameObject::Update();
	}

	void EntanglementBullet::LateUpdate()
	{
		GameObject::LateUpdate();
	}

	void EntanglementBullet::Render()
	{
		GameObject::Render();
	}

	void EntanglementBullet::OnCollisionEnter(Collider* other)
	{
	}

	void EntanglementBullet::OnCollisionStay(Collider* other)
	{
	}

	void EntanglementBullet::OnCollisionExit(Collider* other)
	{
	}
}