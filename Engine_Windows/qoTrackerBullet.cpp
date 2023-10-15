#include "qoTrackerBullet.h"
#include "qoEnemy.h"
#include "ArchitectureInclude.h"
#include "qoCollider.h"

namespace qo
{
	TrackerBullet::TrackerBullet(Enemy* target)
		: Bullet(Vector3::Zero)
		, mTarget(target)
	{
	}

	TrackerBullet::~TrackerBullet()
	{
	}

	void TrackerBullet::Initialize()
	{
		GameObject::Initialize();
	}

	void TrackerBullet::Update()
	{
		GameObject::Update();

		if (mTarget != nullptr && mTarget->GetGameObjectState() == eState::Dead)
		{
			mTarget = nullptr;
		}
	}

	void TrackerBullet::LateUpdate()
	{
		GameObject::LateUpdate();
	}

	void TrackerBullet::Render()
	{
		GameObject::Render();
	}

	void TrackerBullet::OnCollisionEnter(Collider* other)
	{
		Enemy* enemy = dynamic_cast<Enemy*>(other->GetOwner());
		Floor* floor = dynamic_cast<Floor*> (other->GetOwner());
		Wall* wall = dynamic_cast<Wall*> (other->GetOwner());
		LockedDoor* lockedDoor = dynamic_cast<LockedDoor*> (other->GetOwner());
		EventSwitch* eventSwitch = dynamic_cast<EventSwitch*> (other->GetOwner());
		DestuctibleWall* destuctibleWall = dynamic_cast<DestuctibleWall*> (other->GetOwner());
		Barrier* barrier = dynamic_cast<Barrier*> (other->GetOwner());

		// 충돌한 객체가 해당 객체면 Bullet 삭제

		if (mFirst == enemy)
			return;

		if (enemy == nullptr
			&& floor == nullptr
			&& wall == nullptr
			&& lockedDoor == nullptr
			&& eventSwitch == nullptr
			&& destuctibleWall == nullptr
			&& barrier == nullptr)
			return;

		// Enemy 피격 처리
		if (enemy != nullptr)
		{
			Vector3 Dir = enemy->GetComponent<Transform>()->GetPosition() - GetComponent<Transform>()->GetPosition();
			Dir.Normalize();
			enemy->TakeHit(10, Dir);
		}

		Destroy(this);
	}

	void TrackerBullet::OnCollisionStay(Collider* other)
	{
	}

	void TrackerBullet::OnCollisionExit(Collider* other)
	{
	}
}