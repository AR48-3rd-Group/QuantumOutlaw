#pragma once
#include "qoScript.h"

namespace qo
{
	class GuardScript : public Script
	{
	public:
		GuardScript();
		virtual ~GuardScript();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

	private:

	};
}