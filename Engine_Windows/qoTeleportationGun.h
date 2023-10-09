#pragma once
#include "qoGun.h"

namespace qo
{
	class TeleportationBullet;
	class TeleportationGun : public Gun
	{
	public:
		TeleportationGun(Player* owner, UINT bulletCount);
		virtual ~TeleportationGun();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

		void SetTargetBullet(TeleportationBullet* targetBullet) { mTargetBullet = targetBullet; };
		TeleportationBullet* GetTargetBullet() const { return mTargetBullet; }

	private:
		TeleportationBullet* mTargetBullet;
		
	};
}

