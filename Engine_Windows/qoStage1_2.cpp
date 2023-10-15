#include "qoStage1_2.h"
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
#include "qoLabTurret.h"
#include "qoLabGuardScript.h"
#include "qoLabTurretScript.h"

#include "qoInput.h"
#include "qoSceneManager.h"

#include "qoApplication.h"

extern qo::Application application;

namespace qo
{
	Stage1_2::Stage1_2()
	{
	}

	Stage1_2::~Stage1_2()
	{
	}

	void Stage1_2::Initialize()
	{
		#pragma region Player
		mPlayer = new Player();
		Transform* PlayerTransform = mPlayer->AddComponent<Transform>();
		PlayerTransform->SetPositionInPixels(800, 384, 0);
		PlayerTransform->SetScaleInPixels(64, 128, 0);
		PlayerTransform->SetColor(Vector4(0.f, 0.f, 1.f, 0.f));

		MeshRenderer* PlayerMeshRenderer = mPlayer->AddComponent<MeshRenderer>();
		PlayerMeshRenderer->SetMesh(ResourceManager::Find<Mesh>(L"TextureMesh"));
		PlayerMeshRenderer->SetShader(ResourceManager::Find<Shader>(L"TextureShader"));

		Collider* PlayerCollider = mPlayer->AddComponent<Collider>();
		PlayerCollider->SetScale(PlayerTransform->GetScale());

		mPlayer->AddComponent<Rigidbody>();

		mPlayer->AddComponent<PlayerScript>();

		// 총 생성
		mPlayer->AddGun(eGunType::Superposition);
		mPlayer->ChangeActiveGun(eGunType::Superposition);

		mPlayer->Initialize();

		AddGameObject(mPlayer, LAYER::PLAYER);
		Camera::SetTarget(mPlayer);
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

		// 던전 진행도
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
		CreateAndSetUpGameObject(DungeonProcessUI1, enums::UI, 1400, 800, 32, 32, Vector4(0.f, 1.f, 0.f, 0.f));
		DungeonProcessUI1->GetComponent<Transform>()->SetAffectedCamera(false);

		GameObject* DungeonProcessUI2 = new GameObject();
		CreateAndSetUpGameObject(DungeonProcessUI2, enums::UI, 1500, 800, 32, 32, Vector4(1.f, 0.f, 0.f, 0.f));
		DungeonProcessUI2->GetComponent<Transform>()->SetAffectedCamera(false);
		#pragma endregion

		#pragma region Item
		GunItem* gunItem = new GunItem(eGunType::Entanglement);
		CreateAndSetUpGameObject(gunItem, ITEM, 1200, 300, 100, 100, gunItem->GetColor());

		GunItem* gunItem2 = new GunItem(eGunType::Teleportation);
		CreateAndSetUpGameObject(gunItem2, ITEM, 6222, 190, 100, 100, gunItem2->GetColor());
		#pragma endregion

		#pragma region Enemy
		// 객체 할당
		for (size_t i = 0; i < LabGuardCount; i++)	EnemyLabGuard[i] = new LabGuard();
		for (size_t i = 0; i < LabTurretCount; i++)	EnemyLabTurret[i] = new LabTurret();

		// 객체 생성 정보 추가
		// 위치 및 색상
		CreateAndSetUpGameObject(EnemyLabGuard[0], ENEMY, 1376, 180, 100, 100, Vector4(1.f, 0.f, 0.f, 0.f));
		CreateAndSetUpGameObject(EnemyLabGuard[1], ENEMY, 2276, 192, 100, 100, Vector4(1.f, 0.f, 0.f, 0.f));
		CreateAndSetUpGameObject(EnemyLabGuard[2], ENEMY, 2594, 192, 100, 100, Vector4(1.f, 0.f, 0.f, 0.f));
		CreateAndSetUpGameObject(EnemyLabGuard[3], ENEMY, 1832, 322, 100, 100, Vector4(1.f, 0.f, 0.f, 0.f));
		CreateAndSetUpGameObject(EnemyLabGuard[4], ENEMY, 2432, 576, 100, 100, Vector4(1.f, 0.f, 0.f, 0.f));
		CreateAndSetUpGameObject(EnemyLabGuard[5], ENEMY, 3552, 704, 100, 100, Vector4(1.f, 0.f, 0.f, 0.f));
		CreateAndSetUpGameObject(EnemyLabGuard[6], ENEMY, 3840, 704, 100, 100, Vector4(1.f, 0.f, 0.f, 0.f));
		CreateAndSetUpGameObject(EnemyLabGuard[7], ENEMY, 4096, 704, 100, 100, Vector4(1.f, 0.f, 0.f, 0.f));
		CreateAndSetUpGameObject(EnemyLabGuard[8], ENEMY, 4384, 704, 100, 100, Vector4(1.f, 0.f, 0.f, 0.f));
		CreateAndSetUpGameObject(EnemyLabGuard[9], ENEMY, 5040, 704, 100, 100, Vector4(1.f, 0.f, 0.f, 0.f));
		CreateAndSetUpGameObject(EnemyLabGuard[10], ENEMY, 5744, 704, 100, 100, Vector4(1.f, 0.f, 0.f, 0.f));
		CreateAndSetUpGameObject(EnemyLabGuard[11], ENEMY, 4448, 1472, 100, 100, Vector4(1.f, 0.f, 0.f, 0.f));
		CreateAndSetUpGameObject(EnemyLabGuard[12], ENEMY, 4416, 1728, 100, 100, Vector4(1.f, 0.f, 0.f, 0.f));
		CreateAndSetUpGameObject(EnemyLabGuard[13], ENEMY, 4672, 1728, 100, 100, Vector4(1.f, 0.f, 0.f, 0.f));
		CreateAndSetUpGameObject(EnemyLabGuard[14], ENEMY, 3032, 1472, 100, 100, Vector4(1.f, 0.f, 0.f, 0.f));
		CreateAndSetUpGameObject(EnemyLabGuard[15], ENEMY, 2288, 1472, 100, 100, Vector4(1.f, 0.f, 0.f, 0.f));
		CreateAndSetUpGameObject(EnemyLabGuard[16], ENEMY, 632, 1664, 100, 100, Vector4(1.f, 0.f, 0.f, 0.f));
		CreateAndSetUpGameObject(EnemyLabGuard[17], ENEMY, 1680, 2500, 100, 100, Vector4(1.f, 0.f, 0.f, 0.f));
		CreateAndSetUpGameObject(EnemyLabGuard[18], ENEMY, 1872, 2500, 100, 100, Vector4(1.f, 0.f, 0.f, 0.f));
		CreateAndSetUpGameObject(EnemyLabGuard[19], ENEMY, 2170.5, 2500, 100, 100, Vector4(1.f, 0.f, 0.f, 0.f));
		CreateAndSetUpGameObject(EnemyLabGuard[20], ENEMY, 2362.5, 2500, 100, 100, Vector4(1.f, 0.f, 0.f, 0.f));
		CreateAndSetUpGameObject(EnemyLabGuard[21], ENEMY, 2666.5, 2500, 100, 100, Vector4(1.f, 0.f, 0.f, 0.f));
		CreateAndSetUpGameObject(EnemyLabGuard[22], ENEMY, 2858.5, 2500, 100, 100, Vector4(1.f, 0.f, 0.f, 0.f));
		CreateAndSetUpGameObject(EnemyLabGuard[23], ENEMY, 3194.5, 2500, 100, 100, Vector4(1.f, 0.f, 0.f, 0.f));
		CreateAndSetUpGameObject(EnemyLabGuard[24], ENEMY, 3386.5, 2500, 100, 100, Vector4(1.f, 0.f, 0.f, 0.f));
		CreateAndSetUpGameObject(EnemyLabGuard[25], ENEMY, 5936, 2944, 100, 100, Vector4(1.f, 0.f, 0.f, 0.f));
		CreateAndSetUpGameObject(EnemyLabGuard[26], ENEMY, 480, 768, 100, 100, Vector4(1.f, 0.f, 0.f, 0.f));
		CreateAndSetUpGameObject(EnemyLabGuard[27], ENEMY, 1186, 768, 100, 100, Vector4(1.f, 0.f, 0.f, 0.f));

		CreateAndSetUpGameObject(EnemyLabTurret[0], ENEMY, 3792, 864, 64, 64, Vector4(1.f, 1.f, 0.f, 0.f));
		CreateAndSetUpGameObject(EnemyLabTurret[1], ENEMY, 4416, 864, 64, 64, Vector4(1.f, 1.f, 0.f, 0.f));
		CreateAndSetUpGameObject(EnemyLabTurret[2], ENEMY, 96, 896, 64, 64, Vector4(1.f, 1.f, 0.f, 0.f));
		CreateAndSetUpGameObject(EnemyLabTurret[3], ENEMY, 96, 768, 64, 64, Vector4(1.f, 1.f, 0.f, 0.f));
		CreateAndSetUpGameObject(EnemyLabTurret[4], ENEMY, 5806, 1824, 64, 64, Vector4(1.f, 1.f, 0.f, 0.f));
		CreateAndSetUpGameObject(EnemyLabTurret[5], ENEMY, 3952, 1632, 64, 64, Vector4(1.f, 1.f, 0.f, 0.f));
		CreateAndSetUpGameObject(EnemyLabTurret[6], ENEMY, 3248, 1632, 64, 64, Vector4(1.f, 1.f, 0.f, 0.f));
		CreateAndSetUpGameObject(EnemyLabTurret[7], ENEMY, 2223, 1632, 64, 64, Vector4(1.f, 1.f, 0.f, 0.f));
		CreateAndSetUpGameObject(EnemyLabTurret[8], ENEMY, 1968, 2528, 64, 64, Vector4(1.f, 1.f, 0.f, 0.f));
		CreateAndSetUpGameObject(EnemyLabTurret[9], ENEMY, 2479.5, 2528, 64, 64, Vector4(1.f, 1.f, 0.f, 0.f));
		CreateAndSetUpGameObject(EnemyLabTurret[10], ENEMY, 2992, 2528, 64, 64, Vector4(1.f, 1.f, 0.f, 0.f));
		CreateAndSetUpGameObject(EnemyLabTurret[11], ENEMY, 3504, 2528, 64, 64, Vector4(1.f, 1.f, 0.f, 0.f));

		// Script 및 Rigidbody 추가 SetPlayer 적용
		for (size_t i = 0; i < LabGuardCount; i++)
		{
			EnemyLabGuard[i]->AddComponent<LabGuardScript>();
			EnemyLabGuard[i]->AddComponent<Rigidbody>();
			EnemyLabGuard[i]->SetPlayer(mPlayer);
			EnemyLabGuard[i]->Initialize();
		}

		for (size_t i = 17; i < 25; i++)
		{
			EnemyLabGuard[i]->GetComponent<Rigidbody>()->SetActive(false);
		}

		for (size_t i = 0; i < LabTurretCount; i++)
		{
			EnemyLabTurret[i]->AddComponent<LabTurretScript>();
			EnemyLabTurret[i]->AddComponent<Rigidbody>()->SetActive(false);
			EnemyLabTurret[i]->SetPlayer(mPlayer);
			EnemyLabTurret[i]->Initialize();
		}

		#pragma endregion

		#pragma region StageClear
		GameObject* clearImage = new GameObject();
		Transform* clearImageTransform = clearImage->AddComponent<Transform>();
		clearImageTransform->SetPositionInPixels(application.GetWidth() / 2.f, -100.f, 0);
		clearImageTransform->SetScaleInPixels(626, 97, 0);

		MeshRenderer* clearImageRenderer = clearImage->AddComponent<MeshRenderer>();
		clearImageRenderer->SetMesh(ResourceManager::Find<Mesh>(L"ChamjalMesh"));
		clearImageRenderer->SetShader(ResourceManager::Find<Shader>(L"ClearShader2"));

		clearImage->GetComponent<Transform>()->SetAffectedCamera(false);
		AddGameObject(clearImage, LAYER::UI);
		#pragma endregion

		#pragma region Map Layout
		//--------------------------------------------------------
		//						바닥 개체
		//--------------------------------------------------------
		const int StageFloorCount = 2;
		const int Floor_1_Count = 3;
		const int Floor_2_Count = 9;
		const int Floor_3_Count = 5;
		const int Step_1_Count = 4;
		const int Step_2_Count = 4;
		const int Step_3_Count = 4;
		const int Step_4_Count = 4;
		const int Step_5_Count = 2;

		Floor* StageFloor[StageFloorCount];
		Floor* Floor_1[Floor_1_Count];
		Floor* Floor_2[Floor_2_Count];
		Floor* Floor_3[Floor_3_Count];
		Floor* Step_1[Step_1_Count];
		Floor* Step_2[Step_2_Count];
		Floor* Step_3[Step_3_Count];
		Floor* Step_4[Step_4_Count];
		Floor* Step_5[Step_5_Count];

		for (size_t i = 0; i < StageFloorCount; i++)	StageFloor[i] = new Floor();
		for (size_t i = 0; i < Floor_1_Count; i++)		Floor_1[i] = new Floor();
		for (size_t i = 0; i < Floor_2_Count; i++)		Floor_2[i] = new Floor();
		for (size_t i = 0; i < Floor_3_Count; i++)		Floor_3[i] = new Floor();
		for (size_t i = 0; i < Step_1_Count; i++)		Step_1[i] = new Floor();
		for (size_t i = 0; i < Step_2_Count; i++)		Step_2[i] = new Floor();
		for (size_t i = 0; i < Step_3_Count; i++)		Step_3[i] = new Floor();
		for (size_t i = 0; i < Step_4_Count; i++)		Step_4[i] = new Floor();
		for (size_t i = 0; i < Step_5_Count; i++)		Step_5[i] = new Floor();

		// 개체 생성
		CreateAndSetUpGameObject(StageFloor[0], FLOOR, 3200, 64, 6400, 128, Vector4(0.5f, 0.5f, 0.5f, 0.f));
		CreateAndSetUpGameObject(StageFloor[1], FLOOR, 3232, 3136, 6336, 128, Vector4(0.5f, 0.5f, 0.5f, 0.f));
		CreateAndSetUpGameObject(Floor_1[0], FLOOR, 800, 576, 1600, 256, Vector4(0.5f, 0.5f, 0.5f, 0.f));
		CreateAndSetUpGameObject(Floor_1[1], FLOOR, 3712, 384, 1600, 512, Vector4(0.5f, 0.5f, 0.5f, 0.f));
		CreateAndSetUpGameObject(Floor_1[2], FLOOR, 5520, 544, 1632, 192, Vector4(0.5f, 0.5f, 0.5f, 0.f));
		CreateAndSetUpGameObject(Floor_2[0], FLOOR, 3408, 1056, 4992, 192, Vector4(0.5f, 0.5f, 0.5f, 0.f));
		CreateAndSetUpGameObject(Floor_2[1], FLOOR, 320, 1280, 512, 640, Vector4(0.5f, 0.5f, 0.5f, 0.f));
		CreateAndSetUpGameObject(Floor_2[2], FLOOR, 832, 1536, 512, 128, Vector4(0.5f, 0.5f, 0.5f, 0.f));
		CreateAndSetUpGameObject(Floor_2[3], FLOOR, 2512, 1824, 768, 192, Vector4(0.5f, 0.5f, 0.5f, 0.f));
		CreateAndSetUpGameObject(Floor_2[4], FLOOR, 2512, 1280, 768, 256, Vector4(0.5f, 0.5f, 0.5f, 0.f));
		CreateAndSetUpGameObject(Floor_2[5], FLOOR, 3600, 1760, 512, 320, Vector4(0.5f, 0.5f, 0.5f, 0.f));
		CreateAndSetUpGameObject(Floor_2[6], FLOOR, 4528, 1632, 512, 64, Vector4(0.5f, 0.5f, 0.5f, 0.f));
		CreateAndSetUpGameObject(Floor_2[7], FLOOR, 4656, 1280, 768, 256, Vector4(0.5f, 0.5f, 0.5f, 0.f));
		CreateAndSetUpGameObject(Floor_2[8], FLOOR, 6040, 1632, 592, 64, Vector4(0.5f, 0.5f, 0.5f, 0.f));
		CreateAndSetUpGameObject(Floor_3[0], FLOOR, 2720, 1984, 3264, 128, Vector4(0.5f, 0.5f, 0.5f, 0.f));
		CreateAndSetUpGameObject(Floor_3[1], FLOOR, 704, 2112, 768, 384, Vector4(0.5f, 0.5f, 0.5f, 0.f));
		CreateAndSetUpGameObject(Floor_3[2], FLOOR, 5376, 2112, 2048, 384, Vector4(0.5f, 0.5f, 0.5f, 0.f));
		CreateAndSetUpGameObject(Floor_3[3], FLOOR, 2303, 2848, 4478, 448, Vector4(0.5f, 0.5f, 0.5f, 0.f));
		CreateAndSetUpGameObject(Floor_3[4], FLOOR, 5600, 2752, 1600, 256, Vector4(0.5f, 0.5f, 0.5f, 0.f));
		CreateAndSetUpGameObject(Step_1[0], FLOOR, 1792, 224, 256, 64, Vector4(0.5f, 0.5f, 0.5f, 0.f));
		CreateAndSetUpGameObject(Step_1[1], FLOOR, 2112, 352, 256, 64, Vector4(0.5f, 0.5f, 0.5f, 0.f));
		CreateAndSetUpGameObject(Step_1[2], FLOOR, 2432, 480, 256, 64, Vector4(0.5f, 0.5f, 0.5f, 0.f));
		CreateAndSetUpGameObject(Step_1[3], FLOOR, 2768, 608, 288, 64, Vector4(0.5f, 0.5f, 0.5f, 0.f));
		CreateAndSetUpGameObject(Step_2[0], FLOOR, 6272, 736, 128, 64, Vector4(0.5f, 0.5f, 0.5f, 0.f));
		CreateAndSetUpGameObject(Step_2[1], FLOOR, 5968, 864, 128, 64, Vector4(0.5f, 0.5f, 0.5f, 0.f));
		CreateAndSetUpGameObject(Step_2[2], FLOOR, 6272, 992, 128, 64, Vector4(0.5f, 0.5f, 0.5f, 0.f));
		CreateAndSetUpGameObject(Step_2[3], FLOOR, 5968, 1120, 128, 64, Vector4(0.5f, 0.5f, 0.5f, 0.f));
		CreateAndSetUpGameObject(Step_3[0], FLOOR, 5552, 1248, 256, 64, Vector4(0.5f, 0.5f, 0.5f, 0.f));
		CreateAndSetUpGameObject(Step_3[1], FLOOR, 5184, 1376, 288, 64, Vector4(0.5f, 0.5f, 0.5f, 0.f));
		CreateAndSetUpGameObject(Step_3[2], FLOOR, 5552, 1504, 256, 64, Vector4(0.5f, 0.5f, 0.5f, 0.f));
		CreateAndSetUpGameObject(Step_3[3], FLOOR, 5184, 1632, 288, 64, Vector4(0.5f, 0.5f, 0.5f, 0.f));
		CreateAndSetUpGameObject(Step_4[0], FLOOR, 4144, 1376, 256, 64, Vector4(0.5f, 0.5f, 0.5f, 0.f));
		CreateAndSetUpGameObject(Step_4[1], FLOOR, 3824, 1248, 256, 64, Vector4(0.5f, 0.5f, 0.5f, 0.f));
		CreateAndSetUpGameObject(Step_4[2], FLOOR, 3376, 1248, 256, 64, Vector4(0.5f, 0.5f, 0.5f, 0.f));
		CreateAndSetUpGameObject(Step_4[3], FLOOR, 3040, 1376, 288, 64, Vector4(0.5f, 0.5f, 0.5f, 0.f));
		CreateAndSetUpGameObject(Step_5[0], FLOOR, 1984, 1376, 288, 64, Vector4(0.5f, 0.5f, 0.5f, 0.f));
		CreateAndSetUpGameObject(Step_5[1], FLOOR, 1648, 1248, 256, 64, Vector4(0.5f, 0.5f, 0.5f, 0.f));

		//--------------------------------------------------------
		//						벽 개체
		//--------------------------------------------------------
		const int StageWallCount = 4;
		const int FieldWallCount = 2;
		const int CeilWallCount = 14;

		Wall* StageWall[StageWallCount];
		Wall* FieldWall[FieldWallCount];
		Wall* CeilWall[CeilWallCount];

		for (size_t i = 0; i < StageWallCount; i++)	StageWall[i] = new Wall();
		for (size_t i = 0; i < FieldWallCount; i++)	FieldWall[i] = new Wall();
		for (size_t i = 0; i < CeilWallCount; i++)	CeilWall[i] = new Wall();

		// 개체 생성
		CreateAndSetUpGameObject(StageWall[0], WALL, 32, 288, 64, 320, Vector4(0.5f, 0.5f, 0.5f, 0.f));
		CreateAndSetUpGameObject(StageWall[1], WALL, 32, 1952, 64, 2496, Vector4(0.5f, 0.5f, 0.5f, 0.f));
		CreateAndSetUpGameObject(StageWall[2], WALL, 6368, 1024, 64, 1792, Vector4(0.5f, 0.5f, 0.5f, 0.f));
		CreateAndSetUpGameObject(StageWall[3], WALL, 6368, 2976, 64, 192, Vector4(0.5f, 0.5f, 0.5f, 0.f));
		CreateAndSetUpGameObject(FieldWall[0], WALL, 1536, 832, 128, 256, Vector4(0.5f, 0.5f, 0.5f, 0.f));
		CreateAndSetUpGameObject(FieldWall[1], WALL, 4304, 1792, 64, 256, Vector4(0.5f, 0.5f, 0.5f, 0.f));
		CreateAndSetUpGameObject(CeilWall[0], WALL, 1080, 384, 64, 128, Vector4(0.5f, 0.5f, 0.5f, 0.f));
		CreateAndSetUpGameObject(CeilWall[1], WALL, 3856, 896, 64, 128, Vector4(0.5f, 0.5f, 0.5f, 0.f));
		CreateAndSetUpGameObject(CeilWall[2], WALL, 4480, 896, 64, 128, Vector4(0.5f, 0.5f, 0.5f, 0.f));
		CreateAndSetUpGameObject(CeilWall[3], WALL, 5872, 896, 64, 128, Vector4(0.5f, 0.5f, 0.5f, 0.f));
		CreateAndSetUpGameObject(CeilWall[4], WALL, 5872, 1856, 64, 128, Vector4(0.5f, 0.5f, 0.5f, 0.f));
		CreateAndSetUpGameObject(CeilWall[5], WALL, 3888, 1664, 64, 128, Vector4(0.5f, 0.5f, 0.5f, 0.f));
		CreateAndSetUpGameObject(CeilWall[6], WALL, 3312, 1664, 64, 128, Vector4(0.5f, 0.5f, 0.5f, 0.f));
		CreateAndSetUpGameObject(CeilWall[7], WALL, 2160, 1664, 64, 128, Vector4(0.5f, 0.5f, 0.5f, 0.f));
		CreateAndSetUpGameObject(CeilWall[8], WALL, 944, 1408, 64, 128, Vector4(0.5f, 0.5f, 0.5f, 0.f));
		CreateAndSetUpGameObject(CeilWall[9], WALL, 2032, 2560, 64, 128, Vector4(0.5f, 0.5f, 0.5f, 0.f));
		CreateAndSetUpGameObject(CeilWall[10], WALL, 2544, 2560, 64, 128, Vector4(0.5f, 0.5f, 0.5f, 0.f));
		CreateAndSetUpGameObject(CeilWall[11], WALL, 3056, 2560, 64, 128, Vector4(0.5f, 0.5f, 0.5f, 0.f));
		CreateAndSetUpGameObject(CeilWall[12], WALL, 3568, 2560, 64, 128, Vector4(0.5f, 0.5f, 0.5f, 0.f));
		CreateAndSetUpGameObject(CeilWall[13], WALL, 6336, 2560, 128, 128, Vector4(0.5f, 0.5f, 0.5f, 0.f));

		//--------------------------------------------------------
		//					파괴되는 벽 개체
		//--------------------------------------------------------
		const int BreakWallCount = 4;

		DestuctibleWall* BreakWall[BreakWallCount];

		for (size_t i = 0; i < BreakWallCount; i++)	BreakWall[i] = new DestuctibleWall();

		// 개체 생성
		CreateAndSetUpGameObject(BreakWall[0], WALL, 1080, 224, 64, 192, Vector4(0.5f, 0.5f, 0.5f, 0.f));
		CreateAndSetUpGameObject(BreakWall[1], WALL, 4608, 608, 192, 64, Vector4(0.5f, 0.5f, 0.5f, 0.f));
		CreateAndSetUpGameObject(BreakWall[2], WALL, 5872, 736, 64, 192, Vector4(0.5f, 0.5f, 0.5f, 0.f));
		CreateAndSetUpGameObject(BreakWall[3], WALL, 944, 1248, 64, 192, Vector4(0.5f, 0.5f, 0.5f, 0.f));

		//--------------------------------------------------------
		//					배리어 개체
		//--------------------------------------------------------
		const int EventBarrierCount = 3;

		Barrier* EventBarrier[EventBarrierCount];

		for (size_t i = 0; i < EventBarrierCount; i++)	EventBarrier[i] = new Barrier();

		// 개체 생성
		CreateAndSetUpGameObject(EventBarrier[0], WALL, 6176, 1792, 64, 256, Vector4(0.5f, 0.5f, 0.5f, 0.f));
		CreateAndSetUpGameObject(EventBarrier[1], WALL, 1312, 832, 64, 256, Vector4(0.5f, 0.5f, 0.5f, 0.f));
		CreateAndSetUpGameObject(EventBarrier[2], WALL, 6176, 2976, 64, 192, Vector4(0.5f, 0.5f, 0.5f, 0.f));

		//--------------------------------------------------------
		//				이벤트 스위치 개체
		//--------------------------------------------------------
		for (size_t i = 0; i < EventButtonCount; i++)	EventButton[i] = new EventSwitch();

		// 개체 생성
		CreateAndSetUpGameObject(EventButton[0], WALL, 4912, 224, 64, 64, Vector4(0.5f, 0.5f, 0.5f, 0.f));
		CreateAndSetUpGameObject(EventButton[1], WALL, 6304, 1792, 64, 64, Vector4(0.5f, 0.5f, 0.5f, 0.f));
		CreateAndSetUpGameObject(EventButton[2], WALL, 1472, 832, 64, 64, Vector4(0.5f, 0.5f, 0.5f, 0.f));
		CreateAndSetUpGameObject(EventButton[3], WALL, 432, 1696, 64, 64, Vector4(0.5f, 0.5f, 0.5f, 0.f));
		CreateAndSetUpGameObject(EventButton[4], WALL, 976, 2400, 64, 64, Vector4(0.5f, 0.5f, 0.5f, 0.f));
		CreateAndSetUpGameObject(EventButton[5], WALL, 4910, 2432, 64, 64, Vector4(0.5f, 0.5f, 0.5f, 0.f));
		CreateAndSetUpGameObject(EventButton[6], WALL, 6304, 2976, 64, 64, Vector4(0.5f, 0.5f, 0.5f, 0.f));

		//--------------------------------------------------------
		//					잠긴 문 개체
		//--------------------------------------------------------
		for (size_t i = 0; i < EventDoorCount; i++)	EventDoor[i] = new LockedDoor();

		EventDoor[0]->SetTag(1);
		EventDoor[1]->SetTag(1);
		EventDoor[2]->SetTag(2);

		// 개체 생성
		CreateAndSetUpGameObject(EventDoor[0], WALL, 4752, 1504, 64, 192, Vector4(0.5f, 0.5f, 0.5f, 0.f));
		CreateAndSetUpGameObject(EventDoor[1], WALL, 4752, 1792, 64, 256, Vector4(0.5f, 0.5f, 0.5f, 0.f));
		CreateAndSetUpGameObject(EventDoor[2], WALL, 6336, 2400, 128, 192, Vector4(0.5f, 0.5f, 0.5f, 0.f));

		//--------------------------------------------------------
		//					엘레베이터 개체
		//--------------------------------------------------------
		for (size_t i = 0; i < EventElevatorCount; i++)	EventElevator[i] = new Elevator();

		EventElevator[4]->SetDirection(evrDirection::HORIZONTAL);
		EventElevator[0]->SetTimer(2.5f);
		EventElevator[1]->SetTimer(2.0f);
		EventElevator[2]->SetTimer(2.0f);
		EventElevator[3]->SetTimer(3.0f);
		EventElevator[4]->SetTimer(12.565f);
		EventElevator[5]->SetTimer(3.0f);

		EventElevator[0]->SetTag(1);
		EventElevator[1]->SetTag(2);
		EventElevator[3]->SetTag(3);
		EventElevator[4]->SetTag(4);
		EventElevator[5]->SetTag(5);

		EventElevator[2]->SetActive(true);

		EventElevator[0]->SetRange(360);
		EventElevator[1]->SetRange(384);
		EventElevator[2]->SetRange(384);
		EventElevator[3]->SetRange(430);
		EventElevator[4]->SetRange(448);
		EventElevator[5]->SetRange(344);

		// 개체 생성
		CreateAndSetUpGameObject(EventElevator[0], WALL, 4608, 160, 192, 64, Vector4(0.5f, 0.5f, 0.5f, 0.f));
		CreateAndSetUpGameObject(EventElevator[1], WALL, 1186, 1184, 192, 64, Vector4(0.5f, 0.5f, 0.5f, 0.f));
		CreateAndSetUpGameObject(EventElevator[2], WALL, 752, 736, 192, 64, Vector4(0.5f, 0.5f, 0.5f, 0.f));
		CreateAndSetUpGameObject(EventElevator[3], WALL, 192, 1632, 256, 64, Vector4(0.5f, 0.5f, 0.5f, 0.f));
		CreateAndSetUpGameObject(EventElevator[4], WALL, 1312, 2256, 448, 96, Vector4(0.5f, 0.5f, 0.5f, 0.f));
		CreateAndSetUpGameObject(EventElevator[5], WALL, 4672, 2336, 256, 64, Vector4(0.5f, 0.5f, 0.5f, 0.f));


		//--------------------------------------------------------
		//					트리거
		//--------------------------------------------------------

		#pragma region Trigger
		Trigger* SceneTrigger = new Trigger();
		SceneTrigger->SetType(eTriggerType::SceneChanger);
		SceneTrigger->SetSceneName(L"Stage1_3");
		SceneTrigger->SetSceneClearImage2(clearImage);
		CreateAndSetUpGameObject(SceneTrigger, TRIGGER, 6336, 2400, 128, 192, Vector4(0.5f, 0.5f, 0.5f, 0.f));

		UINT enemyCount = 17;
		for (size_t i = 0; i < EnemyFallTriggerCount; i++)
		{
			EnemyFallTrigger[i] = new Trigger();
			EnemyFallTrigger[i]->SetType(eTriggerType::EnemyFall);
			EnemyFallTrigger[i]->SetEnemyObject(EnemyLabGuard[enemyCount++]);
			EnemyFallTrigger[i]->SetEnemyObject(EnemyLabGuard[enemyCount++]);
		}

		CreateAndSetUpGameObject(EnemyFallTrigger[0], TRIGGER, 1776, 2256, 64, 64, Vector4(0.2f, 0.2f, 0.2f, 1.0f));
		CreateAndSetUpGameObject(EnemyFallTrigger[1], TRIGGER, 2266.5, 2256, 64, 64, Vector4(0.2f, 0.2f, 0.2f, 1.0f));
		CreateAndSetUpGameObject(EnemyFallTrigger[2], TRIGGER, 2762.5, 2256, 64, 64, Vector4(0.2f, 0.2f, 0.2f, 1.0f));
		CreateAndSetUpGameObject(EnemyFallTrigger[3], TRIGGER, 3290.5, 2256, 64, 64, Vector4(0.2f, 0.2f, 0.2f, 1.0f));
		
		#pragma endregion

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
		CollisionManager::CollisionLayerCheck(LAYER::WALL, LAYER::TRIGGER, TRUE);
		CollisionManager::CollisionLayerCheck(LAYER::PLAYER, LAYER::TRIGGER, TRUE);
		#pragma endregion
	}

