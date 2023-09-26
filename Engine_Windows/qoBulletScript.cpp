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
		
		// Bullet이 갖고있는 방향으로 초당 5.f 의 속도로 이동
		if (bullet != nullptr)
		{
			Transform* tr = bullet->GetComponent<Transform>();
			Vector3 dir = bullet->mDir;

			Vector3 pos = tr->GetPosition();

			dir.Normalize();

			pos += dir * 5.f * Time::DeltaTime();
			tr->SetPosition(pos);
		}
	}

	void BulletScript::LateUpdate()
	{
	}

	void BulletScript::Render()
	{
	}
}