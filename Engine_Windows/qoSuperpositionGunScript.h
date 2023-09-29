#pragma once
#include "qoScript.h"

namespace qo
{
	class SuperpositionGunScript : public Script
	{
	public:
		SuperpositionGunScript();
		virtual ~SuperpositionGunScript();

		void Initialize() override;
		void Update() override;
		void LateUpdate() override;
		void Render() override;

	private:
		void Shoot();

	};
}

