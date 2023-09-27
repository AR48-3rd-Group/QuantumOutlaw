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
#include "qoRigidbody.h"


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
		Player* player = new Player();
		Transform* PlayerTransform = player->AddComponent<Transform>();
		PlayerTransform->SetPosition(Vector3(0.0f, 0.0f, 0.0f));
		PlayerTransform->SetScale(Vector3(0.3f, 0.3f, 0.f));

		MeshRenderer* PlayerMeshRenderer = player->AddComponent<MeshRenderer>();
		PlayerMeshRenderer->SetMesh(ResourceManager::Find<Mesh>(L"RectangleMesh"));
		PlayerMeshRenderer->SetShader(ResourceManager::Find<Shader>(L"TriangleShader"));

		Collider* PlayerCollider = player->AddComponent<Collider>();
		PlayerCollider->SetScale(Vector3(0.3f, 0.3f, 0.f));
					 
		player->AddComponent<Rigidbody>();
		
		player->AddComponent<PlayerScript>();

		// ÃÑ ÇÏ³ª »ý¼º
		player->AddGun();

		player->Initialize();

		AddGameObject(player, LAYER::PLAYER);

		Ground* ground = new Ground();
		Transform* GroundTransform = ground->AddComponent<Transform>();
		GroundTransform->SetPosition(Vector3(0.0f, -0.5f, 0.0f));
		GroundTransform->SetScale(Vector3(1.f, 0.3f, 0.0f));

		MeshRenderer* GroundMeshRenderer = ground->AddComponent<MeshRenderer>();
		GroundMeshRenderer->SetMesh(ResourceManager::Find<Mesh>(L"RectangleMesh"));
		GroundMeshRenderer->SetShader(ResourceManager::Find<Shader>(L"ColorTestShader")); 

		Collider* GroundCollider = ground->AddComponent<Collider>();
		GroundCollider->SetScale(Vector3(1.f, 0.25f, 0.f));

		AddGameObject(ground, LAYER::GROUND);

		CollisionManager::CollisionLayerCheck(LAYER::PLAYER, LAYER::GROUND, TRUE);
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
