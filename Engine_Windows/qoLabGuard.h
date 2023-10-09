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

		void SetStatus(Vector3 labguardPos) { pos = labguardPos; }

		virtual void Search() override;
		virtual void Chase() override;
		virtual void Attack() override;
		virtual void Dead() override;
		virtual void TakeHit(int DamageAmount, math::Vector3 HitDir = Vector3::Zero) override;

		int Dir; // right -> 1		Left -> -1

		Vector3 pos;
	private:
	};
}

