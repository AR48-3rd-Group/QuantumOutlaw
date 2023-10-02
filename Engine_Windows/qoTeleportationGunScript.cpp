#include "qoTeleportationGunScript.h"
#include "qoInput.h"
#include "qoApplication.h"
#include "qoGun.h"
#include "qoTransform.h"
#include "qoMeshRenderer.h"
#include "qoSceneManager.h"
#include "qoResourceManager.h"
#include "qoBulletScript.h"
#include "qoCollider.h"
#include "qoTeleportationGun.h"
#include "qoTeleportationBullet.h"

extern qo::Application application;


namespace qo
{
	TeleportationGunScript::TeleportationGunScript()
	{
	}

	TeleportationGunScript::~TeleportationGunScript()
	{
	}

	void TeleportationGunScript::Initialize()
	{
	}

	void TeleportationGunScript::Update()
	{
		TeleportationGun* teleportationGun = dynamic_cast<TeleportationGun*>(GetOwner());

		if (teleportationGun == nullptr)
			return;
		// ==========================
		// 총알 발사
		// ==========================
		if (Input::GetKeyState(KEY_CODE::LBTN) == KEY_STATE::DOWN)
		{
			if (teleportationGun->GetCurBulletCount() > 0)
			{
				if (teleportationGun->BulletConsumption(1))
				{
					Shoot();
				}
			}
		}

		// ==========================
		// TargetBullet 위치로 순간이동
		// ==========================
		if (Input::GetKeyState(KEY_CODE::RBTN) == KEY_STATE::DOWN)
		{
			TeleportationBullet* targetBullet = teleportationGun->GetTargetBullet();

			if (targetBullet != nullptr)
			{
				Player* player = teleportationGun->GetPlayer();

				Transform* playerTransform = player->GetComponent<Transform>();
				playerTransform->SetPosition(targetBullet->GetComponent<Transform>()->GetPosition()); // 플레이어 위치를 총알의 위치로 설정

				// 총알 삭제 및 TargetBullet 초기화
				Destroy(targetBullet);
				teleportationGun->SetTargetBullet(nullptr);
			}
		}
	}

	void TeleportationGunScript::LateUpdate()
	{
	}

	void TeleportationGunScript::Render()
	{
	}

	void TeleportationGunScript::Shoot()
	{
		TeleportationGun* teleportationGun = dynamic_cast<TeleportationGun*>(GetOwner());

		if (teleportationGun != nullptr)
		{
			// ==============================================
			// 총알 방향 결정 Gun 위치 → 현재 마우스 위치로 발사
			// ==============================================
			Vector2 mousePos = Input::GetMousPosition();
			Vector3 GunPos = teleportationGun->GetComponent<Transform>()->GetPosition();

			// 윈도우 좌표계 → 왼손 좌표계 기준 변환
			GunPos.x += application.GetWidth() / 2.f;
			GunPos.y += application.GetHeight() / 2.f;

			// Gun 위치 → 현재 마우스 위치
			Vector3 Dir = Vector3(0.f, 0.f, 0.f);
			Dir.x = mousePos.x - GunPos.x;
			Dir.y = mousePos.y - GunPos.y;
			Dir.y *= -1.f; // Window 좌표계 → 왼손 좌표계 Y 방향 전환



			// Gun 위치 재설정
			GunPos = teleportationGun->GetComponent<Transform>()->GetPosition();

			// ================================================
			// 총알 생성
			// ================================================
			TeleportationBullet* bullet = new TeleportationBullet(Dir);
			Transform* tr = bullet->AddComponent<Transform>();
			tr->SetPosition(GunPos); // 총알 시작위치는 총위치로 설정
			tr->SetScale(Vector3(0.1f, 0.1f, 0.1f));

			MeshRenderer* meshRenderer = bullet->AddComponent<MeshRenderer>();
			meshRenderer->SetMesh(ResourceManager::Find<Mesh>(L"CircleMesh"));
			meshRenderer->SetShader(ResourceManager::Find<Shader>(L"CircleShader"));

			Collider* col = bullet->AddComponent<Collider>();
			col->SetScale(Vector3(0.1f, 0.1f, 0.1f));

			bullet->AddComponent<BulletScript>();

			bullet->Initialize();

			SceneManager::GetActiveScene()->AddGameObject(bullet, LAYER::BULLET);

			// TargetBullet 설정
			teleportationGun->SetTargetBullet(bullet);
		}
	}
}