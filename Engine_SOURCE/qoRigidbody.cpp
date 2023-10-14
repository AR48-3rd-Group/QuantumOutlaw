#include "qoRigidbody.h"
#include "qoTime.h"
#include "qoTransform.h"
#include "qoGameObject.h"

namespace qo
{
	Rigidbody::Rigidbody()
		:
		Component(COMPONENTTYPE::RIGIDBODY)
		, mfMass(1.f)
		, mVelocity(math::Vector3(0.f, 0.f, 0.f))
		, mAccelation(math::Vector3(0.f, 0.f, 0.f))
		, mForce(math::Vector3(0.f, 0.f, 0.f))
		, mfFriction(0.5f)
		, mCoefficient(0.002f)
		, mbGround(false)
		, mbActive(true)
	{
		mGravity = math::Vector3(0.f, 2.5f, 0.f);
		mMaxGravity = math::Vector3(10.f, 10.f,0.f);
	}

	Rigidbody::~Rigidbody()
	{
	}

	void Rigidbody::Initialize()
	{
	}

	void Rigidbody::Update()
	{
		if (!mbActive)
			return;

		mAccelation = mForce / mfMass;

		mVelocity += math::Vector3(mAccelation.x * Time::DeltaTime(), mAccelation.y * Time::DeltaTime(), 0.f);

		if (mbGround)
		{
			math::Vector3 gravity = mGravity;
			gravity.Normalize();
			float dot = math::Dot(mVelocity, gravity);
			mVelocity -= gravity * dot;
		}
		else
		{
			mVelocity -= math::Vector3(mGravity.x * Time::DeltaTime(), mGravity.y * Time::DeltaTime(), mGravity.z * Time::DeltaTime());
		}

		math::Vector3 gravity = mGravity;
		gravity.Normalize();
		float dot = math::Dot(mVelocity, gravity);
		gravity = gravity * dot;

		math::Vector3 SideGravity = mVelocity - gravity;
		if (mMaxGravity.y < gravity.Length())
		{
			gravity.Normalize();
			gravity.y *= mMaxGravity.y;
		}

		if (mMaxGravity.x < SideGravity.Length())
		{
			SideGravity.Normalize();
			SideGravity.x *= mMaxGravity.x;
		}
		mVelocity = gravity + SideGravity;

		if (!(mVelocity == math::Vector3(0.f, 0.f, 0.f)))
		{
			math::Vector3 friction = -mVelocity;
			friction.Normalize();
			friction = friction * mfFriction * mfMass * Time::DeltaTime();

			if (mVelocity.Length() < friction.Length())
			{
				mVelocity = math::Vector3(0.f, 0.f, 0.f);
			}
			else
			{
				mVelocity += friction;
			}
		}

		Transform* tr = GetOwner()->GetComponent<Transform>();
		tr->SetPosition(tr->GetPosition() + math::Vector3(mVelocity.x * Time::DeltaTime(), mVelocity.y * Time::DeltaTime(), mVelocity.z * Time::DeltaTime()));
		Clear();
	}

	void Rigidbody::LateUpdate()
	{
	}

	void Rigidbody::Render()
	{
	}
}