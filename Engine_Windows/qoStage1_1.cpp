#include "qoStage1_1.h"
#include "qoResourceManager.h"
#include "qoCollisionManager.h"

#include "qoGameObject.h"
#include "qoTransform.h"
#include "qoMeshRenderer.h"
#include "qoCollider.h"
#include "qoRigidbody.h"
#include "qoPlayerScript.h"
#include "qoPlayer.h"
#include "qofloor.h"
#include "qoRigidbody.h"
#include "qoCamera.h"

namespace qo
{
	Stage1_1::Stage1_1()
	{
	}

	Stage1_1::~Stage1_1()
	{
	}

	void Stage1_1::Initialize()
	{
		#pragma region Player
		Player* player = new Player();
		Transform* PlayerTransform = player->AddComponent<Transform>();
		PlayerTransform->SetPositionInPixels(800, 384, 0.);
		PlayerTransform->SetScaleInPixels(96, 192, 0);
		//PlayerTransform->SetScale(1, 1, 0);
		PlayerTransform->SetColor(Vector4(0.f, 0.f, 1.f, 0.f));

		MeshRenderer* PlayerMeshRenderer = player->AddComponent<MeshRenderer>();
		PlayerMeshRenderer->SetMesh(ResourceManager::Find<Mesh>(L"RectangleMesh"));
		PlayerMeshRenderer->SetShader(ResourceManager::Find<Shader>(L"ColorTestShader"));

		Collider* PlayerCollider = player->AddComponent<Collider>();
		PlayerCollider->SetScale(PlayerTransform->GetScale());

		player->AddComponent<Rigidbody>();

		player->AddComponent<PlayerScript>();

		// 총 생성
		player->AddGun(eGunType::Superposition);
		player->AddGun(eGunType::Entanglement);
		player->AddGun(eGunType::Teleportation);

		player->ChangeActiveGun(eGunType::Superposition);

		player->Initialize();

		AddGameObject(player, LAYER::PLAYER);
		Camera::SetTarget(player);
		#pragma endregion

		#pragma region Map Layout
		// 바닥 개체
		Floor* StageFloor = new Floor();
		Floor* Ceiling_1 = new Floor();
		Floor* Ceiling_2 = new Floor();
		Floor* Ceiling_3 = new Floor();

		Transform* StageFloorTransform = StageFloor->AddComponent<Transform>();
		Transform* Ceiling_1_Transform = Ceiling_1->AddComponent<Transform>();
		Transform* Ceiling_2_Transform = Ceiling_2->AddComponent<Transform>();
		Transform* Ceiling_3_Transform = Ceiling_3->AddComponent<Transform>();

		// 좌표(위치) 설정
		StageFloorTransform->SetPositionInPixels(3200, 128, 0);
		Ceiling_1_Transform->SetPositionInPixels(1760, 1256, 0);
		Ceiling_2_Transform->SetPositionInPixels(4960, 2000, 0);
		Ceiling_3_Transform->SetPositionInPixels(5440, 1800, 0);
		
		// 크기 설정
		StageFloorTransform->SetScaleInPixels(6400, 256, 0);
		Ceiling_1_Transform->SetScaleInPixels(3520, 840, 0);
		Ceiling_2_Transform->SetScaleInPixels(2880, 128, 0);
		Ceiling_3_Transform->SetScaleInPixels(1920, 256, 0);
		
		// 색상 설정
		StageFloorTransform->SetColor(Vector4(0.5f, 0.5f, 0.5f, 0.f));
		Ceiling_1_Transform->SetColor(Vector4(0.5f, 0.5f, 0.5f, 0.f));
		Ceiling_2_Transform->SetColor(Vector4(0.5f, 0.5f, 0.5f, 0.f));
		Ceiling_3_Transform->SetColor(Vector4(0.5f, 0.5f, 0.5f, 0.f));
		
		MeshRenderer* StageFloorMeshRenderer = StageFloor->AddComponent<MeshRenderer>();
		MeshRenderer* Ceiling_1_MeshRenderer = Ceiling_1->AddComponent<MeshRenderer>();
		MeshRenderer* Ceiling_2_MeshRenderer = Ceiling_2->AddComponent<MeshRenderer>();
		MeshRenderer* Ceiling_3_MeshRenderer = Ceiling_3->AddComponent<MeshRenderer>();

		StageFloorMeshRenderer->SetMesh(ResourceManager::Find<Mesh>(L"RectangleMesh"));
		Ceiling_1_MeshRenderer->SetMesh(ResourceManager::Find<Mesh>(L"RectangleMesh"));
		Ceiling_2_MeshRenderer->SetMesh(ResourceManager::Find<Mesh>(L"RectangleMesh"));
		Ceiling_3_MeshRenderer->SetMesh(ResourceManager::Find<Mesh>(L"RectangleMesh"));

		StageFloorMeshRenderer->SetShader(ResourceManager::Find<Shader>(L"ColorTestShader"));
		Ceiling_1_MeshRenderer->SetShader(ResourceManager::Find<Shader>(L"ColorTestShader"));
		Ceiling_2_MeshRenderer->SetShader(ResourceManager::Find<Shader>(L"ColorTestShader"));
		Ceiling_3_MeshRenderer->SetShader(ResourceManager::Find<Shader>(L"ColorTestShader"));

		Collider* StageFloorCollider = StageFloor->AddComponent<Collider>();
		Collider* Ceiling_1_Collider = Ceiling_1->AddComponent<Collider>();
		Collider* Ceiling_2_Collider = Ceiling_2->AddComponent<Collider>();
		Collider* Ceiling_3_Collider = Ceiling_3->AddComponent<Collider>();

		StageFloorCollider->SetScale(StageFloorTransform->GetScale());
		Ceiling_1_Collider->SetScale(Ceiling_1_Transform->GetScale());
		Ceiling_2_Collider->SetScale(Ceiling_2_Transform->GetScale());
		Ceiling_3_Collider->SetScale(Ceiling_3_Transform->GetScale());

		AddGameObject(StageFloor, LAYER::FLOOR);
		AddGameObject(Ceiling_1, LAYER::FLOOR);
		//AddGameObject(Ceiling_2, LAYER::FLOOR);
		//AddGameObject(Ceiling_3, LAYER::FLOOR);

		CollisionManager::CollisionLayerCheck(LAYER::PLAYER, LAYER::FLOOR, TRUE);

		// 벽 개체
		Wall* wall = new Wall();
		Wall* wall1 = new Wall();
		Wall* wall2 = new Wall();
		Wall* wall3 = new Wall();
		Transform* WallTransform = wall->AddComponent<Transform>();
		Transform* Wall1Transform = wall1->AddComponent<Transform>();
		Transform* Wall2Transform = wall2->AddComponent<Transform>();
		Transform* Wall3Transform = wall3->AddComponent<Transform>();
		WallTransform->SetPositionInPixels(1600, 320, 0);
		Wall1Transform->SetPositionInPixels(3200, 320, 0);
		Wall2Transform->SetPositionInPixels(4800, 320, 0);
		Wall3Transform->SetPositionInPixels(6400, 320, 0);
		WallTransform->SetScaleInPixels(128, 128, 0);
		Wall1Transform->SetScaleInPixels(128, 128, 0);
		Wall2Transform->SetScaleInPixels(128, 128, 0);
		Wall3Transform->SetScaleInPixels(128, 128, 0);
		WallTransform->SetColor(Vector4(0.5f, 0.5f, 0.5f, 0.f));
		Wall1Transform->SetColor(Vector4(0.5f, 0.5f, 0.5f, 0.f));
		Wall2Transform->SetColor(Vector4(0.5f, 0.5f, 0.5f, 0.f));
		Wall3Transform->SetColor(Vector4(0.5f, 0.5f, 0.5f, 0.f));

		MeshRenderer* WallMeshRenderer = wall->AddComponent<MeshRenderer>();
		MeshRenderer* Wall1MeshRenderer = wall1->AddComponent<MeshRenderer>();
		MeshRenderer* Wall2MeshRenderer = wall2->AddComponent<MeshRenderer>();
		MeshRenderer* Wall3MeshRenderer = wall3->AddComponent<MeshRenderer>();
		WallMeshRenderer->SetMesh(ResourceManager::Find<Mesh>(L"RectangleMesh"));
		Wall1MeshRenderer->SetMesh(ResourceManager::Find<Mesh>(L"RectangleMesh"));
		Wall2MeshRenderer->SetMesh(ResourceManager::Find<Mesh>(L"RectangleMesh"));
		Wall3MeshRenderer->SetMesh(ResourceManager::Find<Mesh>(L"RectangleMesh"));
		WallMeshRenderer->SetShader(ResourceManager::Find<Shader>(L"ColorTestShader"));
		Wall1MeshRenderer->SetShader(ResourceManager::Find<Shader>(L"ColorTestShader"));
		Wall2MeshRenderer->SetShader(ResourceManager::Find<Shader>(L"ColorTestShader"));
		Wall3MeshRenderer->SetShader(ResourceManager::Find<Shader>(L"ColorTestShader"));

		Collider* WallCollider = wall->AddComponent<Collider>();
		Collider* Wall1Collider = wall1->AddComponent<Collider>();
		Collider* Wall2Collider = wall2->AddComponent<Collider>();
		Collider* Wall3Collider = wall3->AddComponent<Collider>();
		WallCollider->SetScale(WallTransform->GetScale());
		Wall1Collider->SetScale(Wall1Transform->GetScale());
		Wall2Collider->SetScale(Wall2Transform->GetScale());
		Wall3Collider->SetScale(Wall3Transform->GetScale());

		AddGameObject(wall, LAYER::WALL);
		AddGameObject(wall1, LAYER::WALL);
		AddGameObject(wall2, LAYER::WALL);
		AddGameObject(wall3, LAYER::WALL);

		CollisionManager::CollisionLayerCheck(LAYER::PLAYER, LAYER::WALL, TRUE);
		#pragma endregion

	}

	void Stage1_1::Update()
	{
		Scene::Update();
	}

	void Stage1_1::LateUpdate()
	{
		Scene::LateUpdate();
	}

	void Stage1_1::Render()
	{
		Scene::Render();
	}

	void Stage1_1::UnlockDoor(int tag)
	{
	}

}
