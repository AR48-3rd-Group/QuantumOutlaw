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
		, mTransform(nullptr)
		, mRigidbody(nullptr)
		, mDuration(0.f)
	{
	}

	PlayerScript::~PlayerScript()
	{
	}

	void PlayerScript::Initialize()
	{
		mPlayer = dynamic_cast<Player*>(GetOwner());
		mTransform = mPlayer->GetComponent<Transform>();
		mRigidbody = mPlayer->GetComponent<Rigidbody>();

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
		case ePlayerState::Fall:
			Fall();
			break;
		case ePlayerState::Jump:
			Jump();
			break;
		case ePlayerState::Dash:
			Dash();
			break;
		case ePlayerState::Dead:
			Dead();
			break;
		default:
			break;
		}

		// =========================================================
		// �� ���� �̺�Ʈ
		// =========================================================
		if (Input::GetKeyState(KEY_CODE::N_1) == KEY_STATE::DOWN)
		{
			mPlayer->ChangeActiveGun(eGunType::Superposition);
		}
		else if (Input::GetKeyState(KEY_CODE::N_2) == KEY_STATE::DOWN)
		{
			mPlayer->ChangeActiveGun(eGunType::Entanglement);
		}
		else if (Input::GetKeyState(KEY_CODE::N_3) == KEY_STATE::DOWN)
		{
			mPlayer->ChangeActiveGun(eGunType::Teleportation);
		}
	}

	void PlayerScript::LateUpdate()
	{
		if (Input::GetKeyState(KEY_CODE::O) == KEY_STATE::DOWN)
		{
			mPlayer->mCurHp -= 10;
		}

		if (Input::GetKeyState(KEY_CODE::P) == KEY_STATE::DOWN)
		{
			mPlayer->mCurHp += 10;
		}

		if (Input::GetKeyState(KEY_CODE::G) == KEY_STATE::DOWN)
		{
			mPlayer->mbGodMode = !mPlayer->mbGodMode;
		}
	}

	void PlayerScript::Render()
	{
	}

	void PlayerScript::Idle()
	{
		// ���� �浹�� ���°� �ƴϸ� Fall ���·� ����
		if (!mRigidbody->GetGround())
		{
			mPlayer->mState = ePlayerState::Fall;
		}

		// Walk
		if (Input::GetKeyState(KEY_CODE::A) == KEY_STATE::DOWN
			|| Input::GetKeyState(KEY_CODE::A) == KEY_STATE::PRESSED)
		{
			mPlayer->mState = ePlayerState::Walk;
			mPlayer->mDir = eDirection::LEFT;
		}
		else if (Input::GetKeyState(KEY_CODE::D) == KEY_STATE::DOWN
			|| Input::GetKeyState(KEY_CODE::D) == KEY_STATE::PRESSED)
		{
			mPlayer->mState = ePlayerState::Walk;
			mPlayer->mDir = eDirection::RIGHT;
		}

		// Jump
		if (Input::GetKeyState(KEY_CODE::SPACE) == KEY_STATE::DOWN)
		{
			// ������ Colider Exit�� ���ؼ� ���� �߰�
			Vector3 pos = mTransform->GetPosition();
			mTransform->SetPosition(Vector3(pos.x, pos.y + 0.05f, pos.z));

			mRigidbody->SetGround(false);
			mRigidbody->AddVelocity(Vector3(0.f, mPlayer->mJumpPower, 0.f));
			mPlayer->mState = ePlayerState::Jump;
		}
	}

	void PlayerScript::Walk()
	{
		// ���� �浹�� ���°� �ƴϸ� Fall ���·� ����
		if (!mRigidbody->GetGround())
		{
			mPlayer->mState = ePlayerState::Fall;
		}

		// �¿� �̵�
		Vector3 pos = mTransform->GetPosition();

		if (Input::GetKeyState(KEY_CODE::A) == KEY_STATE::PRESSED)
		{
			pos.x -= mPlayer->mMoveSpeed * Time::DeltaTime();
			mPlayer->mDir = eDirection::LEFT;
		}

		if (Input::GetKeyState(KEY_CODE::D) == KEY_STATE::PRESSED)
		{
			pos.x += mPlayer->mMoveSpeed * Time::DeltaTime();
			mPlayer->mDir = eDirection::RIGHT;
		}

		mTransform->SetPosition(pos);

		// Jump
		if (Input::GetKeyState(KEY_CODE::SPACE) == KEY_STATE::DOWN)
		{
			// ������ Colider Exit�� ���ؼ� ���� �߰�
			Vector3 pos = mTransform->GetPosition();
			mTransform->SetPosition(Vector3(pos.x, pos.y + 0.05f, pos.z));

			mRigidbody->SetGround(false);
			mRigidbody->AddVelocity(Vector3(0.f, mPlayer->mJumpPower, 0.f));
			mPlayer->mState = ePlayerState::Jump;
		}
	}

	void PlayerScript::Fall()
	{
		// Idle
		if (mRigidbody->GetGround())
		{
			mPlayer->mState = ePlayerState::Idle;
		}

		// �¿� �̵�
		Vector3 pos = mTransform->GetPosition();

		if (Input::GetKeyState(KEY_CODE::A) == KEY_STATE::PRESSED)
		{
			pos.x -= mPlayer->mMoveSpeed * Time::DeltaTime();
			mPlayer->mDir = eDirection::LEFT;
		}

		if (Input::GetKeyState(KEY_CODE::D) == KEY_STATE::PRESSED)
		{
			pos.x += mPlayer->mMoveSpeed * Time::DeltaTime();
			mPlayer->mDir = eDirection::RIGHT;
		}

		mTransform->SetPosition(pos);

		// Dash
		if (Input::GetKeyState(KEY_CODE::SPACE) == KEY_STATE::DOWN)
		{
			Vector3 velocity = Vector3::Zero;

			if (mPlayer->mDir == eDirection::LEFT)
			{
				velocity.x -= mPlayer->mDashPower;
			}
			else if (mPlayer->mDir == eDirection::RIGHT)
			{
				velocity.x += mPlayer->mDashPower;
			}

			mRigidbody->AddVelocity(velocity);

			mPlayer->mState = ePlayerState::Dash;
			mDuration = 0.f;
		}
	}

	void PlayerScript::Jump()
	{
		// ���� �ӷ��� �Ʒ� �����̸� Fall ���·� ��ȯ
		if (mRigidbody->GetVelocity().y < 0.f)
		{
			mPlayer->mState = ePlayerState::Fall;
		}

		// �¿� �̵�
		Vector3 pos = mTransform->GetPosition();

		if (Input::GetKeyState(KEY_CODE::A) == KEY_STATE::PRESSED)
		{
			pos.x -= mPlayer->mMoveSpeed * Time::DeltaTime();
			mPlayer->mDir = eDirection::LEFT;
		}

		if (Input::GetKeyState(KEY_CODE::D) == KEY_STATE::PRESSED)
		{
			pos.x += mPlayer->mMoveSpeed * Time::DeltaTime();
			mPlayer->mDir = eDirection::RIGHT;
		}

		mTransform->SetPosition(pos);


		// Idle
		if (mRigidbody->GetGround())
		{
			mPlayer->mState = ePlayerState::Idle;
		}

		// Dash
		if (Input::GetKeyState(KEY_CODE::SPACE) == KEY_STATE::DOWN)
		{
			Vector3 velocity = Vector3::Zero;

			if (mPlayer->mDir == eDirection::LEFT)
			{
				velocity.x -= mPlayer->mDashPower;
			}
			else if (mPlayer->mDir == eDirection::RIGHT)
			{
				velocity.x += mPlayer->mDashPower;
			}

			mRigidbody->AddVelocity(velocity);

			mPlayer->mState = ePlayerState::Dash;
			mDuration = 0.f;
		}
	}

	void PlayerScript::Dash()
	{
		// Idle
		if (mRigidbody->GetGround())
		{
			// X�� �ӵ� �ʱ�ȭ
			Vector3 velocity = mRigidbody->GetVelocity();
			velocity.x = 0.f;
			mRigidbody->SetVelocity(velocity);

			mPlayer->mState = ePlayerState::Idle;
		}

		// ���� ����
		Vector3 pos = mTransform->GetPosition();

		if (Input::GetKeyState(KEY_CODE::A) == KEY_STATE::PRESSED)
		{
			mPlayer->mDir = eDirection::LEFT;
		}

		if (Input::GetKeyState(KEY_CODE::D) == KEY_STATE::PRESSED)
		{
			mPlayer->mDir = eDirection::RIGHT;
		}

		mTransform->SetPosition(pos);


		mDuration += Time::DeltaTime();
		if (mDuration > 1.f)
		{
			// X�� �ӵ� �ʱ�ȭ
			Vector3 velocity = mRigidbody->GetVelocity();
			velocity.x = 0.f;
			mRigidbody->SetVelocity(velocity);

			mPlayer->mState = ePlayerState::Fall;
			mDuration = 0.f;
		}
	}

	void PlayerScript::Dead()
	{
	}
}
