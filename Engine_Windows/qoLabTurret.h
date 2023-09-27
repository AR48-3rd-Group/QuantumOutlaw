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
		eType myTYPE;
		eStage mySTAGE;

		int myHP;
		int mySPEED;
		int myATK;
	};
}

