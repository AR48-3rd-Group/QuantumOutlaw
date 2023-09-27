#include "qoPlayScene.h"
#include "qoResourceManager.h"
#include "qoCollisionManager.h"

#include "qoGameObject.h"
#include "qoTransform.h"
#include "qoMeshRenderer.h"
#include "qoCollider.h"
#include "qoRigidbody.h"
#include "qoPlayerScript.h"

#include "qoPlayer.h"
#include "qoGround.h"

namespace qo
{
	PlayScene::PlayScene()
	{
	}


	PlayScene::~PlayScene()
	{

	}

	void PlayScene::Initialize()
	{
		{
			Player* object = new Player();
			Transform* tr = object->AddComponent<Transform>();
			tr->SetPosition(Vector3(0.5f, 0.2f, 0.0f));
			tr->SetScale(Vector3(0.1f, 0.1f, 0.1f));

			MeshRenderer* meshRenderer = object->AddComponent<MeshRenderer>();
			meshRenderer->SetMesh(ResourceManager::Find<Mesh>(L"TriangleMesh"));
			meshRenderer->SetShader(ResourceManager::Find<Shader>(L"TriangleShader"));

			Collider* collider = object->AddComponent<Collider>();
			collider->SetScale(Vector3(0.1f, 0.1f, 0.1f));

			Rigidbody* rigidbody = object->AddComponent<Rigidbody>();

			AddGameObject(object, LAYER::PLAYER);
			//object->AddComponent<PlayerScript>();
			//object->AddComponent<PlayerScript2>();

			Ground* object2 = new Ground();
			tr = object2->AddComponent<Transform>();
			tr->SetPosition(Vector3(0.0f, -1.f, 0.0f));
			tr->SetScale(Vector3(1.f, 0.2f, 1.f));

			meshRenderer = object2->AddComponent<MeshRenderer>();
			meshRenderer->SetMesh(ResourceManager::Find<Mesh>(L"TriangleMesh"));
			meshRenderer->SetShader(ResourceManager::Find<Shader>(L"TriangleShader"));

			collider = object2->AddComponent<Collider>();
			collider->SetScale(Vector3(1.f, 0.2f, 1.f));

			AddGameObject(object2, LAYER::GROUND);


			CollisionManager::CollisionLayerCheck(LAYER::PLAYER, LAYER::GROUND, TRUE);
		}
	}

	void PlayScene::Update()
	{
		Scene::Update();
	}

	void PlayScene::LateUpdate()
	{
		Scene::LateUpdate();
	}

	void PlayScene::Render()
	{
		Scene::Render();
	}
}
