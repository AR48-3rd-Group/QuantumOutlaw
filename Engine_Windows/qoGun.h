#pragma once
#include "qoGameObject.h"
#include "qoPlayer.h"

namespace qo
{
	class Player;
	class Gun : public GameObject
	{
	public:
		Gun(eGunType type, Player* owner, UINT bulletCount);
		virtual ~Gun();

		virtual void Initialize() = 0;
		virtual void Update() = 0;
		virtual void LateUpdate()  = 0;
		virtual void Render() = 0;

		eGunType GetGunType() const { return mGunType; }

		Player* GetPlayer() const { return mPlayer; }

		UINT GetCurBulletCount() const { return mCurBulletCount; }
		bool BulletConsumption(UINT amount);
		void ReLoad();

		Vector4 GetGunColor() const { return mGunColor; }

	private:
		eGunType	mGunType;
		Player*		mPlayer;
		UINT		mMaxBulletCount;
		UINT		mCurBulletCount;
		Vector4		mGunColor;
	};
}

