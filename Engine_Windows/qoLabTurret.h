#pragma once
#include "qoEnemy.h"

namespace qo
{
	class LabTurret : public Enemy
	{
	public:
		LabTurret();
		virtual ~LabTurret();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

		void SetPlayer(GameObject* player);

		virtual void TakeHit(int DamageAmount, math::Vector3 HitDir = Vector3::Zero) override;

		class Player* mPlayer;
	private:
	};
}

