#pragma once
#include "qoGameObject.h"

namespace qo
{
    class Bullet : public GameObject
    {
	public:
		Bullet(Vector3 Dir);
		virtual ~Bullet();

		virtual void Initialize() = 0;
		virtual void Update() = 0;
		virtual void LateUpdate() = 0;
		virtual void Render() = 0;

		virtual void OnCollisionEnter(class Collider* other) = 0;
		virtual void OnCollisionStay(class Collider* other) = 0;
		virtual void OnCollisionExit(class Collider* other) = 0;

		Vector3 GetDirection() const { return mDir; }

	private:
		Vector3 mDir;
    };
}

