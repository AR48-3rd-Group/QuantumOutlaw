#pragma once
#include "qoUI.h"

namespace qo
{
	class HPUIBackGround : public UI
	{
	public:
		HPUIBackGround();
		virtual ~HPUIBackGround();

		void Initialize() override;
		void Update() override;
		void LateUpdate() override;
		void Render() override;
	};
}


