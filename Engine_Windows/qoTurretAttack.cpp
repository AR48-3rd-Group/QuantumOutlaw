#include "qoTurretAttack.h"
#include "qoCollider.h"
#include "qoPlayer.h"
#include "qoTransform.h"
#include "qoScene.h"
#include "qoSceneManager.h"
#include "qoMeshRenderer.h"
#include "qoResourceManager.h"

namespace qo
{
	TurretAttack::TurretAttack(Vector3 Dir)
		: Bullet(Dir)
	{
	}

	TurretAttack::~TurretAttack()
	{
	}

	void TurretAttack::Initialize()
	{
		GameObject::Initialize();
	}

	void TurretAttack::Update()
	{
		GameObject::Update();
	}

	void TurretAttack::LateUpdate()
	{
		GameObject::LateUpdate();
	}

	void TurretAttack::Render()
	{
		GameObject::Render();
	}

	void TurretAttack::OnCollisionEnter(Collider* other)
	{
		Player* player = dynamic_cast<Player*>(other->GetOwner());

		if (player != nullptr)
		{
			// 충돌한 player 객체의 포지션
			Vector3 first = player->GetComponent<Transform>()->GetPosition();

			// 이제 그 에너미와 가까운 에너미 탐색
			Scene* ActiveScene = SceneManager::GetActiveScene();
			std::vector<GameObject*> players = ActiveScene->GetLayer((UINT)LAYER::PLAYER)->GetGameObjects();
			//long double min = 60.f;

			GameObject* target = nullptr;

			for (GameObject* playerobj : players)
			{
				if (player == playerobj)
				{
					target = playerobj;
					continue;
				}

				//Vector3 compare = playerobj->GetComponent<Transform>()->GetPosition();

				//long double Distance = sqrt(pow(static_cast<long double>(first.x) - static_cast<long double>(compare.x), 2) +
				//	pow(static_cast<long double>(first.x) - static_cast<long double>(compare.x), 2));

				//if (static_cast<long double>(min) > Distance)
				//{
				//	min = Distance;
				//	target = playerobj;
				//}
			}

			// 타겟을 찾았다면 연쇄 반응
			if (target != nullptr)
			{
				//TrackerBullet* trackerBullet = new TrackerBullet(dynamic_cast<Player*>(target));
				//Transform* tr = trackerBullet->AddComponent<Transform>();
				//tr->SetPosition(first); // 총알 시작위치는 총위치로 설정
				//tr->SetScale(Vector3(0.1f, 0.1f, 0.1f));

				//MeshRenderer* meshRenderer = trackerBullet->AddComponent<MeshRenderer>();
				//meshRenderer->SetMesh(ResourceManager::Find<Mesh>(L"TriangleMesh"));
				//meshRenderer->SetShader(ResourceManager::Find<Shader>(L"TriangleMesh"));

				//Collider* col = trackerBullet->AddComponent<Collider>();
				//col->SetScale(Vector3(0.1f, 0.1f, 0.1f));

				//trackerBullet->AddComponent<TrackerBulletScript>();

				//trackerBullet->Initialize();

				//trackerBullet->SetFirst(enemy);

				//SceneManager::GetActiveScene()->AddGameObject(trackerBullet, LAYER::BULLET);
			}

			Destroy(this);
			return;
		}
	}

	void TurretAttack::OnCollisionStay(Collider* other)
	{
	}

	void TurretAttack::OnCollisionExit(Collider* other)
	{
	}

}
