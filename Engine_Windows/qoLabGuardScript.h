#pragma once
#include "ES_CommonInclude.h"

namespace qo
{
	class LabGuardScript : public Script
	{
	public:
		LabGuardScript();
		virtual ~LabGuardScript();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

	private:
		void Search();
		void Chase();
		void Fall();
		void Attack();
		void Hit();
		void Dead();

		// labguard 穿号識情
		class LabGuard* mLabGuard;
		class Transform* mTransform;
		class Rigidbody* mRigidbody;
		Vector3 LabGuardPos;

		// player 穿号識情
		class Player* mPlayer;
		class Transform* mPlayerTr;
		Vector3 PlayerPos;
	};

}
