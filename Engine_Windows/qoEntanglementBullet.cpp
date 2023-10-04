#include "qoEntanglementBullet.h"
#include "qoCollider.h"
#include "ArchitectureInclude.h"
#include "qoEnemy.h"
#include "qoSceneManager.h"
#include "qoMeshRenderer.h"
#include "qoResourceManager.h"
#include "qoBulletScript.h"

namespace qo
{
	EntanglementBullet::EntanglementBullet(Vector3 Dir)
		: Bullet(Dir)
	{
	}

	EntanglementBullet::~EntanglementBullet()
	{
	}

	void EntanglementBullet::Initialize()
	{
		GameObject::Initialize();
	}

	void EntanglementBullet::Update()
	{
		GameObject::Update();
	}

	void EntanglementBullet::LateUpdate()
	{
		GameObject::LateUpdate();
	}

	void EntanglementBullet::Render()
	{
		GameObject::Render();
	}

	void EntanglementBullet::OnCollisionEnter(Collider* other)
	{
		Enemy* enemy = dynamic_cast<Enemy*>(other->GetOwner());

		if (enemy != nullptr)
		{
			// 충돌한 에너미 객체의 포지션
			Vector3 first = enemy->GetComponent<Transform>()->GetPosition();

			// 이제 그 에너미와 가까운 에너미 탐색
			Scene* ActiveScene = SceneManager::GetActiveScene();
			std::vector<GameObject*> enemies = ActiveScene->GetLayer((UINT)LAYER::MONSTER)->GetGameObjects();
			long double min = 1.f;

			GameObject* target = nullptr;

			for (GameObject* enemyobj : enemies)
			{
				if (enemy == enemyobj)
					continue;

				Vector3 compare = enemyobj->GetComponent<Transform>()->GetPosition();
				long double Distance = sqrt(pow(static_cast<long double>(first.x) - static_cast<long double>(compare.x), 2) +
					pow(static_cast<long double>(first.x) - static_cast<long double>(compare.x), 2));
				if (static_cast<long double>(min) > Distance)
				{
					min = Distance;
					target = enemyobj;
				}
			}

			// 타겟을 찾았다면 연쇄 반응
			if (target != nullptr)
			{
				Vector3 Dir = Vector3(0.f, 0.f, 0.f);
				Vector3 targetPosition = target->GetComponent<Transform>()->GetPosition();
				Dir.x = targetPosition.x - first.x;
				Dir.y = targetPosition.y - first.y;

				EntanglementBullet* bullet = new EntanglementBullet(Dir);
				Transform* tr = bullet->AddComponent<Transform>();
				tr->SetPosition(first); // 총알 시작위치는 총위치로 설정
				tr->SetScale(Vector3(0.1f, 0.1f, 0.1f));

				MeshRenderer* meshRenderer = bullet->AddComponent<MeshRenderer>();
				meshRenderer->SetMesh(ResourceManager::Find<Mesh>(L"CircleMesh"));
				meshRenderer->SetShader(ResourceManager::Find<Shader>(L"CircleShader"));

				Collider* col = bullet->AddComponent<Collider>();
				col->SetScale(Vector3(0.1f, 0.1f, 0.1f));

				bullet->AddComponent<BulletScript>();

				bullet->Initialize();

				SceneManager::GetActiveScene()->AddGameObject(bullet, LAYER::BULLET);
			}

			Destroy(this);
			return;
		}

		Floor* floor = dynamic_cast<Floor*> (other->GetOwner());
		Wall* wall = dynamic_cast<Wall*> (other->GetOwner());
		LockedDoor* lockedDoor = dynamic_cast<LockedDoor*> (other->GetOwner());
		DoorSwitch* doorSwitch = dynamic_cast<DoorSwitch*> (other->GetOwner());
		DestuctibleWall* destuctibleWall = dynamic_cast<DestuctibleWall*> (other->GetOwner());
		Barrier* barrier = dynamic_cast<Barrier*> (other->GetOwner());

		// 충돌한 객체가 해당 객체면 Bullet 삭제
		if (floor == nullptr
			&& wall == nullptr
			&& lockedDoor == nullptr
			&& doorSwitch == nullptr
			&& destuctibleWall == nullptr
			&& barrier == nullptr)
			return;

		Destroy(this);
	}

	void EntanglementBullet::OnCollisionStay(Collider* other)
	{
	}

	void EntanglementBullet::OnCollisionExit(Collider* other)
	{
	}
}