#pragma once
#include "qoGameObject.h"

namespace qo
{
	class LockedDoor : public GameObject
	{
	public:
		LockedDoor();
		virtual ~LockedDoor();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

		virtual void OnCollisionEnter(class Collider* other) override;
		virtual void OnCollisionStay(class Collider* other) override;
		virtual void OnCollisionExit(class Collider* other) override;

		void SetTag(int tag) { mTagNumber = tag; }
		int GetTag() { return mTagNumber; }

		void SetLocked(bool locked) { mIsLocked = locked; }
		bool GetLocked() { return mIsLocked; }

	private:
		bool mIsLocked;
		int mTagNumber;
	};
}
