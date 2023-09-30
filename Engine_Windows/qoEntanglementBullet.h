#pragma once
#include "qoBullet.h"

namespace qo
{
	class EntanglementBullet : public Bullet
	{
	public:
		EntanglementBullet(Vector3 Dir);
		virtual ~EntanglementBullet();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

		virtual void OnCollisionEnter(class Collider* other) override;
		virtual void OnCollisionStay(class Collider* other) override;
		virtual void OnCollisionExit(class Collider* other) override;
	};
}

