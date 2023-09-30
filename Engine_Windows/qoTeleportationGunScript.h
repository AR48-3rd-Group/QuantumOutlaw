#pragma once
#include "qoScript.h"

namespace qo
{
	class TeleportationGunScript : public Script
	{
	public:
		TeleportationGunScript();
		virtual ~TeleportationGunScript();

		void Initialize() override;
		void Update() override;
		void LateUpdate() override;
		void Render() override;

	private:
		void Shoot();
	};
}

