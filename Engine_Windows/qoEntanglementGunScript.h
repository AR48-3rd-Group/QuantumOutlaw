#pragma once
#include "qoScript.h"

namespace qo
{
	class EntanglementGunScript : public Script
	{
	public:
		EntanglementGunScript();
		virtual ~EntanglementGunScript();

		void Initialize() override;
		void Update() override;
		void LateUpdate() override;
		void Render() override;

	private:
		void Shoot();
	};
}

