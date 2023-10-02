#include "qoDoorSwitch.h"
#include "qoPlayer.h"
#include "qoBullet.h"
#include "qoCollider.h"
#include "qoTransform.h"
#include "qoRigidbody.h"

namespace qo
{
	DoorSwitch::DoorSwitch()
		: mIsActivated(false)
	{
	}

	DoorSwitch::~DoorSwitch()
	{
	}

	void DoorSwitch::Initialize()
	{
	}

	void DoorSwitch::Update()
	{
		GameObject::Update();
	}

	void DoorSwitch::LateUpdate()
	{
		GameObject::LateUpdate();
	}

	void DoorSwitch::Render()
	{
		GameObject::Render();
	}

	void DoorSwitch::OnCollisionEnter(Collider* other)
	{
		Bullet* bullet = dynamic_cast<Bullet*>(other->GetOwner());

		if (bullet != nullptr)
		{
			SetSwitch(true);
		}
	}

	void DoorSwitch::OnCollisionStay(Collider* other)
	{
	}

	void DoorSwitch::OnCollisionExit(Collider* other)
	{
	}
}
