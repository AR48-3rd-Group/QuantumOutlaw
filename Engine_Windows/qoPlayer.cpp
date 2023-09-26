#include "qoPlayer.h"
#include "qoGun.h"
#include "qoGunScript.h"
#include "qoTransform.h"
#include "qoMeshRenderer.h"
#include "qoResourceManager.h"

namespace qo
{
	Player::Player()
		: mGuns{}
		, mActiveGun(nullptr)
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

	void Player::AddGun()
	{
		// 플레이어 객체 정보
		Transform* PlayerTransform = GetComponent<Transform>();
		Vector3 PlayerPos = PlayerTransform->GetPosition();

		// ============
		// 총 객체 생성
		// ============
		Gun* gun = new Gun(this, 50);

		Transform* GunTransform = gun->AddComponent<Transform>();
		GunTransform->SetPosition(PlayerPos);
		GunTransform->SetScale(Vector3(0.3f, 0.3f, 0.3f));

		MeshRenderer* meshRenderer = gun->AddComponent<MeshRenderer>();
		meshRenderer->SetMesh(ResourceManager::Find<Mesh>(L"RectangleMesh"));
		meshRenderer->SetShader(ResourceManager::Find<Shader>(L"TriangleShader"));

		gun->AddComponent<GunScript>();
		
		gun->Initialize();

		mGuns.push_back(gun);
		mActiveGun = gun;		
	}
}