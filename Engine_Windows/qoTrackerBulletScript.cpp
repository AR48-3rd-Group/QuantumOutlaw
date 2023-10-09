#include "qoTrackerBulletScript.h"
#include "qoTrackerBullet.h"
#include "qoTransform.h"
#include "qoEnemy.h"

namespace qo
{
	TrackerBulletScript::TrackerBulletScript()
	{
	}

	TrackerBulletScript::~TrackerBulletScript()
	{
	}

	void TrackerBulletScript::Initialize()
	{
	}

	void TrackerBulletScript::Update()
	{
		Enemy* target = dynamic_cast<TrackerBullet*>(GetOwner())->GetTarget();

		if(target==nullptr)
			return;
		
		Transform* tr = GetOwner()->GetComponent<Transform>();
		Transform* targettr = target->GetComponent<Transform>();

		Vector3 Dir = Vector3(0.f, 0.f, 0.f);
		Dir.x = targettr->GetPosition().x - tr->GetPosition().x;
		Dir.y = targettr->GetPosition().y - tr->GetPosition().y;

		Dir.Normalize();

		tr->SetPosition(tr->GetPosition() += Dir * 2.f * Time::DeltaTime());
	}

	void TrackerBulletScript::LateUpdate()
	{
	}

	void TrackerBulletScript::Render()
	{
	}
}