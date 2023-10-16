#include "qoSuperpositionBullet.h"
#include "qoGameObject.h"
#include "qoCollider.h"
#include "ArchitectureInclude.h"
#include "qoEnemy.h"

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
		Enemy* enemy = dynamic_cast<Enemy*>(other->GetOwner());
		Floor* floor = dynamic_cast<Floor*> (other->GetOwner());
		Wall* wall = dynamic_cast<Wall*> (other->GetOwner());
		LockedDoor* lockedDoor = dynamic_cast<LockedDoor*> (other->GetOwner());
		EventSwitch* eventSwitch = dynamic_cast<EventSwitch*> (other->GetOwner());
		
		// SuperpositionBullet Ư��ȿ�� 
		//DestuctibleWall* destuctibleWall = dynamic_cast<DestuctibleWall*> (other->GetOwner());
		//Barrier* barrier = dynamic_cast<Barrier*> (other->GetOwner());

		// �浹�� ��ü�� �ش� ��ü�� Bullet ����
		if (enemy == nullptr
			&& floor == nullptr
			&& wall == nullptr
			&& lockedDoor == nullptr
			&& eventSwitch == nullptr)
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

	void SuperpositionBullet::OnCollisionStay(Collider* other)
	{
	}

	void SuperpositionBullet::OnCollisionExit(Collider* other)
	{
	}
}