#pragma once
#include "qoGun.h"

namespace qo
{
	class TeleportationGun : public Gun
	{
	public:
		TeleportationGun(Player* owner, UINT bulletCount);
		virtual ~TeleportationGun();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;
	};
}

