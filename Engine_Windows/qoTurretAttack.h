#pragma once
#include "qoBullet.h"

namespace qo
{
	class TurretAttack : public Bullet
	{
	public:
		TurretAttack(Vector3 Dir);
		virtual ~TurretAttack();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

		virtual void OnCollisionEnter(class Collider* other);
		virtual void OnCollisionStay(class Collider* other);
		virtual void OnCollisionExit(class Collider* other);

	private:
	};

}

