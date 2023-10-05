#include "qoSuperpositionGunScript.h"
#include "qoInput.h"
#include "qoApplication.h"
#include "qoGun.h"
#include "qoTransform.h"
#include "qoSuperpositionBullet.h"
#include "qoMeshRenderer.h"
#include "qoSceneManager.h"
#include "qoResourceManager.h"
#include "qoBulletScript.h"
#include "qoCollider.h"
#include "qoCamera.h"

extern qo::Application application;

namespace qo
{
	SuperpositionGunScript::SuperpositionGunScript()
	{
	}

	SuperpositionGunScript::~SuperpositionGunScript()
	{
	}

	void SuperpositionGunScript::Initialize()
	{
	}

	void SuperpositionGunScript::Update()
	{
		Gun* owner = dynamic_cast<Gun*>(GetOwner());

		if (owner == nullptr)
			return;
		
		// 총알 발사
		if (Input::GetKeyState(KEY_CODE::LBTN) == KEY_STATE::DOWN)
		{
			if (owner->GetCurBulletCount() > 0)
			{
				if (owner->BulletConsumption(1))
				{
					Shoot();
				}
			}
		}		
	}

	void SuperpositionGunScript::LateUpdate()
	{
	}

	void SuperpositionGunScript::Render()
	{
	}

	void SuperpositionGunScript::Shoot()
	{
		Gun* owner = dynamic_cast<Gun*>(GetOwner());
		if (owner != nullptr)
		{
			// ==============================================
			// 총알 방향 결정 Gun 위치 → 현재 마우스 위치로 발사
			// ==============================================
			Vector2 mousePos = Input::GetMousPosition();
			Vector3 GunPos = owner->GetComponent<Transform>()->GetPosition();

			// 총위치 왼손 좌표계 좌표상의 위치로 변경
			GunPos = Camera::CaculatePos(GunPos);

			// 윈도우 좌표계 → 왼손 좌표계 정규화
			mousePos.x -= application.GetWidth() / 2.f;
			mousePos.y -= application.GetHeight() / 2.f;

			mousePos.x /= (application.GetWidth() / 2.f);
			mousePos.y /= (application.GetHeight() / 2.f);

			mousePos.y *= -1.f;

			// Gun 위치 → 현재 마우스 위치
			Vector3 Dir = Vector3(0.f, 0.f, 0.f);
			Dir.x = mousePos.x - GunPos.x;
			Dir.y = mousePos.y - GunPos.y;

			// Gun 위치 재설정
			GunPos = owner->GetComponent<Transform>()->GetPosition();

			// ================================================
			// 총알 생성
			// ================================================
			SuperpositionBullet* bullet = new SuperpositionBullet(Dir);
			Transform* tr = bullet->AddComponent<Transform>();
			tr->SetPosition(GunPos); // 총알 시작위치는 총위치로 설정
			tr->SetScale(Vector3(0.1f, 0.1f, 0.1f));
			tr->SetColor(owner->GetGunColor());

			MeshRenderer* meshRenderer = bullet->AddComponent<MeshRenderer>();
			meshRenderer->SetMesh(ResourceManager::Find<Mesh>(L"CircleMesh"));
			meshRenderer->SetShader(ResourceManager::Find<Shader>(L"CircleShader"));

			Collider* col = bullet->AddComponent<Collider>();
			col->SetScale(Vector3(0.1f, 0.1f, 0.1f));

			bullet->AddComponent<BulletScript>();

			bullet->Initialize();

			SceneManager::GetActiveScene()->AddGameObject(bullet, LAYER::BULLET);
		}
	}
}