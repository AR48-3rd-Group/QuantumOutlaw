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
#include "qoTrigger.h"

#include "qoLabGuard.h"
#include "qoLabGuardScript.h"
#include "qoLabTurret.h"
#include "qoLabTurretScript.h"

#include "qoInput.h"
#include "qoSceneManager.h"

#include "qoApplication.h"

extern qo::Application application;

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
		mPlayer = new Player();
		Transform* PlayerTransform = mPlayer->AddComponent<Transform>();
		PlayerTransform->SetPositionInPixels(800, 384, 0.);
		PlayerTransform->SetScaleInPixels(64, 128, 0);
		//PlayerTransform->SetScale(1, 1, 0);
		PlayerTransform->SetColor(Vector4(0.f, 0.f, 1.f, 0.f));

		MeshRenderer* PlayerMeshRenderer = mPlayer->AddComponent<MeshRenderer>();
		PlayerMeshRenderer->SetMesh(ResourceManager::Find<Mesh>(L"TextureMesh"));
		PlayerMeshRenderer->SetShader(ResourceManager::Find<Shader>(L"TextureShader"));

		Collider* PlayerCollider = mPlayer->AddComponent<Collider>();
		PlayerCollider->SetScale(PlayerTransform->GetScale());

		mPlayer->AddComponent<Rigidbody>();

		mPlayer->AddComponent<PlayerScript>();

		mPlayer->Initialize();

		AddGameObject(mPlayer, LAYER::PLAYER);
		Camera::SetTarget(mPlayer);
		#pragma endregion

		#pragma region StageClear
		GameObject* clearImage = new GameObject();
		Transform* clearImageTransform = clearImage->AddComponent<Transform>();
		clearImageTransform->SetPositionInPixels(application.GetWidth() / 2.f, -100.f, 0);
		clearImageTransform->SetScaleInPixels(606, 103, 0);

		MeshRenderer* clearImageRenderer = clearImage->AddComponent<MeshRenderer>();
		clearImageRenderer->SetMesh(ResourceManager::Find<Mesh>(L"ChamjalMesh"));
		clearImageRenderer->SetShader(ResourceManager::Find<Shader>(L"ClearShader1"));

		clearImage->GetComponent<Transform>()->SetAffectedCamera(false);
		AddGameObject(clearImage, LAYER::UI);
		#pragma endregion

		#pragma region Item
		GunItem* gunItem = new GunItem(eGunType::Superposition);
		CreateAndSetUpGameObject(gunItem, ITEM, 1200, 300, 100, 100, gunItem->GetColor());
		#pragma endregion


		#pragma region Enemy
		// ��ü �Ҵ�
		for (size_t i = 0; i < LabGuardCount; i++)	EnemyLabGuard[i] = new LabGuard();

		// ��ü ���� ���� �߰�
		// ��ġ �� ����
		CreateAndSetUpGameObject(EnemyLabGuard[0], ENEMY, 1720, 320, 100, 100, Vector4(1.f, 0.f, 0.f, 0.f));
		CreateAndSetUpGameObject(EnemyLabGuard[1], ENEMY, 2120, 320, 100, 100, Vector4(1.f, 0.f, 0.f, 0.f));
		CreateAndSetUpGameObject(EnemyLabGuard[2], ENEMY, 2520, 320, 100, 100, Vector4(1.f, 0.f, 0.f, 0.f));
		CreateAndSetUpGameObject(EnemyLabGuard[3], ENEMY, 2900, 320, 100, 100, Vector4(1.f, 0.f, 0.f, 0.f));
		CreateAndSetUpGameObject(EnemyLabGuard[4], ENEMY, 5440, 840, 100, 100, Vector4(1.f, 0.f, 0.f, 0.f));
		CreateAndSetUpGameObject(EnemyLabGuard[5], ENEMY, 5440, 320, 100, 100, Vector4(1.f, 0.f, 0.f, 0.f));
		CreateAndSetUpGameObject(EnemyLabGuard[6], ENEMY, 5840, 320, 100, 100, Vector4(1.f, 0.f, 0.f, 0.f));

		// Script �� Rigidbody �߰� SetPlayer ����
		for (size_t i = 0; i < LabGuardCount; i++)
		{
			EnemyLabGuard[i]->AddComponent<LabGuardScript>();
			EnemyLabGuard[i]->AddComponent<Rigidbody>();
			EnemyLabGuard[i]->SetPlayer(mPlayer);
			EnemyLabGuard[i]->Initialize();
		}
		#pragma endregion

		#pragma region Map Layout
		//--------------------------------------------------------
		//						�ٴ� ��ü
		//--------------------------------------------------------
		const int StageFloorCount = 4;
		const int StepCount = 5;

		Floor* StageFloor[StageFloorCount];
		Floor* Step[StepCount];

		for (size_t i = 0; i < StageFloorCount; i++)	StageFloor[i] = new Floor();
		for (size_t i = 0; i < StepCount; i++)	Step[i] = new Floor();

		// ��ü ����
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
		//						�� ��ü
		//--------------------------------------------------------
		const int StageWallCount = 2;
		const int CeilWallCount = 2;

		Wall* StageWall[StageWallCount];
		Wall* CeilWall[CeilWallCount];

		for (size_t i = 0; i < StageWallCount; i++)	StageWall[i] = new Wall();
		for (size_t i = 0; i < CeilWallCount; i++)	CeilWall[i] = new Wall();

		// ��ü ����
		CreateAndSetUpGameObject(StageWall[0], WALL, 64, 416, 128, 320, Vector4(0.5f, 0.5f, 0.5f, 0.f));
		CreateAndSetUpGameObject(StageWall[1], WALL, 6336, 960, 128, 256, Vector4(0.5f, 0.5f, 0.5f, 0.f));
		CreateAndSetUpGameObject(CeilWall[0], WALL, 1632, 512, 64, 128, Vector4(0.5f, 0.5f, 0.5f, 0.f));
		CreateAndSetUpGameObject(CeilWall[1], WALL, 6336, 512, 128, 128, Vector4(0.5f, 0.5f, 0.5f, 0.f));

		//--------------------------------------------------------
		//					�ı��Ǵ� �� ��ü
		//--------------------------------------------------------
		DestuctibleWall* BreakWall = new DestuctibleWall();

		// ��ü ����
		CreateAndSetUpGameObject(BreakWall, WALL, 1632, 352, 64, 192, Vector4(0.5f, 0.5f, 0.5f, 0.f));

		//--------------------------------------------------------
		//					�踮�� ��ü
		//--------------------------------------------------------
		Barrier* EventBarrier = new Barrier();

		// ��ü ����
		CreateAndSetUpGameObject(EventBarrier, WALL, 6112, 960, 64, 256, Vector4(0.5f, 0.5f, 0.5f, 0.f));

		//--------------------------------------------------------
		//				�̺�Ʈ ����ġ ��ü
		//--------------------------------------------------------
		EventButton = new EventSwitch();

		// ��ü ����
		CreateAndSetUpGameObject(EventButton, WALL, 6240, 960, 64, 64, Vector4(0.5f, 0.5f, 0.5f, 0.f));

		//--------------------------------------------------------
		//					��� �� ��ü
		//--------------------------------------------------------
		EventDoor = new LockedDoor();

		EventDoor->SetTag(1);

		// ��ü ����
		CreateAndSetUpGameObject(EventDoor, WALL, 6336, 352, 128, 192, Vector4(0.5f, 0.5f, 0.5f, 0.f));
		#pragma endregion

		//--------------------------------------------------------
		//					Ʈ����
		//--------------------------------------------------------

		#pragma region SceneTrigger
		Trigger* SceneTrigger = new Trigger();
		SceneTrigger->SetType(eTriggerType::SceneChanger);
		SceneTrigger->SetSceneName(L"Stage1_2");
		SceneTrigger->SetSceneClearImage1(clearImage);
		CreateAndSetUpGameObject(SceneTrigger, TRIGGER, 6336, 352, 64, 64, Vector4(0.5f, 0.5f, 0.5f, 0.f));
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

		// ���� ���൵
		GameObject* ProgressImage = new GameObject();
		Transform* ProgressImageTransform = ProgressImage->AddComponent<Transform>();
		ProgressImageTransform->SetPositionInPixels(1450.f, 850.f, 0);
		ProgressImageTransform->SetScaleInPixels(300, 51, 0);

		MeshRenderer* ProgressImageRenderer = ProgressImage->AddComponent<MeshRenderer>();
		ProgressImageRenderer->SetMesh(ResourceManager::Find<Mesh>(L"ChamjalMesh"));
		ProgressImageRenderer->SetShader(ResourceManager::Find<Shader>(L"ProgressShader"));

		ProgressImage->GetComponent<Transform>()->SetAffectedCamera(false);
		AddGameObject(ProgressImage, LAYER::UI);

		GameObject* DungeonProcessUI1 = new GameObject();
		CreateAndSetUpGameObject(DungeonProcessUI1, enums::UI, 1400, 800, 32, 32, Vector4(1.f, 0.f, 0.f, 0.f));
		DungeonProcessUI1->GetComponent<Transform>()->SetAffectedCamera(false);

		GameObject* DungeonProcessUI2 = new GameObject();
		CreateAndSetUpGameObject(DungeonProcessUI2, enums::UI, 1500, 800, 32, 32, Vector4(1.f, 0.f, 0.f, 0.f));
		DungeonProcessUI2->GetComponent<Transform>()->SetAffectedCamera(false);

		#pragma endregion

		#pragma region Managers
		CollisionManager::CollisionLayerCheck(LAYER::PLAYER, LAYER::FLOOR, TRUE);
		CollisionManager::CollisionLayerCheck(LAYER::PLAYER, LAYER::WALL, TRUE);
		CollisionManager::CollisionLayerCheck(LAYER::PLAYER, LAYER::ITEM, TRUE);
		CollisionManager::CollisionLayerCheck(LAYER::PLAYER, LAYER::BULLET, TRUE);
		CollisionManager::CollisionLayerCheck(LAYER::BULLET, LAYER::WALL, TRUE);
		CollisionManager::CollisionLayerCheck(LAYER::BULLET, LAYER::FLOOR, TRUE);
		CollisionManager::CollisionLayerCheck(LAYER::BULLET, LAYER::ENEMY, TRUE);
		CollisionManager::CollisionLayerCheck(LAYER::ENEMY, LAYER::FLOOR, TRUE);
		CollisionManager::CollisionLayerCheck(LAYER::ENEMY, LAYER::WALL, TRUE);
		CollisionManager::CollisionLayerCheck(LAYER::ENEMY, LAYER::PLAYER, TRUE);
		CollisionManager::CollisionLayerCheck(LAYER::PLAYER, LAYER::TRIGGER, TRUE);
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

		if (mPlayer->GetCurHP() <= 0.f
			|| Input::GetKeyState(KEY_CODE::L) == KEY_STATE::DOWN)
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
