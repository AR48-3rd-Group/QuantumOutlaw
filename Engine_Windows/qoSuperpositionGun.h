#pragma once
#include "qoGun.h"

namespace qo
{
	class SuperpositionGun : public Gun
	{
	public:
		SuperpositionGun(Player* owner, UINT bulletCount);
		virtual ~SuperpositionGun();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;
	};
}

