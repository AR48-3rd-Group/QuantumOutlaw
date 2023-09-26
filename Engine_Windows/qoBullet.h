#pragma once
#include "qoGameObject.h"

namespace qo
{
    class Bullet : public GameObject
    {
		friend class BulletScript;
	public:
		Bullet(Vector3 Dir);
		virtual ~Bullet();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

	private:
		Vector3 mDir;
    };
}

