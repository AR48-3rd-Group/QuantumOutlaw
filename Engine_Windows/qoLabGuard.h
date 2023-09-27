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

