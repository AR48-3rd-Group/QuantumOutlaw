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
	{
	}

	Player::~Player()
	{
		// 플레이어 소멸시 플레이어가 관리하던 Guns 메모리 해제
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

		// 현재 활성화 되어있는 총만 Update 시켜준다.
		if (mActiveGun != nullptr)
		{
			mActiveGun->Update();
		}
	}

	void Player::LateUpdate()
	{
		GameObject::LateUpdate();

		// 현재 활성화 되어있는 총만 LateUpdate 시켜준다.
		if (mActiveGun != nullptr)
		{
			mActiveGun->LateUpdate();
		}
	}

	void Player::Render()
	{
		GameObject::Render();

		// 현재 활성화 되어있는 총만 Render 시켜준다.
		if (mActiveGun != nullptr)
		{
			mActiveGun->Render();
		}
	}

	void Player::AddGun(eGunType type)
	{
		// 이미 해당 타입의 총을 들고있다면 무효
		for (Gun* gun : mGuns)
		{
			if (gun->GetGunType() == type)
			{
				return;
			}
		}


		// 플레이어 객체 정보
		Transform* PlayerTransform = GetComponent<Transform>();
		Vector3 PlayerPos = PlayerTransform->GetPosition();

		// ================================
		// 총 객체 생성
		// ================================
		if (type == eGunType::Superposition)
		{
			SuperpositionGun* gun = new SuperpositionGun(this, 50);
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
			EntanglementGun* gun = new EntanglementGun(this, 50);
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
			TeleportationGun* gun = new TeleportationGun(this, 50);
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

		// 해당타입의 총을 찾지 못했다
		return false;
	}

	void Player::TakeHit(int DamageAmount, math::Vector3 HitDir)
	{
		Damaged(DamageAmount);

		// Player Dead시 Scene 재시작
		if (GetCurHP() <= 0.f)
		{
			std::wstring SceneName = SceneManager::GetActiveScene()->GetName();

			if (SceneName == L"Stage1_1")
			{
				SceneManager::ReStartScene<Stage1_1>(SceneName);
			}
			else if (SceneName == L"Stage1_2")
			{
				SceneManager::ReStartScene<Stage1_2>(SceneName);
			}		
		}

		Rigidbody* rb = GetComponent<Rigidbody>();

		if (rb != nullptr)
		{
			rb->AddVelocity(HitDir * 0.5f);
		}
	}
}