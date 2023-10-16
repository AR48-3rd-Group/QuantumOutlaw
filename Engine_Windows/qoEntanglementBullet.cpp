#include "qoEntanglementBullet.h"
#include "qoCollider.h"
#include "ArchitectureInclude.h"
#include "qoEnemy.h"
#include "qoSceneManager.h"
#include "qoMeshRenderer.h"
#include "qoResourceManager.h"
#include "qoBulletScript.h"
#include "qoTrackerBullet.h"
#include "qoTrackerBulletScript.h"

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
			// �浹�� ���ʹ� ��ü�� ������
			Vector3 first = enemy->GetComponent<Transform>()->GetPosition();

			// ���� �� ���ʹ̿� ����� ���ʹ� Ž��
			Scene* ActiveScene = SceneManager::GetActiveScene();
			std::vector<GameObject*> enemies = ActiveScene->GetLayer((UINT)LAYER::ENEMY)->GetGameObjects();
			long double min = 60.f;

			GameObject* target = nullptr;

			for (GameObject* enemyobj : enemies)
			{
				if (enemy == enemyobj)
					continue;

				Vector3 compare = enemyobj->GetComponent<Transform>()->GetPosition();

				long double Distance = sqrt(pow(static_cast<long double>(first.x) - static_cast<long double>(compare.x), 2) +
					pow(static_cast<long double>(first.y) - static_cast<long double>(compare.y), 2));

				if (static_cast<long double>(min) > Distance)
				{
					min = Distance;
					target = enemyobj;
				}
			}

			// Ÿ���� ã�Ҵٸ� ���� ����
			if (target != nullptr)
			{
				TrackerBullet* trackerBullet = new TrackerBullet(dynamic_cast<Enemy*>(target));
				Transform* tr = trackerBullet->AddComponent<Transform>();
				tr->SetPosition(first); // �Ѿ� ������ġ�� ����ġ�� ����
				tr->SetScale(Vector3(0.1f, 0.1f, 0.1f));
				tr->SetColor(Vector4(0.f, 0.f, 0.f, 0.f));

				MeshRenderer* meshRenderer = trackerBullet->AddComponent<MeshRenderer>();
				meshRenderer->SetMesh(ResourceManager::Find<Mesh>(L"CircleMesh"));
				meshRenderer->SetShader(ResourceManager::Find<Shader>(L"CircleShader"));

				Collider* col = trackerBullet->AddComponent<Collider>();
				col->SetScale(Vector3(0.1f, 0.1f, 0.1f));

				trackerBullet->AddComponent<TrackerBulletScript>();

				trackerBullet->Initialize();

				trackerBullet->SetFirst(enemy);

				SceneManager::GetActiveScene()->AddGameObject(trackerBullet, LAYER::BULLET);
			}

			// Enemy �浹 ó��
			Vector3 Dir = enemy->GetComponent<Transform>()->GetPosition() - GetComponent<Transform>()->GetPosition();
			Dir.Normalize();
			enemy->TakeHit(10, Dir);

			Destroy(this);
			return;
		}

		Floor* floor = dynamic_cast<Floor*> (other->GetOwner());
		Wall* wall = dynamic_cast<Wall*> (other->GetOwner());
		LockedDoor* lockedDoor = dynamic_cast<LockedDoor*> (other->GetOwner());
		EventSwitch* eventSwitch = dynamic_cast<EventSwitch*> (other->GetOwner());
		DestuctibleWall* destuctibleWall = dynamic_cast<DestuctibleWall*> (other->GetOwner());
		Barrier* barrier = dynamic_cast<Barrier*> (other->GetOwner());

		// �浹�� ��ü�� �ش� ��ü�� Bullet ����
		if (floor == nullptr
			&& wall == nullptr
			&& lockedDoor == nullptr
			&& eventSwitch == nullptr
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