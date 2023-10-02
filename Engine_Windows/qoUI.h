#pragma once

#include "qoGameObject.h"

namespace qo 
{
	class UI : public GameObject
	{
	public:
		UI();
		virtual ~UI();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

		virtual void OnCollisionEnter(Collider* other) override {};
		virtual void OnCollisionStay(Collider* other) override {};
		virtual void OnCollisionExit(Collider* other) override {};

	private:

	};
}


