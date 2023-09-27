#pragma once
#include "qoLabGuard.h"
#include "ES_CommonInclude.h"

namespace qo
{
	class LabGuardScript : public Script
	{
	public:
		LabGuardScript();
		virtual ~LabGuardScript();

		void Initialize() override;
		void Update() override;
		void LateUpdate() override;
		void Render() override;
	};

}
