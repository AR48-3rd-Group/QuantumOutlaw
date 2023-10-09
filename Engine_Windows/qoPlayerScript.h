#pragma once
#include "..\\Engine_SOURCE\\qoScript.h"

namespace qo
{
	class PlayerScript : public Script
	{
	public:
		PlayerScript();
		virtual ~PlayerScript();

		void Initialize() override;
		void Update() override;
		void LateUpdate() override;
		void Render() override;

	private:
		// FSM
		void Idle();
		void Walk();
		void Fall();
		void Jump();
		void Dash();
		void Dead();

	private:
		class Player*		mPlayer;
		class Transform*	mTransform;
		class Rigidbody*	mRigidbody;

		float				mDuration;
	};
}