	void Stage1_2::Update()
	{
		Scene::Update();

		if (EventButton[0]->GetEventActive())	ActivateElevator(1);
		if (EventButton[1]->GetEventActive())	UnlockDoor(1);
		if (EventButton[2]->GetEventActive())	ActivateElevator(2);
		if (EventButton[3]->GetEventActive())	ActivateElevator(3);
		if (EventButton[4]->GetEventActive())	ActivateElevator(4);
		if (EventButton[5]->GetEventActive())	ActivateElevator(5);
		if (EventButton[6]->GetEventActive())	UnlockDoor(2);
	}

	void Stage1_2::LateUpdate()
	{
		Scene::LateUpdate();

		if (mPlayer->GetCurHP() <= 0.f
			|| Input::GetKeyState(KEY_CODE::L) == KEY_STATE::DOWN)
		{
			SceneManager::ReStartScene<Stage1_2>(GetName());
		}
	}

	void Stage1_2::Render()
	{
		Scene::Render();
	}

	void Stage1_2::UnlockDoor(int tag)
	{
		for (size_t i = 0; i < EventDoorCount; i++)
		{
			if (EventDoor[i]->GetTag() == tag)	EventDoor[i]->SetLocked(false);
		}
	}

	void Stage1_2::ActivateElevator(int tag)
	{
		for (size_t i = 0; i < EventElevatorCount; i++)
		{
			if (EventElevator[i]->GetTag() == tag)	EventElevator[i]->SetActive(true);
		}
	}

	void Stage1_2::Enter()
	{
		Camera::SetTarget(mPlayer);
	}

	void Stage1_2::Exit()
	{
	}

	// 작동 테스트
}
