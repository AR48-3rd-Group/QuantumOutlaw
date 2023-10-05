#pragma once
#include "qoGameObject.h"

namespace qo
{
	enum evrDirection
	{
		VERTICAL,
		HORIZONTAL,
	};

	class Elevator : public GameObject
	{

	public:
		Elevator();
		virtual ~Elevator();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

		virtual void OnCollisionEnter(class Collider* other) override;
		virtual void OnCollisionStay(class Collider* other) override;
		virtual void OnCollisionExit(class Collider* other) override;

		void SetDirection(evrDirection dir) { mDirection = dir; }
		evrDirection GetType() const { return mDirection; }

		void SetActive(bool active) { mIsActive = active; }
		bool GetActive() { return mIsActive; }

		void SetTag(int tag) { mTagNumber = tag; }
		int GetTag() { return mTagNumber; }

		void SetRange(float range) { mMovementRange = range; }
		float GetRange() { return mMovementRange; }

		void SetTimer(float timer) { mTimer = timer; }
		float GetTimer() { return mTimer; }

		void ResetTimer();

	private:
		evrDirection mDirection;
		bool mIsActive;
		int mTagNumber;
		float mMovementRange;
		float mTimer;

		bool mTick;
	};
}
