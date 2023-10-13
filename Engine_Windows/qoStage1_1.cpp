#include "qoStage1_1.h"
#include "qoResourceManager.h"
#include "qoCollisionManager.h"

#include "qoTransform.h"
#include "qoMeshRenderer.h"
#include "qoCollider.h"
#include "qoRigidbody.h"
#include "qoPlayerScript.h"
#include "qoPlayer.h"
#include "qoRigidbody.h"
#include "qoCamera.h"
#include "qoGunItem.h"
#include "qoHPUI.h"
#include "qoHPUIBackGround.h"
#include "qoHPUIScript.h"

#include "qoLabGuard.h"
#include "qoLabGuardScript.h"
#include "qoLabTurret.h"
#include "qoLabTurretScript.h"

#include "qoInput.h"
#include "qoSceneManager.h"

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
		#pragma region BG
		/*GameObject* BackGround = new GameObject();
		Transform* BackGroundTransform = BackGround->AddComponent<Transform>();
		BackGroundTransform->SetPositionInPixels(800, 450, 0.);
		BackGroundTransform->SetScaleInPixels(1600, 900, 0);
		BackGroundTransform->SetAffectedCamera(false);

		MeshRenderer* BackGroundMeshRenderer = BackGround->AddComponent<MeshRenderer>();
		BackGroundMeshRenderer->SetMesh(ResourceManager::Find<Mesh>(L"TextureMesh"));
		BackGroundMeshRenderer->SetShader(ResourceManager::Find<Shader>(L"TextureShader"));

		AddGameObject(BackGround, LAYER::BACKGROUND);*/
		#pragma endregion

		#pragma region Player
		mPlayer = new Player();
		Transform* PlayerTransform = mPlayer->AddComponent<Transform>();
		PlayerTransform->SetPositionInPixels(800, 384, 0.);
		PlayerTransform->SetScaleInPixels(64, 128, 0);
		//PlayerTransform->SetScale(1, 1, 0);
		PlayerTransform->SetColor(Vector4(0.f, 0.f, 1.f, 0.f));

		MeshRenderer* PlayerMeshRenderer = mPlayer->AddComponent<MeshRenderer>();
		PlayerMeshRenderer->SetMesh(ResourceManager::Find<Mesh>(L"RectangleMesh"));
		PlayerMeshRenderer->SetShader(ResourceManager::Find<Shader>(L"ColorTestShader"));

		Collider* PlayerCollider = mPlayer->AddComponent<Collider>();
		PlayerCollider->SetScale(PlayerTransform->GetScale());

		mPlayer->AddComponent<Rigidbody>();

		mPlayer->AddComponent<PlayerScript>();

		mPlayer->Initialize();

		AddGameObject(mPlayer, LAYER::PLAYER);
		Camera::SetTarget(mPlayer);
		#pragma endregion

		#pragma region LabGuard

		// 첫번째 근접 몬스터
		LabGuard* mLabGuard_1 = new LabGuard();
		Transform* LabGuardTransform = mLabGuard_1->AddComponent<Transform>();
		LabGuardTransform->SetPositionInPixels(2150, 305, 0.);
		LabGuardTransform->SetScaleInPixels(100, 100, 0);
		LabGuardTransform->SetColor(Vector4(1.f, 0.f, 0.f, 0.f));

		MeshRenderer* LabGuardMeshRenderer = mLabGuard_1->AddComponent<MeshRenderer>();
		LabGuardMeshRenderer->SetMesh(ResourceManager::Find<Mesh>(L"RectangleMesh"));
		LabGuardMeshRenderer->SetShader(ResourceManager::Find<Shader>(L"ColorTestShader"));

		Collider* LabGuardCollider = mLabGuard_1->AddComponent<Collider>();
		LabGuardCollider->SetScale(LabGuardTransform->GetScale());

		mLabGuard_1->AddComponent<Rigidbody>();
		mLabGuard_1->AddComponent<LabGuardScript>();
		mLabGuard_1->SetPlayer(mPlayer);
		mLabGuard_1->Initialize();

		AddGameObject(mLabGuard_1, LAYER::ENEMY);


		// 두번째 근접 몬스터
		LabGuard* mLabGuard_2 = new LabGuard();
		LabGuardTransform = mLabGuard_2->AddComponent<Transform>();
		LabGuardTransform->SetPositionInPixels(3200, 305, 0.);
		LabGuardTransform->SetScaleInPixels(100, 100, 0);
		LabGuardTransform->SetColor(Vector4(1.f, 0.f, 0.f, 0.f));

		LabGuardMeshRenderer = mLabGuard_2->AddComponent<MeshRenderer>();
		LabGuardMeshRenderer->SetMesh(ResourceManager::Find<Mesh>(L"RectangleMesh"));
		LabGuardMeshRenderer->SetShader(ResourceManager::Find<Shader>(L"ColorTestShader"));

		LabGuardCollider = mLabGuard_2->AddComponent<Collider>();
		LabGuardCollider->SetScale(LabGuardTransform->GetScale());

		mLabGuard_2->AddComponent<Rigidbody>();
		mLabGuard_2->AddComponent<LabGuardScript>();
		mLabGuard_2->SetPlayer(mPlayer);
		mLabGuard_2->Initialize();

		AddGameObject(mLabGuard_2, LAYER::ENEMY);

		// 세번째 근접 몬스터
		LabGuard* mLabGuard_3 = new LabGuard();
		LabGuardTransform = mLabGuard_3->AddComponent<Transform>();
		LabGuardTransform->SetPositionInPixels(5000, 305, 0.);
		LabGuardTransform->SetScaleInPixels(100, 100, 0);
		LabGuardTransform->SetColor(Vector4(1.f, 0.f, 0.f, 0.f));

		LabGuardMeshRenderer = mLabGuard_3->AddComponent<MeshRenderer>();
		LabGuardMeshRenderer->SetMesh(ResourceManager::Find<Mesh>(L"RectangleMesh"));
		LabGuardMeshRenderer->SetShader(ResourceManager::Find<Shader>(L"ColorTestShader"));

		LabGuardCollider = mLabGuard_3->AddComponent<Collider>();
		LabGuardCollider->SetScale(LabGuardTransform->GetScale());

		mLabGuard_3->AddComponent<Rigidbody>();
		mLabGuard_3->AddComponent<LabGuardScript>();
		mLabGuard_3->SetPlayer(mPlayer);
		mLabGuard_3->Initialize();

		AddGameObject(mLabGuard_3, LAYER::ENEMY);
		#pragma endregion

		#pragma region LabTurret
		
		// 첫번째 포탑
		LabTurret* LabTurret_1 = new LabTurret();
		Transform* LabTurretTransform = LabTurret_1->AddComponent<Transform>();
		LabTurretTransform->SetPositionInPixels(2150, 400, 0.);
		LabTurretTransform->SetScaleInPixels(100, 200, 0);
		LabTurretTransform->SetColor(Vector4(1.f, 1.f, 0.f, 0.f));

		MeshRenderer* LabTurretMeshRenderer = LabTurret_1->AddComponent<MeshRenderer>();
		LabTurretMeshRenderer->SetMesh(ResourceManager::Find<Mesh>(L"RectangleMesh"));
		LabTurretMeshRenderer->SetShader(ResourceManager::Find<Shader>(L"ColorTestShader"));

		Collider* LabTurretCollider = LabTurret_1->AddComponent<Collider>();
		LabTurretCollider->SetScale(LabTurretTransform->GetScale());

		LabTurret_1->AddComponent<LabTurretScript>();
		LabTurret_1->AddComponent<Rigidbody>();
		LabTurret_1->SetPlayer(mPlayer);
		LabTurret_1->Initialize();

		AddGameObject(LabTurret_1, LAYER::ENEMY);
		#pragma endregion

		#pragma region Item
		GunItem* gunItem = new GunItem(eGunType::Superposition);
		CreateAndSetUpGameObject(gunItem, ITEM, 1200, 300, 100, 100, gunItem->GetColor());
		#pragma endregion

		#pragma region Map Layout
		//--------------------------------------------------------
		//						바닥 개체
		//--------------------------------------------------------
		const int StageFloorCount = 4;
		const int StepCount = 5;

		Floor* StageFloor[StageFloorCount];
		Floor* Step[StepCount];

		for (size_t i = 0; i < StageFloorCount; i++)	StageFloor[i] = new Floor();
		for (size_t i = 0; i < StepCount; i++)	Step[i] = new Floor();

		// 개체 생성
		CreateAndSetUpGameObject(StageFloor[0], FLOOR, 3200, 128, 6400, 256, Vector4(0.5f, 0.5f, 0.5f, 0.f));
		CreateAndSetUpGameObject(StageFloor[1], FLOOR, 1760, 1072, 3520, 992, Vector4(0.5f, 0.5f, 0.5f, 0.f));
		CreateAndSetUpGameObject(StageFloor[2], FLOOR, 4960, 1328, 2880, 480, Vector4(0.5f, 0.5f, 0.5f, 0.f));
		CreateAndSetUpGameObject(StageFloor[3], FLOOR, 5440, 704, 1920, 256, Vector4(0.5f, 0.5f, 0.5f, 0.f));
		CreateAndSetUpGameObject(Step[0], FLOOR, 4192, 288, 256, 64, Vector4(0.5f, 0.5f, 0.5f, 0.f));
		CreateAndSetUpGameObject(Step[1], FLOOR, 3808, 416, 256, 64, Vector4(0.5f, 0.5f, 0.5f, 0.f));
		CreateAndSetUpGameObject(Step[2], FLOOR, 4192, 544, 256, 64, Vector4(0.5f, 0.5f, 0.5f, 0.f));
		CreateAndSetUpGameObject(Step[3], FLOOR, 3808, 672, 256, 64, Vector4(0.5f, 0.5f, 0.5f, 0.f));
		CreateAndSetUpGameObject(Step[4], FLOOR, 4192, 800, 256, 64, Vector4(0.5f, 0.5f, 0.5f, 0.f));

		//--------------------------------------------------------
		//						벽 개체
		//--------------------------------------------------------
		const int StageWallCount = 2;
		const int CeilWallCount = 2;

		Wall* StageWall[StageWallCount];
		Wall* CeilWall[CeilWallCount];

		for (size_t i = 0; i < StageWallCount; i++)	StageWall[i] = new Wall();
		for (size_t i = 0; i < CeilWallCount; i++)	CeilWall[i] = new Wall();

		// 개체 생성
		CreateAndSetUpGameObject(StageWall[0], WALL, 64, 416, 128, 320, Vector4(0.5f, 0.5f, 0.5f, 0.f));
		CreateAndSetUpGameObject(StageWall[1], WALL, 6336, 960, 128, 256, Vector4(0.5f, 0.5f, 0.5f, 0.f));
		CreateAndSetUpGameObject(CeilWall[0], WALL, 1632, 512, 64, 128, Vector4(0.5f, 0.5f, 0.5f, 0.f));
		CreateAndSetUpGameObject(CeilWall[1], WALL, 6336, 512, 128, 128, Vector4(0.5f, 0.5f, 0.5f, 0.f));

		//--------------------------------------------------------
		//					파괴되는 벽 개체
		//--------------------------------------------------------
		DestuctibleWall* BreakWall = new DestuctibleWall();

		// 개체 생성
		CreateAndSetUpGameObject(BreakWall, WALL, 1632, 352, 64, 192, Vector4(0.5f, 0.5f, 0.5f, 0.f));

		//--------------------------------------------------------
		//					배리어 개체
		//--------------------------------------------------------
		Barrier* EventBarrier = new Barrier();

		// 개체 생성
		CreateAndSetUpGameObject(EventBarrier, WALL, 6112, 960, 64, 256, Vector4(0.5f, 0.5f, 0.5f, 0.f));

		//--------------------------------------------------------
		//				이벤트 스위치 개체
		//--------------------------------------------------------
		EventButton = new EventSwitch();

		// 개체 생성
		CreateAndSetUpGameObject(EventButton, WALL, 6240, 960, 64, 64, Vector4(0.5f, 0.5f, 0.5f, 0.f));

		//--------------------------------------------------------
		//					잠긴 문 개체
		//--------------------------------------------------------
		EventDoor = new LockedDoor();

		EventDoor->SetTag(1);

		// 개체 생성
		CreateAndSetUpGameObject(EventDoor, WALL, 6336, 352, 128, 192, Vector4(0.5f, 0.5f, 0.5f, 0.f));
		#pragma endregion

		#pragma region UI
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
		#pragma endregion

		#pragma region Managers
		CollisionManager::CollisionLayerCheck(LAYER::PLAYER, LAYER::FLOOR, TRUE);
		CollisionManager::CollisionLayerCheck(LAYER::PLAYER, LAYER::WALL, TRUE);
		CollisionManager::CollisionLayerCheck(LAYER::PLAYER, LAYER::ITEM, TRUE);
		CollisionManager::CollisionLayerCheck(LAYER::BULLET, LAYER::WALL, TRUE);
		CollisionManager::CollisionLayerCheck(LAYER::BULLET, LAYER::FLOOR, TRUE);
		CollisionManager::CollisionLayerCheck(LAYER::ENEMY, LAYER::FLOOR, TRUE);
		CollisionManager::CollisionLayerCheck(LAYER::ENEMY, LAYER::WALL, TRUE);
		CollisionManager::CollisionLayerCheck(LAYER::ENEMY, LAYER::PLAYER, TRUE);
		#pragma endregion
	}

	void Stage1_1::Update()
	{
		Scene::Update();

		if (EventButton->GetEventActive())	UnlockDoor(1);
	}

	void Stage1_1::LateUpdate()
	{
		Scene::LateUpdate();

		if (Input::GetKeyState(KEY_CODE::L) == KEY_STATE::DOWN)
		{
			SceneManager::ReStartScene<Stage1_1>(GetName());
		}
	}

	void Stage1_1::Render()
	{
		Scene::Render();
	}

	void Stage1_1::UnlockDoor(int tag)
	{
		if (EventDoor->GetTag() == tag)	EventDoor->SetLocked(false);
	}

	void Stage1_1::Enter()
	{
		Camera::SetTarget(mPlayer);
	}

	void Stage1_1::Exit()
	{
	}

}
