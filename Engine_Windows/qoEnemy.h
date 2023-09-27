#pragma once
#include "qoGameObject.h"
#include "qoTransform.h"
#include "qoTime.h"

namespace qo
{
	enum eType
	{
		eMelee,
		eRanged,
	};

	enum eStage
	{
		eSearch,
		eChase,
		eAttack,
		eHit,
		eDead,
	};

	class Enemy : public GameObject
	{
	public:
		Enemy();
		virtual ~Enemy();

		// Get-Set 함수
		eType GetType() const { return myTYPE; }
		void SetType(eType type) { myTYPE = type; }

		eStage GetStage() const { return mySTAGE; }
		void SetStage(eStage stage) { mySTAGE = stage; }

		int GetHP() const { return myHP; }
		void SetHP(int hp) { myHP = hp; }

		int GetMovementSpeed() const { return mySPEED; }
		void SetMovementSpeed(int speed) { mySPEED = speed; }

		int GetATK() const { return myATK; }
		void SetATK(int atk) { myATK = atk; }

		// 공통으로 사용할 메서드
		virtual void Search();
		virtual void Chase();
		virtual void Attack();
		virtual void Hit(int damage) { myHP -= damage; }
		virtual void Dead();

	private:
		eType myTYPE;
		eStage mySTAGE;

		int myHP;
		int mySPEED;
		int myATK;
	};
}

