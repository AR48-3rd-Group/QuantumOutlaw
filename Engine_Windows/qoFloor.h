#pragma once
#include "qoGameObject.h"

namespace qo
{
	class Floor : public GameObject
	{
	public:
		Floor();
		virtual ~Floor();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

		virtual void OnCollisionEnter(class Collider* other) override;
		virtual void OnCollisionStay(class Collider* other) override;
		virtual void OnCollisionExit(class Collider* other) override;

	private:
	};
}
