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
#include "qoLabGuard.h"
#include "qoLabGuardScript.h"

#include "qoLabTurret.h"
#include "qoLabGuard.h"
#include "qoLabGuardScript.h"
#include "qoHPUI.h"
#include "qoHPUIScript.h"
#include "qoHPUIBackGround.h"

#include "qoSceneManager.h"

namespace qo
{
	PlayScene::PlayScene()
		: mPlayer(nullptr)
	{
	}

	PlayScene::~PlayScene()
	{

	}

	void PlayScene::Initialize()
	{		
		mPlayer = new Player();
		Transform* PlayerTransform = mPlayer->AddComponent<Transform>();
		PlayerTransform->SetPosition(Vector3(0.0f, 0.0f, 0.0f));
		PlayerTransform->SetScale(Vector3(0.1f, 0.3f, 0.f));
		//PlayerTransform->SetColor(Vector4(0.f, 0.f, 1.f, 0.f));

		MeshRenderer* PlayerMeshRenderer = mPlayer->AddComponent<MeshRenderer>();
		PlayerMeshRenderer->SetMesh(ResourceManager::Find<Mesh>(L"TextureMesh"));
		PlayerMeshRenderer->SetShader(ResourceManager::Find<Shader>(L"TextureShader"));	

		Collider* PlayerCollider = mPlayer->AddComponent<Collider>();
		PlayerCollider->SetScale(PlayerTransform->GetScale());
					 
		mPlayer->AddComponent<Rigidbody>();
		
		mPlayer->AddComponent<PlayerScript>();

		// 총 생성
		mPlayer->AddGun(eGunType::Superposition);
		mPlayer->AddGun(eGunType::Entanglement);
		mPlayer->AddGun(eGunType::Teleportation);

		mPlayer->ChangeActiveGun(eGunType::Superposition);

		mPlayer->Initialize();

		AddGameObject(mPlayer, LAYER::PLAYER);
		Camera::SetTarget(mPlayer);

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
		eventSwitch = new EventSwitch();
		Transform* DSTransform = eventSwitch->AddComponent<Transform>();
		DSTransform->SetPositionInPixels(-500, 200, 0);
		DSTransform->SetScaleInPixels(400, 400, 0);
		DSTransform->SetColor(Vector4(0.5f, 0.5f, 0.5f, 0.f));

		MeshRenderer* DSMeshRenderer = eventSwitch->AddComponent<MeshRenderer>();
		DSMeshRenderer->SetMesh(ResourceManager::Find<Mesh>(L"RectangleMesh"));
		DSMeshRenderer->SetShader(ResourceManager::Find<Shader>(L"ColorTestShader"));

		Collider* DSCollider = eventSwitch->AddComponent<Collider>();
		DSCollider->SetScale(DSTransform->GetScale());

		AddGameObject(eventSwitch, LAYER::WALL);

		CollisionManager::CollisionLayerCheck(LAYER::PLAYER, LAYER::WALL, TRUE);
		CollisionManager::CollisionLayerCheck(LAYER::BULLET, LAYER::WALL, TRUE);

		// 잠긴 문 개체 생성
		/*lockeddoor = new LockedDoor();
		Transform* LockedDoorTransform = lockeddoor->AddComponent<Transform>();
		LockedDoorTransform->SetPositionInPixels(500, 200, 0);
		LockedDoorTransform->SetScaleInPixels(400, 400, 0);
		LockedDoorTransform->SetColor(Vector4(0.5f, 0.5f, 0.5f, 0.f));

		MeshRenderer* LockedDoorMeshRenderer = lockeddoor->AddComponent<MeshRenderer>();
		LockedDoorMeshRenderer->SetMesh(ResourceManager::Find<Mesh>(L"RectangleMesh"));
		LockedDoorMeshRenderer->SetShader(ResourceManager::Find<Shader>(L"ColorTestShader"));

		Collider* LockedDoorCollider = lockeddoor->AddComponent<Collider>();
		LockedDoorCollider->SetScale(LockedDoorTransform->GetScale());

		AddGameObject(lockeddoor, LAYER::WALL);*/

		CollisionManager::CollisionLayerCheck(LAYER::PLAYER, LAYER::WALL, TRUE);

		LabTurret* enemy1 = new LabTurret();
		Transform* EnemyTransform = enemy1->AddComponent<Transform>();
		EnemyTransform->SetPositionInPixels(300, 400, 0);
		EnemyTransform->SetScaleInPixels(50, 50, 0);
		EnemyTransform->SetColor(Vector4(1.f, 0.f, 0.f, 0.f));

		MeshRenderer* EnemyMeshRenderer = enemy1->AddComponent<MeshRenderer>();
		EnemyMeshRenderer->SetMesh(ResourceManager::Find<Mesh>(L"RectangleMesh"));
		EnemyMeshRenderer->SetShader(ResourceManager::Find<Shader>(L"ColorTestShader"));

		Collider* EnemyCollider = enemy1->AddComponent<Collider>();
		EnemyCollider->SetScale(EnemyTransform->GetScale());

		AddGameObject(enemy1, LAYER::ENEMY);

		CollisionManager::CollisionLayerCheck(LAYER::PLAYER, LAYER::WALL, TRUE);

		LabGuard* enemy2 = new LabGuard();
		EnemyTransform = enemy2->AddComponent<Transform>();
		EnemyTransform->SetPositionInPixels(300, 600, 0);
		EnemyTransform->SetScaleInPixels(50, 50, 0);
		EnemyTransform->SetColor(Vector4(1.f, 0.f, 0.f, 0.f));

		EnemyMeshRenderer = enemy2->AddComponent<MeshRenderer>();
		EnemyMeshRenderer->SetMesh(ResourceManager::Find<Mesh>(L"RectangleMesh"));
		EnemyMeshRenderer->SetShader(ResourceManager::Find<Shader>(L"ColorTestShader"));

		EnemyCollider = enemy2->AddComponent<Collider>();
		EnemyCollider->SetScale(EnemyTransform->GetScale());

		enemy2->AddComponent<LabGuardScript>();

		AddGameObject(enemy2, LAYER::ENEMY);


		CollisionManager::CollisionLayerCheck(LAYER::BULLET, LAYER::ENEMY, TRUE);

		HPUI* hpui = new HPUI(mPlayer);
		Transform* hpuiTransform = hpui->AddComponent<Transform>();
		hpuiTransform->SetPositionInPixels(300, 830, 0);
		hpuiTransform->SetScaleInPixels(400, 50, 0);
		hpuiTransform->SetColor(Vector4(1.f, 0.f, 0.f, 0.f));
		hpuiTransform->SetAffectedCamera(false);
		hpui->SetFixedPosition(Vector3(300.f, 830.f, 0));
		hpui->SetFixedScale(Vector3(400.f, 50.f, 0));

		MeshRenderer* hpuiMeshRenderer = hpui->AddComponent<MeshRenderer>();
		hpuiMeshRenderer->SetMesh(ResourceManager::Find<Mesh>(L"RectangleMesh"));
		hpuiMeshRenderer->SetShader(ResourceManager::Find<Shader>(L"ColorTestShader"));

		hpui->AddComponent<HPUIScript>();

		AddGameObject(hpui, LAYER::UI);

		HPUIBackGround* hpuiBG = new HPUIBackGround();
		hpuiTransform = hpuiBG->AddComponent<Transform>();
		hpuiTransform->SetPositionInPixels(300, 830, 0);
		hpuiTransform->SetScaleInPixels(400, 50, 0);
		hpuiTransform->SetColor(Vector4(0.f, 0.f, 0.f, 0.f));
		hpuiTransform->SetAffectedCamera(false);

		hpuiMeshRenderer = hpuiBG->AddComponent<MeshRenderer>();
		hpuiMeshRenderer->SetMesh(ResourceManager::Find<Mesh>(L"RectangleMesh"));
		hpuiMeshRenderer->SetShader(ResourceManager::Find<Shader>(L"ColorTestShader"));
		
		AddGameObject(hpuiBG, LAYER::UI);
	}

	void PlayScene::Update()
	{
		Scene::Update();

		if (eventSwitch->GetEventActive())
		{
			lockeddoor->SetLocked(false);
		}
	}

	void PlayScene::LateUpdate()
	{
		Scene* scene = SceneManager::GetActiveScene();
		Scene::LateUpdate();
	}

	void PlayScene::Render()
	{
		Scene::Render();
	}

	void PlayScene::Enter()
	{
		Camera::SetTarget(mPlayer);
	}

	void PlayScene::Exit()
	{
	}
}
