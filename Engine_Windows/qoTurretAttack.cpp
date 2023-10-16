#include "qoTurretAttack.h"
#include "qoCollider.h"
#include "qoPlayer.h"
#include "qoTransform.h"
#include "qoScene.h"
#include "qoSceneManager.h"
#include "qoMeshRenderer.h"
#include "qoResourceManager.h"
#include "qoLabTurret.h"

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
			// �浹�� player ��ü�� ������
			Vector3 PlayerPos = player->GetComponent<Transform>()->GetPosition();

			// ���� �� ���ʹ̿� ����� ���ʹ� Ž��
			Scene* ActiveScene = SceneManager::GetActiveScene();
			std::vector<GameObject*> players = ActiveScene->GetLayer((UINT)LAYER::PLAYER)->GetGameObjects();

			GameObject* target = nullptr;

			for (GameObject* playerobj : players)
			{
				if (player == playerobj)
				{
					target = playerobj;
					continue;
				}
			}

			if (target != nullptr)
			{
				//TrackerBullet* trackerBullet = new TrackerBullet(dynamic_cast<Player*>(target));
				//Transform* tr = trackerBullet->AddComponent<Transform>();
				//tr->SetPosition(first); // �Ѿ� ������ġ�� ����ġ�� ����
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

			Vector3 Dir = player->GetComponent<Transform>()->GetPosition() - GetComponent<Transform>()->GetPosition();
			Dir.Normalize();

			player->TakeHit(10, Dir);

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
