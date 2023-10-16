#include "qoPlayer.h"
#include "qoGun.h"
#include "qoGunScript.h"
#include "qoTransform.h"
#include "qoMeshRenderer.h"
#include "qoResourceManager.h"
#include "qoSuperpositionGun.h"
#include "qoEntanglementGun.h"
#include "qoTeleportationGun.h"
#include "qoSuperpositionGunScript.h"
#include "qoEntanglementGunScript.h"
#include "qoTeleportationGunScript.h"
#include "qoRigidbody.h"
#include "qoSceneManager.h"
#include "qoStage1_1.h"
#include "qoStage1_2.h"

namespace qo
{
	Player::Player()
		: mGuns{}
		, mActiveGun(nullptr)
		, mState(ePlayerState::Idle)
		, mDir(eDirection::RIGHT)
		, mCurHp(100)
		, mMaxHp(100)
		, mMoveSpeed(0.5f)
		, mJumpPower(1.5f)
		, mDashPower(1.f)
		, mbGodMode(false)
	{
	}

	Player::~Player()
	{
		// �÷��̾� �Ҹ�� �÷��̾ �����ϴ� Guns �޸� ����
		for (Gun* gun : mGuns)
		{
			if (gun != nullptr)
			{
				delete gun;
				gun = nullptr;
			}
		}
	}

	void Player::Initialize()
	{
		GameObject::Initialize();
	}

	void Player::Update()
	{
		GameObject::Update();

		// ���� Ȱ��ȭ �Ǿ��ִ� �Ѹ� Update �����ش�.
		if (mActiveGun != nullptr)
		{
			mActiveGun->Update();
		}
	}

	void Player::LateUpdate()
	{
		GameObject::LateUpdate();

		// ���� Ȱ��ȭ �Ǿ��ִ� �Ѹ� LateUpdate �����ش�.
		if (mActiveGun != nullptr)
		{
			mActiveGun->LateUpdate();
		}
	}

	void Player::Render()
	{
		GameObject::Render();

		// ���� Ȱ��ȭ �Ǿ��ִ� �Ѹ� Render �����ش�.
		if (mActiveGun != nullptr)
		{
			mActiveGun->Render();
		}
	}

	void Player::AddGun(eGunType type)
	{
		// �̹� �ش� Ÿ���� ���� ����ִٸ� ��ȿ
		for (Gun* gun : mGuns)
		{
			if (gun->GetGunType() == type)
			{
				return;
			}
		}


		// �÷��̾� ��ü ����
		Transform* PlayerTransform = GetComponent<Transform>();
		Vector3 PlayerPos = PlayerTransform->GetPosition();

		// ================================
		// �� ��ü ����
		// ================================
		if (type == eGunType::Superposition)
		{
			SuperpositionGun* gun = new SuperpositionGun(this, 200);
			Vector3 GunPos = PlayerPos + Vector3(0.2f, 0.f, 0.f);

			Transform* GunTransform = gun->AddComponent<Transform>();
			GunTransform->SetPosition(GunPos);
			GunTransform->SetScale(Vector3(0.1f, 0.1f, 0.f));
			GunTransform->SetColor(gun->GetGunColor());

			MeshRenderer* meshRenderer = gun->AddComponent<MeshRenderer>();
			meshRenderer->SetMesh(ResourceManager::Find<Mesh>(L"RectangleMesh"));
			meshRenderer->SetShader(ResourceManager::Find<Shader>(L"ColorTestShader"));

			gun->AddComponent<GunScript>();
			gun->AddComponent<SuperpositionGunScript>();

			gun->Initialize();

			mGuns.push_back(gun);
			mActiveGun = gun;
		}
		else if(type == eGunType::Entanglement)
		{
			EntanglementGun* gun = new EntanglementGun(this, 100);
			Vector3 GunPos = PlayerPos + Vector3(0.2f, 0.f, 0.f);

			Transform* GunTransform = gun->AddComponent<Transform>();
			GunTransform->SetPosition(GunPos);
			GunTransform->SetScale(Vector3(0.1f, 0.1f, 0.f));
			GunTransform->SetColor(gun->GetGunColor());

			MeshRenderer* meshRenderer = gun->AddComponent<MeshRenderer>();
			meshRenderer->SetMesh(ResourceManager::Find<Mesh>(L"RectangleMesh"));
			meshRenderer->SetShader(ResourceManager::Find<Shader>(L"ColorTestShader"));

			gun->AddComponent<GunScript>();
			gun->AddComponent<EntanglementGunScript>();

			gun->Initialize();

			mGuns.push_back(gun);
			mActiveGun = gun;
		}
		else if (type == eGunType::Teleportation)
		{
			TeleportationGun* gun = new TeleportationGun(this, 3);
			Vector3 GunPos = PlayerPos + Vector3(0.2f, 0.f, 0.f);

			Transform* GunTransform = gun->AddComponent<Transform>();
			GunTransform->SetPosition(GunPos);
			GunTransform->SetScale(Vector3(0.1f, 0.1f, 0.f));
			GunTransform->SetColor(gun->GetGunColor());

			MeshRenderer* meshRenderer = gun->AddComponent<MeshRenderer>();
			meshRenderer->SetMesh(ResourceManager::Find<Mesh>(L"RectangleMesh"));
			meshRenderer->SetShader(ResourceManager::Find<Shader>(L"ColorTestShader"));

			gun->AddComponent<GunScript>();
			gun->AddComponent<TeleportationGunScript>();

			gun->Initialize();

			mGuns.push_back(gun);
			mActiveGun = gun;
		}
	}

	bool Player::ChangeActiveGun(eGunType type)
	{
		for (Gun* gun : mGuns)
		{
			if (type != gun->GetGunType())
				continue;

			mActiveGun = gun;
			return true;
		}

		// �ش�Ÿ���� ���� ã�� ���ߴ�
		return false;
	}

	void Player::TakeHit(int DamageAmount, math::Vector3 HitDir)
	{
		if (mbGodMode) return;

		Damaged(DamageAmount);

		Rigidbody* rb = GetComponent<Rigidbody>();

		if (rb != nullptr)
		{
			rb->AddVelocity(HitDir * 0.5f);
		}
	}
}