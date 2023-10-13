#pragma once

#include "qoGameObject.h"

namespace qo
{
	class Trigger : public GameObject
	{
	public:
		Trigger();
		virtual ~Trigger();

		void Initialize() override;
		void Update() override;
		void LateUpdate() override;
		void Render() override;

		void OnCollisionEnter(class Collider* other) override;
		void OnCollisionStay(class Collider* other) override;
		void OnCollisionExit(class Collider* other) override;

		void SetSceneName(std::wstring scenename) { mSceneName = scenename; }

	private:
		std::wstring mSceneName;

	};
}


