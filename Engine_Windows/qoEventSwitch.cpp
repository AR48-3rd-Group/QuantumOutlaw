#include "qoEventSwitch.h"
#include "qoPlayer.h"
#include "qoBullet.h"
#include "qoCollider.h"
#include "qoTransform.h"
#include "qoRigidbody.h"

namespace qo
{
	EventSwitch::EventSwitch()
		: mIsActive(false)
	{
	}

	EventSwitch::~EventSwitch()
	{
	}

	void EventSwitch::Initialize()
	{
	}

	void EventSwitch::Update()
	{
		GameObject::Update();
	}

	void EventSwitch::LateUpdate()
	{
		GameObject::LateUpdate();
	}

	void EventSwitch::Render()
	{
		GameObject::Render();
	}

	void EventSwitch::OnCollisionEnter(Collider* other)
	{
		Bullet* bullet = dynamic_cast<Bullet*>(other->GetOwner());

		if (bullet != nullptr)
		{
			SetEventActive(true);
		}
	}

	void EventSwitch::OnCollisionStay(Collider* other)
	{
	}

	void EventSwitch::OnCollisionExit(Collider* other)
	{
	}
}
