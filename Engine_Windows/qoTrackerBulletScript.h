#pragma once

#include "qoScript.h"

namespace qo
{
	class TrackerBulletScript : public Script
	{
	public:
		TrackerBulletScript();
		virtual ~TrackerBulletScript();

		void Initialize() override;
		void Update() override;
		void LateUpdate() override;
		void Render() override;
	};
}


