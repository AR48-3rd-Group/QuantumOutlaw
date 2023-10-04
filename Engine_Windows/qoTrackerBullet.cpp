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
		Floor* floor = dynamic_cast<Floor*> (other->GetOwner());
		Wall* wall = dynamic_cast<Wall*> (other->GetOwner());
		LockedDoor* lockedDoor = dynamic_cast<LockedDoor*> (other->GetOwner());
		DoorSwitch* doorSwitch = dynamic_cast<DoorSwitch*> (other->GetOwner());
		DestuctibleWall* destuctibleWall = dynamic_cast<DestuctibleWall*> (other->GetOwner());
		Barrier* barrier = dynamic_cast<Barrier*> (other->GetOwner());

		// 충돌한 객체가 해당 객체면 Bullet 삭제
		if (floor == nullptr
			&& wall == nullptr
			&& lockedDoor == nullptr
			&& doorSwitch == nullptr
			&& destuctibleWall == nullptr
			&& barrier == nullptr)
			return;

		Destroy(this);
	}

	void TrackerBullet::OnCollisionStay(Collider* other)
	{
	}

	void TrackerBullet::OnCollisionExit(Collider* other)
	{
	}
}