#pragma once
#include "qoScript.h"

namespace qo
{
	class UIScript : public Script
	{
	public:
		UIScript();
		virtual ~UIScript();

		void Initialize() override;
		void Update() override;
		void LateUpdate() override;
		void Render() override;

	private:

	};
}


