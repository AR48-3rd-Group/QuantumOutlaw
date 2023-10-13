#pragma once
#include "qoEnemy.h"

namespace qo
{
	class LabGuard : public Enemy
	{
	public:
		LabGuard();
		virtual ~LabGuard();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

		void SetStatus(Vector3 Position) { Pos = Position; }
		void SetPlayer(GameObject* player);

		virtual void OnCollisionEnter(class Collider* other) override;
		virtual void OnCollisionStay(class Collider* other) override;
		virtual void OnCollisionExit(class Collider* other) override;

		virtual void TakeHit(int DamageAmount, math::Vector3 HitDir = Vector3::Zero) override;

		class Player* mPlayer;
		Vector3 Pos;

		float AttackTime;
	private:
	};
}

