#pragma once
#include "qoGameObject.h"

namespace qo
{
	class EventSwitch : public GameObject
	{
	public:
		EventSwitch();
		virtual ~EventSwitch();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

		virtual void OnCollisionEnter(class Collider* other) override;
		virtual void OnCollisionStay(class Collider* other) override;
		virtual void OnCollisionExit(class Collider* other) override;

		void SetEventActive(bool active) { mIsActive = active; }
		bool GetEventActive() { return mIsActive; }

	private:
		bool mIsActive;
	};
}
