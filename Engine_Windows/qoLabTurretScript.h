#pragma once
#include "qoLabTurret.h"
#include "ES_CommonInclude.h"

namespace qo
{
	class LabTurretScript : public Script
	{
	public:
		LabTurretScript();
		virtual ~LabTurretScript();

		void Initialize() override;
		void Update() override;
		void LateUpdate() override;
		void Render() override;
	};

}
