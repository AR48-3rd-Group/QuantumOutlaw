#include "qoTeleportationBullet.h"
#include "qoCollider.h"
#include "ArchitectureInclude.h"
#include "qoTeleportationGun.h"
#include "qoEnemy.h"

namespace qo
{
	TeleportationBullet::TeleportationBullet(TeleportationGun* onwer, Vector3 Dir)
		: Bullet(Dir)
		, mOwner(onwer)
	{
	}

	TeleportationBullet::~TeleportationBullet()
	{
		// �Ѿ� ������ Onwer �� Ÿ���� �� �Ѿ��̸� nullptr�� �ʱ�ȭ
		if (mOwner->GetTargetBullet() == this)
		{
			mOwner->SetTargetBullet(nullptr);
		}
	}

	void TeleportationBullet::Initialize()
	{
		GameObject::Initialize();
	}

	void TeleportationBullet::Update()
	{
		GameObject::Update();
	}

	void TeleportationBullet::LateUpdate()
	{
		GameObject::LateUpdate();
	}

	void TeleportationBullet::Render()
	{
		GameObject::Render();
	}

	void TeleportationBullet::OnCollisionEnter(Collider* other)
	{
		Enemy* enemy = dynamic_cast<Enemy*>(other->GetOwner());
		Floor* floor = dynamic_cast<Floor*> (other->GetOwner());
		Wall* wall = dynamic_cast<Wall*> (other->GetOwner());
		LockedDoor* lockedDoor = dynamic_cast<LockedDoor*> (other->GetOwner());
		EventSwitch* eventSwitch = dynamic_cast<EventSwitch*> (other->GetOwner());
		DestuctibleWall* destuctibleWall = dynamic_cast<DestuctibleWall*> (other->GetOwner());
		Barrier* barrier = dynamic_cast<Barrier*> (other->GetOwner());

		// �浹�� ��ü�� �ش� ��ü�� Bullet ����
		if (enemy == nullptr
			&& floor == nullptr
			&& wall == nullptr
			&& lockedDoor == nullptr
			&& eventSwitch == nullptr
			&& destuctibleWall == nullptr
			&& barrier == nullptr)
			return;

		// Enemy �ǰ� ó��
		if (enemy != nullptr)
		{
			Vector3 Dir = enemy->GetComponent<Transform>()->GetPosition() - GetComponent<Transform>()->GetPosition();
			Dir.Normalize();
			enemy->TakeHit(10, Dir);
		}

		Destroy(this);
	}

	void TeleportationBullet::OnCollisionStay(Collider* other)
	{
	}

	void TeleportationBullet::OnCollisionExit(Collider* other)
	{
	}
}