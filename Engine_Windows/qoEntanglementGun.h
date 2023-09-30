#pragma once
#include "qoGun.h"

namespace qo
{
	class EntanglementGun : public Gun
	{
	public:
		EntanglementGun(Player* owner, UINT bulletCount);
		virtual ~EntanglementGun();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;
	};
}

