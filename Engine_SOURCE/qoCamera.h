#pragma once

#include "qoGameObject.h"

namespace qo
{
	enum class CAM_EFFECT
	{
		Shake,
		None
	};

	enum class ShakeDir
	{
		Vertical,
		Horizontal,
		Comprehensive,
		None
	};

	struct tCamEffect
	{
		CAM_EFFECT eEffect;
		float fDuration;
		float fCurTime;
		ShakeDir eShakeDir;
		float fDistance;
		float fSpeed;
	};

	class Camera
	{
	public:
		static void Initialize();
		static void Update();

		static void SetTarget(GameObject* target) { mTarget = target; }
		static math::Vector3 CaculatePos(math::Vector3 pos) { return pos - mDiffDistance; }
		static void SetLookAt(math::Vector3 lookat) { mLookAt = lookat; }
		static math::Vector3 GetLookAt() { return mLookAt; }
		static void SetLimitLookAt(math::Vector3 limitlookat) { mLimitLookAt = limitlookat; }

	public:
		static void ShakeCam(float _fDuration, ShakeDir _eShakeDir, float _fDistance, float _fSpeed)
		{
			tCamEffect ef = {};
			ef.eEffect = CAM_EFFECT::Shake;
			ef.eShakeDir = _eShakeDir;
			ef.fDuration = _fDuration;
			ef.fCurTime = 0.f;
			ef.fDistance = _fDistance;
			ef.fSpeed = _fSpeed;

			m_listCamEffect.push_back(ef);
		}

	private:
		static math::Vector3 mResolution;
		static math::Vector3 mLookAt;
		static math::Vector3 mDiffDistance;
		static GameObject* mTarget;

		// ¸®¹ÌÆ®
		static math::Vector3 mLimitLookAt;

		static CAM_EFFECT mCurCamEffect;
		static std::list<tCamEffect> m_listCamEffect;
	};
}


