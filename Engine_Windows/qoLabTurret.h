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
		virtual void Hit(int damage) override;
		virtual void Dead() override;

	private:
	};
}

