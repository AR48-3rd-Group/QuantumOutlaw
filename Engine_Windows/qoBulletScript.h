#pragma once
#include "qoScript.h"

namespace qo
{
	class BulletScript : public Script
	{
	public:
		BulletScript();
		virtual ~BulletScript();

		void Initialize() override;
		void Update() override;
		void LateUpdate() override;
		void Render() override;
	};
}

