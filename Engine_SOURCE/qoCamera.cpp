#include "qoCamera.h"
#include "qoInput.h"
#include "qoTime.h"

namespace qo
{
	math::Vector3 Camera::mResolution = {};
	math::Vector3 Camera::mLookAt = {};
	math::Vector3 Camera::mDiffDistance = {};
	GameObject* Camera::mTarget = nullptr;

	void Camera::Initialize()
	{
		mLookAt.x = 0.f;
		mLookAt.y = 0.f;
		mLookAt.z = 0.f;
	}

	void Camera::Update()
	{
		if (Input::GetKeyState(KEY_CODE::LEFT) == KEY_STATE::PRESSED)
		{
			mLookAt.x -= 1.f * Time::DeltaTime();
		}
		if (Input::GetKeyState(KEY_CODE::UP) == KEY_STATE::PRESSED)
		{
			mLookAt.y += 1.f * Time::DeltaTime();
		}
		if (Input::GetKeyState(KEY_CODE::DOWN) == KEY_STATE::PRESSED)
		{
			mLookAt.y -= 1.f * Time::DeltaTime();
		}
		if (Input::GetKeyState(KEY_CODE::RIGHT) == KEY_STATE::PRESSED)
		{
			mLookAt.x += 1.f * Time::DeltaTime();
		}

		mDiffDistance = mLookAt - math::Vector3(0.f, 0.f, 0.f);
	}
}