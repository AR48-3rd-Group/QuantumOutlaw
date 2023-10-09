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

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

	private:
		// FSM
		void Search();
		void Chase();
		void Attack();
		void Hit();
		void Dead();

		class LabGuard* mLabGuard;
	};

}
