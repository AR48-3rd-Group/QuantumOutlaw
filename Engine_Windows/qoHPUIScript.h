#pragma once

#include "qoUIScript.h"

namespace qo
{
	class HPUIScript : public UIScript
	{
	public:
		HPUIScript();
		virtual ~HPUIScript();

		void Initialize() override;
		void Update() override;
		void LateUpdate() override;
		void Render() override;

	private:
		UINT mMaxHP;
		UINT mCurHP;
	};
}


