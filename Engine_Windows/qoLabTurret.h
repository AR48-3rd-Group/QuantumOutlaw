#pragma once
#include "qoEnemy.h"

namespace qo
{
	class LabTurret : public Enemy
	{
	public:
		LabTurret();
		virtual ~LabTurret();

		virtual void Search() override;
		virtual void Chase() override;
		virtual void Attack() override;
		virtual void Dead() override;
		virtual void TakeHit(int DamageAmount, math::Vector3 HitDir = Vector3::Zero) override;

	private:
	};
}

