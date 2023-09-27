#pragma once
#include "..\\Engine_SOURCE\\qoScript.h"

namespace qo
{
	class PlayerScript : public Script
	{
	public:
		PlayerScript();
		virtual ~PlayerScript();

		void Initialize() override;
		void Update() override;
		void LateUpdate() override;
		void Render() override;
	};
}
