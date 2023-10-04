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

	public:
		void SetEntangle(bool Entangle) { mIsEntangle = Entangle; }
		void SetFirst(GameObject* first) { mFirst = first; }

	private:
		bool mIsEntangle;
		GameObject* mFirst;
		GameObject* mTarget;
	};
}

