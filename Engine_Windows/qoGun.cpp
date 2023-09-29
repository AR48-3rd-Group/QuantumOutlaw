#include "qoGun.h"

namespace qo
{
	Gun::Gun(eGunType type, Player* owner, UINT bulletCount)
		: mGunType(type)
		, mPlayer(owner)
		, mBulletCount(bulletCount)
	{
	}

	Gun::~Gun()
	{
	}

	bool Gun::BulletConsumption(UINT amount)
	{
		// 소모되는 양이 남아있는 탄알보다 많다면 실패처리
		if(mBulletCount - amount < 0)
			return false;

		mBulletCount -= amount;
		return true;
	}
}