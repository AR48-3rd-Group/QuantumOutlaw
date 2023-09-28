#include "qoCollider.h"
#include "qoGameObject.h"

namespace qo
{
	UINT Collider::mCollisionCount = 0;

	Collider::Collider()
		:
		Component(COMPONENTTYPE::COLLIDER)
		, mScale(math::Vector3(0.f, 0.f, 0.f))
		, mOffset(math::Vector3(0.f, 0.f, 0.f))
		, mAffectedCamera(true)
		, mCollisionNumber(mCollisionCount++)
	{
	}

	Collider::~Collider()
	{
	}

	void Collider::Initialize()
	{
	}

	void Collider::Update()
	{
	}

	void Collider::LateUpdate()
	{
	}

	void Collider::Render()
	{
	}

	void Collider::OnCollisionEnter(Collider* other)
	{
		GetOwner()->OnCollisionEnter(other);
	}

	void Collider::OnCollisionStay(Collider* other)
	{
		GetOwner()->OnCollisionStay(other);
	}

	void Collider::OnCollisionExit(Collider* other)
	{
		GetOwner()->OnCollisionExit(other);
	}
}