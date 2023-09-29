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
		PlayerTransform->SetScale(Vector3(0.1f, 0.3f, 0.f));
		PlayerTransform->SetColor(Vector4(0.f, 1.f, 0.f, 0.f));

		MeshRenderer* PlayerMeshRenderer = player->AddComponent<MeshRenderer>();
		PlayerMeshRenderer->SetMesh(ResourceManager::Find<Mesh>(L"RectangleMesh"));
		PlayerMeshRenderer->SetShader(ResourceManager::Find<Shader>(L"ColorTestShader"));	

		Collider* PlayerCollider = player->AddComponent<Collider>();
		PlayerCollider->SetScale(Vector3(0.3f, 0.3f, 0.f));
					 
		player->AddComponent<Rigidbody>();
		
		player->AddComponent<PlayerScript>();

		// 총 생성
		player->AddGun(eGunType::Superposition);

		player->Initialize();

		AddGameObject(player, LAYER::PLAYER);

		Ground* ground = new Ground();
		Transform* GroundTransform = ground->AddComponent<Transform>();
		GroundTransform->SetPosition(Vector3(0.0f, -0.5f, 0.0f));
		GroundTransform->SetScale(Vector3(1.f, 0.3f, 0.0f));
		GroundTransform->SetColor(Vector4(0.5f, 0.5f, 0.5f, 0.f));

		MeshRenderer* GroundMeshRenderer = ground->AddComponent<MeshRenderer>();
		GroundMeshRenderer->SetMesh(ResourceManager::Find<Mesh>(L"RectangleMesh"));
		GroundMeshRenderer->SetShader(ResourceManager::Find<Shader>(L"ColorTestShader")); 

		Collider* GroundCollider = ground->AddComponent<Collider>();
		GroundCollider->SetScale(Vector3(1.f, 0.3f, 0.f));

		AddGameObject(ground, LAYER::GROUND);

		CollisionManager::CollisionLayerCheck(LAYER::PLAYER, LAYER::GROUND, TRUE);

		// 벽 오브젝트 생성
		Ground* Wall = new Ground();
		Transform* WallTransform = Wall->AddComponent<Transform>();
		WallTransform->SetPosition(Vector3(0.5f, 0.0f, 0.0f));
		WallTransform->SetScale(Vector3(0.3f, 1.f, 0.0f));
		WallTransform->SetColor(Vector4(0.3f, 0.3f, 0.3f, 0.f));

		MeshRenderer* WallMeshRenderer = Wall->AddComponent<MeshRenderer>();
		WallMeshRenderer->SetMesh(ResourceManager::Find<Mesh>(L"RectangleMesh"));
		WallMeshRenderer->SetShader(ResourceManager::Find<Shader>(L"ColorTestShader"));

		Collider* WallCollider = Wall->AddComponent<Collider>();
		WallCollider->SetScale(Vector3(0.3f, 1.f, 0.0f));

		AddGameObject(Wall, LAYER::GROUND);

		CollisionManager::CollisionLayerCheck(LAYER::BULLET, LAYER::GROUND, TRUE);
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
