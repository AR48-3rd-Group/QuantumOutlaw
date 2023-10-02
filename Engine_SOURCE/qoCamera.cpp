#include "qoCamera.h"
#include "qoInput.h"
#include "qoTime.h"
#include "qoTransform.h"

namespace qo
{
	math::Vector3 Camera::mResolution = {};
	math::Vector3 Camera::mLookAt = {};
	math::Vector3 Camera::mDiffDistance = {};
	GameObject* Camera::mTarget = nullptr;

	CAM_EFFECT Camera::mCurCamEffect = CAM_EFFECT::None;
	std::list<tCamEffect> Camera::m_listCamEffect = {};

	void Camera::Initialize()
	{
		mLookAt.x = 0.f;
		mLookAt.y = 0.f;
		mLookAt.z = 0.f;
	}

	void Camera::Update()
	{
		if (m_listCamEffect.empty())
		{
			if (mTarget != nullptr)
			{
				Vector3 TargetPosition = mTarget->GetComponent<Transform>()->GetPosition();
				mLookAt = TargetPosition;
			}
		}
		else
		{
			if (mTarget != nullptr)
			{
				tCamEffect& effect = m_listCamEffect.front();

				mCurCamEffect = effect.eEffect;
				effect.fCurTime += Time::DeltaTime();

				Vector3 TargetPosition = mTarget->GetComponent<Transform>()->GetPosition();
				if (effect.eShakeDir == ShakeDir::Horizontal)
				{
					mLookAt.x = TargetPosition.x + cosf(effect.fCurTime * effect.fSpeed) * effect.fDistance;
				}
				else if (effect.eShakeDir == ShakeDir::Vertical)
				{
					mLookAt.y = TargetPosition.y - sinf(effect.fCurTime * effect.fSpeed) * effect.fDistance;
				}
				else if (effect.eShakeDir == ShakeDir::Comprehensive)
				{
					mLookAt.x = TargetPosition.x + cosf(effect.fCurTime * effect.fSpeed) * effect.fDistance;
					mLookAt.y = TargetPosition.y - sinf(effect.fCurTime * effect.fSpeed) * effect.fDistance;
				}

				if (effect.fCurTime > effect.fDuration)
				{
					mCurCamEffect = CAM_EFFECT::None;
					m_listCamEffect.pop_front();
				}
			}
		}

		mDiffDistance = mLookAt - math::Vector3(0.f, 0.f, 0.f);
	}
}