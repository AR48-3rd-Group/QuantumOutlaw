#pragma once

#include "qoUI.h"

namespace qo
{
	class HPUI : public UI
	{
	public:
		HPUI();
		virtual ~HPUI();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

	private:

	};
}


