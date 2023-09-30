#include "qoGun.h"
#include "qoTransform.h"

namespace qo
{
	Gun::Gun(eGunType type, Player* owner, UINT bulletCount)
		: mGunType(type)
		, mPlayer(owner)
		, mMaxBulletCount(bulletCount)
		, mCurBulletCount(mMaxBulletCount)
		, mGunColor(Vector4::Zero)
	{
		if (mGunType == eGunType::Superposition)
		{
			mGunColor = Vector4(1.0f, 0.f, 0.f, 0.f);
		}
		else if (mGunType == eGunType::Entanglement)
		{
			mGunColor = Vector4(0.f, 1.f, 0.f, 0.f);
		}
		else if (mGunType == eGunType::Teleportation)
		{
			mGunColor = Vector4(0.f, 0.f, 1.f, 0.f);
		}
	}

	Gun::~Gun()
	{
	}

	bool Gun::BulletConsumption(UINT amount)
	{
		// 소모되는 양이 남아있는 탄알보다 많다면 실패처리
		if(mCurBulletCount - amount < 0)
			return false;

		mCurBulletCount -= amount;
		return true;
	}

	void Gun::ReLoad()
	{
		mCurBulletCount = mMaxBulletCount; 
		GetComponent<Transform>()->SetColor(mGunColor);
	}
}