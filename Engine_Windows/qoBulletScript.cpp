#include "qoBulletScript.h"
#include "qoBullet.h"
#include "qoTransform.h"
#include "qoTime.h"

namespace qo
{
	BulletScript::BulletScript()
	{
	}

	BulletScript::~BulletScript()
	{
	}

	void BulletScript::Initialize()
	{
	}

	void BulletScript::Update()
	{
		Bullet* bullet = dynamic_cast<Bullet*>(GetOwner());
		
		if (bullet == nullptr)
			return;
		
		// Bullet이 갖고있는 방향으로 초당 2.f 의 속도로 이동
		Transform* tr = bullet->GetComponent<Transform>();
		Vector3 dir = bullet->GetDirection();

		Vector3 pos = tr->GetPosition();

		dir.Normalize();

		pos += dir * 2.f * Time::DeltaTime();
		tr->SetPosition(pos);		
	}

	void BulletScript::LateUpdate()
	{
	}

	void BulletScript::Render()
	{
	}
}