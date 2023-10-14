#pragma once

#include "qoComponent.h"

namespace qo
{
	class Rigidbody : public Component
	{
	public:
		Rigidbody();
		virtual ~Rigidbody();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

		void Clear() { mForce = math::Vector3(0.f, 0.f, 0.f); }

		void SetMass(float mass) { mfMass = mass; }
		void AddForce(math::Vector3 force) { mForce += force; }

		void SetVelocity(math::Vector3 velocity) { mVelocity = velocity; }
		void AddVelocity(math::Vector3 velocity) { mVelocity += velocity; }
		math::Vector3 GetVelocity() { return mVelocity; }

		void SetGround(bool ground) { mbGround = ground; }
		bool GetGround() { return mbGround; }

		void SetFriction(float friction) { mfFriction = friction; }
		float GetFriction() { return mfFriction; }

		void SetActive(bool active) { mbActive = active; }

	private:
		bool mbGround;

		float mfMass;
		float mfFriction;
		float mCoefficient;

		bool mbActive;

		math::Vector3 mVelocity;
		math::Vector3 mAccelation;
		math::Vector3 mForce;
		math::Vector3 mGravity;
		math::Vector3 mMaxGravity;
	};
}


