#pragma once
#include "qoScript.h"

namespace qo
{
	class GunScript : public Script
	{
	public:
		GunScript();
		virtual ~GunScript();

		void Initialize() override;
		void Update() override;
		void LateUpdate() override;
		void Render() override;
	};
}

