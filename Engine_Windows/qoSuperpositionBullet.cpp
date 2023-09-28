#include "qoSuperpositionBullet.h"
#include "qoGameObject.h"
#include "qoGround.h"
#include "qoCollider.h"

namespace qo
{
	SuperpositionBullet::SuperpositionBullet(Vector3 Dir)
		: Bullet(Dir)
	{
	}

	SuperpositionBullet::~SuperpositionBullet()
	{
	}

	void SuperpositionBullet::Initialize()
	{
		GameObject::Initialize();
	}

	void SuperpositionBullet::Update()
	{
		GameObject::Update();
	}

	void SuperpositionBullet::LateUpdate()
	{
		GameObject::LateUpdate();
	}

	void SuperpositionBullet::Render()
	{
		GameObject::Render();
	}

	void SuperpositionBullet::OnCollisionEnter(Collider* other)
	{
		Ground* Test = dynamic_cast<Ground*>(other->GetOwner());

		if (Test == nullptr)
			return;

		Destroy(this);
	}

	void SuperpositionBullet::OnCollisionStay(Collider* other)
	{
	}

	void SuperpositionBullet::OnCollisionExit(Collider* other)
	{
	}
}