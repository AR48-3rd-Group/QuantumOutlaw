#pragma once
#include "qoGameObject.h"

namespace qo
{
	class DoorSwitch : public GameObject
	{
	public:
		DoorSwitch();
		virtual ~DoorSwitch();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

		virtual void OnCollisionEnter(class Collider* other) override;
		virtual void OnCollisionStay(class Collider* other) override;
		virtual void OnCollisionExit(class Collider* other) override;

		void SetSwitch(bool activated) { mIsActivated = activated; }
		bool GetSwitch() { return mIsActivated; }

	private:
		bool mIsActivated;
	};
}
