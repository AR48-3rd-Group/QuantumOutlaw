#pragma once
#include "qoEnemy.h"

namespace qo
{
	class LabGuard : public Enemy
	{
	public:
		LabGuard();
		virtual ~LabGuard();

		virtual void Search() override;
		virtual void Chase() override;
		virtual void Attack() override;
		virtual void Dead() override;
		virtual void TakeHit(int DamageAmount, math::Vector3 HitDir = Vector3::Zero) override;

	private:
	};
}

