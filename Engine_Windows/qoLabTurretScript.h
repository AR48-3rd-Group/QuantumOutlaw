#pragma once
#include "ES_CommonInclude.h"

namespace qo
{
	class LabTurretScript : public Script
	{
	public:
		LabTurretScript();
		virtual ~LabTurretScript();

		void Initialize() override;
		void Update() override;
		void LateUpdate() override;
		void Render() override;

	private:
		void Search();
		void Fall();
		void Attack();
		void Hit();
		void Dead();

		// LabTurret ���漱��
		class LabTurret* mLabTurret;
		class Transform* mTransform;
		class Rigidbody* mRigidbody;
		Vector3 LabTurretPos;

		// player ���漱��
		class Player* mPlayer;
		class Transform* mPlayerTr;
		Vector3 PlayerPos;

		float AttackTime;
		float mDamagedDlay;
	};

}
