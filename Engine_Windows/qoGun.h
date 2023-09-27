#pragma once
#include "qoGameObject.h"

namespace qo
{
	class Player;
	class Gun : public GameObject
	{
		friend class GunScript;
	public:
		Gun(Player* owner, UINT bulletCount);
		virtual ~Gun();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

	private:
		Player* mPlayer;
		UINT	mBulletCount;
	};
}

