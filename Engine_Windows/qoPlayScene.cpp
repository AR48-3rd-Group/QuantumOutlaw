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
#include "qofloor.h"
#include "qoRigidbody.h"
#include "qoCamera.h"

#include "qoLabTurret.h"
#include "qoHPUI.h"
#include "qoHPUIScript.h"

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

		// 바닥 객체 생성
		Floor* floor = new Floor();
		Transform* FloorTransform = floor->AddComponent<Transform>();
		FloorTransform->SetPositionInPixels(0, 0, 0);
		FloorTransform->SetScaleInPixels(1990, 100, 0);
		FloorTransform->SetColor(Vector4(0.5f, 0.5f, 0.5f, 0.f));

		MeshRenderer* FloorMeshRenderer = floor->AddComponent<MeshRenderer>();
		FloorMeshRenderer->SetMesh(ResourceManager::Find<Mesh>(L"RectangleMesh"));
		FloorMeshRenderer->SetShader(ResourceManager::Find<Shader>(L"ColorTestShader"));

		Collider* FloorCollider = floor->AddComponent<Collider>();
		FloorCollider->SetScale(FloorTransform->GetScale());

		AddGameObject(floor, LAYER::FLOOR);

		CollisionManager::CollisionLayerCheck(LAYER::PLAYER, LAYER::FLOOR, TRUE);

		// 스위치 개체 생성
		doorswitch = new DoorSwitch();
		Transform* DSTransform = doorswitch->AddComponent<Transform>();
		DSTransform->SetPositionInPixels(-500, 200, 0);
		DSTransform->SetScaleInPixels(400, 400, 0);
		DSTransform->SetColor(Vector4(0.5f, 0.5f, 0.5f, 0.f));

		MeshRenderer* DSMeshRenderer = doorswitch->AddComponent<MeshRenderer>();
		DSMeshRenderer->SetMesh(ResourceManager::Find<Mesh>(L"RectangleMesh"));
		DSMeshRenderer->SetShader(ResourceManager::Find<Shader>(L"ColorTestShader"));

		Collider* DSCollider = doorswitch->AddComponent<Collider>();
		DSCollider->SetScale(DSTransform->GetScale());

		AddGameObject(doorswitch, LAYER::WALL);

		CollisionManager::CollisionLayerCheck(LAYER::PLAYER, LAYER::WALL, TRUE);
		CollisionManager::CollisionLayerCheck(LAYER::BULLET, LAYER::WALL, TRUE);

		// 잠긴 문 개체 생성
		lockeddoor = new LockedDoor();
		Transform* LockedDoorTransform = lockeddoor->AddComponent<Transform>();
		LockedDoorTransform->SetPositionInPixels(500, 200, 0);
		LockedDoorTransform->SetScaleInPixels(400, 400, 0);
		LockedDoorTransform->SetColor(Vector4(0.5f, 0.5f, 0.5f, 0.f));

		MeshRenderer* LockedDoorMeshRenderer = lockeddoor->AddComponent<MeshRenderer>();
		LockedDoorMeshRenderer->SetMesh(ResourceManager::Find<Mesh>(L"RectangleMesh"));
		LockedDoorMeshRenderer->SetShader(ResourceManager::Find<Shader>(L"ColorTestShader"));

		Collider* LockedDoorCollider = lockeddoor->AddComponent<Collider>();
		LockedDoorCollider->SetScale(LockedDoorTransform->GetScale());

		AddGameObject(lockeddoor, LAYER::WALL);

		CollisionManager::CollisionLayerCheck(LAYER::PLAYER, LAYER::WALL, TRUE);
	}

	void PlayScene::Update()
	{
		Scene::Update();

		if (doorswitch->GetSwitch())
		{
			lockeddoor->SetLocked(false);
		}
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
