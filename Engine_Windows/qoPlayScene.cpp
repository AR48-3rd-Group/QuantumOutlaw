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
#include "ArchitectureInclude.h"

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
		//PlayerTransform->SetPosition(Vector3(0.0f, 0.0f, 0.0f));
		PlayerTransform->SetPositionInPixels(0, 500, 0);
		PlayerTransform->SetScale(Vector3(0.1f, 0.3f, 0.f));
		PlayerTransform->SetColor(Vector4(0.f, 0.f, 1.f, 0.f));

		MeshRenderer* PlayerMeshRenderer = player->AddComponent<MeshRenderer>();
		PlayerMeshRenderer->SetMesh(ResourceManager::Find<Mesh>(L"RectangleMesh"));
		PlayerMeshRenderer->SetShader(ResourceManager::Find<Shader>(L"ColorTestShader"));	

		Collider* PlayerCollider = player->AddComponent<Collider>();
		PlayerCollider->SetScale(Vector3(0.1f, 0.3f, 0.f));
					 
		player->AddComponent<Rigidbody>();
		
		player->AddComponent<PlayerScript>();

		// 총 생성
		player->AddGun(eGunType::Superposition);

		player->Initialize();

		AddGameObject(player, LAYER::PLAYER);

		// 바닥 오브젝트 생성
		Floor* floor = new Floor();
		Transform* FloorTransform = floor->AddComponent<Transform>();
		FloorTransform->SetPositionInPixels(0, 0, 1);
		FloorTransform->SetScaleInPixels(1990, 100, 1);
		FloorTransform->SetColor(Vector4(0.5f, 0.5f, 0.5f, 0.f));

		MeshRenderer* FloorMeshRenderer = floor->AddComponent<MeshRenderer>();
		FloorMeshRenderer->SetMesh(ResourceManager::Find<Mesh>(L"RectangleMesh"));
		FloorMeshRenderer->SetShader(ResourceManager::Find<Shader>(L"ColorTestShader"));

		Collider* GroundCollider = floor->AddComponent<Collider>();
		GroundCollider->SetScale(FloorTransform->GetScale());

		AddGameObject(floor, LAYER::FLOOR);

		CollisionManager::CollisionLayerCheck(LAYER::PLAYER, LAYER::FLOOR, TRUE);

		// 벽 오브젝트 생성
		Wall* wall = new Wall();
		DestuctibleWall* dWall = new DestuctibleWall();
		Transform* WallTransform = wall->AddComponent<Transform>();
		Transform* dWallTransform = dWall->AddComponent<Transform>();
		WallTransform->SetPositionInPixels(500, 400, 1);
		dWallTransform->SetPositionInPixels(-500, 400, 1);
		WallTransform->SetScaleInPixels(400, 800, 1);
		dWallTransform->SetScaleInPixels(400, 800, 1);
		WallTransform->SetColor(Vector4(0.3f, 0.3f, 0.3f, 0.f));
		dWallTransform->SetColor(Vector4(0.3f, 0.3f, 0.3f, 0.f));

		MeshRenderer* WallMeshRenderer = wall->AddComponent<MeshRenderer>();
		MeshRenderer* dWallMeshRenderer = dWall->AddComponent<MeshRenderer>();
		WallMeshRenderer->SetMesh(ResourceManager::Find<Mesh>(L"RectangleMesh"));
		dWallMeshRenderer->SetMesh(ResourceManager::Find<Mesh>(L"RectangleMesh"));
		WallMeshRenderer->SetShader(ResourceManager::Find<Shader>(L"ColorTestShader"));
		dWallMeshRenderer->SetShader(ResourceManager::Find<Shader>(L"ColorTestShader"));

		Collider* WallCollider = wall->AddComponent<Collider>();
		Collider* dWallCollider = dWall->AddComponent<Collider>();
		WallCollider->SetScale(WallTransform->GetScale());
		dWallCollider->SetScale(dWallTransform->GetScale());

		AddGameObject(wall, LAYER::WALL);
		AddGameObject(dWall, LAYER::WALL);

		CollisionManager::CollisionLayerCheck(LAYER::PLAYER, LAYER::WALL, TRUE);
		CollisionManager::CollisionLayerCheck(LAYER::BULLET, LAYER::WALL, TRUE);
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
