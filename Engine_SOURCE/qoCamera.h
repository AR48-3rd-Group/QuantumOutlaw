#pragma once

#include "qoGameObject.h"

namespace qo
{
	class Camera
	{
	public:
		static void Initialize();
		static void Update();

		static void SetTarget(GameObject* target) { mTarget = target; }
		static math::Vector3 CaculatePos(math::Vector3 pos) { return pos - mDiffDistance; }
		static void SetLookAt(math::Vector3 lookat) { mLookAt = lookat; }
		static math::Vector3 GetLookAt() { return mLookAt; }

	private:
		static math::Vector3 mResolution;
		static math::Vector3 mLookAt;
		static math::Vector3 mDiffDistance;
		static GameObject* mTarget;
	};
}


