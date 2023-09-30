#include "qoPlayerScript.h"
#include "qoTransform.h"
#include "qoGameObject.h"
#include "qoTime.h"
#include "qoInput.h"
#include "qoPlayer.h"
#include "qoRigidbody.h"

namespace qo
{
	PlayerScript::PlayerScript()
		: mPlayer(nullptr)
	{
	}

	PlayerScript::~PlayerScript()
	{
	}

	void PlayerScript::Initialize()
	{
		mPlayer = dynamic_cast<Player*>(GetOwner());

		assert(mPlayer);
	}

	void PlayerScript::Update()
	{		
		switch (mPlayer->mState)
		{
		case ePlayerState::Idle :
			Idle();
			break;
		case ePlayerState::Walk:
			Walk();
			break;
		case ePlayerState::Jump:
			Jump();
			break;
		case ePlayerState::Dead:
			Dead();
			break;
		default:
			break;
		}
	}

	void PlayerScript::LateUpdate()
	{
	}

	void PlayerScript::Render()
	{
	}

	void PlayerScript::Idle()
	{
		// Walk
		if (Input::GetKeyState(KEY_CODE::A) == KEY_STATE::DOWN
			|| Input::GetKeyState(KEY_CODE::A) == KEY_STATE::PRESSED
			|| Input::GetKeyState(KEY_CODE::D) == KEY_STATE::DOWN
			|| Input::GetKeyState(KEY_CODE::D) == KEY_STATE::PRESSED)
		{
			mPlayer->mState = ePlayerState::Walk;
		}

		// Jump
		if (Input::GetKeyState(KEY_CODE::SPACE) == KEY_STATE::DOWN)
		{
			Rigidbody* rigidbody = mPlayer->GetComponent<Rigidbody>();

			rigidbody->SetGround(false);
			rigidbody->SetVelocity(Vector3(0.f, 1.5f, 0.f));
			mPlayer->mState = ePlayerState::Jump;
		}
	}

	void PlayerScript::Walk()
	{
		// ÁÂ¿ì ÀÌµ¿
		Transform* tranform = mPlayer->GetComponent<Transform>();
		Vector3 pos = tranform->GetPosition();

		if (Input::GetKeyState(KEY_CODE::A) == KEY_STATE::PRESSED)
		{
			pos.x -= mPlayer->mSpeed * Time::DeltaTime();
		}

		if (Input::GetKeyState(KEY_CODE::D) == KEY_STATE::PRESSED)
		{
			pos.x += mPlayer->mSpeed * Time::DeltaTime();
		}
		tranform->SetPosition(pos);

		// Jump
		if (Input::GetKeyState(KEY_CODE::SPACE) == KEY_STATE::DOWN)
		{
			Rigidbody* rigidbody = mPlayer->GetComponent<Rigidbody>();

			rigidbody->SetGround(false);
			rigidbody->SetVelocity(Vector3(0.f, 0.5f, 0.f));
			mPlayer->mState = ePlayerState::Jump;
		}
	}

	void PlayerScript::Jump()
	{
		// ÁÂ¿ì ÀÌµ¿
		Transform* tranform = mPlayer->GetComponent<Transform>();
		Vector3 pos = tranform->GetPosition();

		if (Input::GetKeyState(KEY_CODE::A) == KEY_STATE::PRESSED)
		{
			pos.x -= mPlayer->mSpeed * Time::DeltaTime();
		}

		if (Input::GetKeyState(KEY_CODE::D) == KEY_STATE::PRESSED)
		{
			pos.x += mPlayer->mSpeed * Time::DeltaTime();
		}
		tranform->SetPosition(pos);


		// Idle
		Rigidbody* rigidbody = mPlayer->GetComponent<Rigidbody>();

		if (rigidbody->GetGround())
		{
			mPlayer->mState = ePlayerState::Idle;
		}
	}

	void PlayerScript::Dead()
	{
	}

}
