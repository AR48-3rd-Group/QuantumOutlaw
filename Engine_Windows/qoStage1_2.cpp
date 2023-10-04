#include "qoStage1_2.h"
#include "qoResourceManager.h"
#include "qoCollisionManager.h"

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
	Stage1_2::Stage1_2()
	{
	}

	Stage1_2::~Stage1_2()
	{
	}

	void Stage1_2::Initialize()
	{
		#pragma region Player
		Player* player = new Player();
		Transform* PlayerTransform = player->AddComponent<Transform>();
		PlayerTransform->SetPositionInPixels(800, 384, 0);
		PlayerTransform->SetScaleInPixels(96, 192, 0);
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
		//--------------------------------------------------------
		//						바닥 개체
		//--------------------------------------------------------
		const int FloorCount_1 = 3;
		const int FloorCount_2 = 3;
		const int FloorCount_3 = 4;
		const int CeilingCount = 2;
		const int StepBlockCount = 3;

		Floor* StageFloor = new Floor();
		Floor* ElevatorLRDiagonal = new Floor();
		Floor* Floor_1[FloorCount_1];
		Floor* Floor_2[FloorCount_2];
		Floor* Floor_3[FloorCount_3];
		Floor* Ceiling[CeilingCount];
		Floor* StepBlock[StepBlockCount];

		for (int i = 0; i < FloorCount_1; i++)
			Floor_1[i] = new Floor();
		for (int i = 0; i < FloorCount_2; i++)
			Floor_2[i] = new Floor();
		for (int i = 0; i < FloorCount_3; i++)
			Floor_3[i] = new Floor();
		for (int i = 0; i < CeilingCount; i++)
			Ceiling[i] = new Floor();
		for (int i = 0; i < StepBlockCount; i++)
			StepBlock[i] = new Floor();

		// 개체 생성
		CreateAndSetUpGameObject(StageFloor, FLOOR, 3200, 128, 6400, 256, Vector4(0.5f, 0.5f, 0.5f, 0.f));
		CreateAndSetUpGameObject(ElevatorLRDiagonal, FLOOR, 888, 2516, 368, 128, Vector4(0.5f, 0.5f, 0.5f, 0.f));
		CreateAndSetUpGameObject(Floor_1[0], FLOOR, 1368, 824, 2736, 256, Vector4(0.5f, 0.5f, 0.5f, 0.f));
		CreateAndSetUpGameObject(Floor_1[1], FLOOR, 934, 1334, 1232, 128, Vector4(0.5f, 0.5f, 0.5f, 0.f));
		CreateAndSetUpGameObject(Floor_1[2], FLOOR, 2926, 1662, 1376, 128, Vector4(0.5f, 0.5f, 0.5f, 0.f));
		CreateAndSetUpGameObject(Floor_2[0], FLOOR, 1138, 2070, 2020, 128, Vector4(0.5f, 0.5f, 0.5f, 0.f));
		CreateAndSetUpGameObject(Floor_2[1], FLOOR, 3840, 2412, 2656, 128, Vector4(0.5f, 0.5f, 0.5f, 0.f));
		CreateAndSetUpGameObject(Floor_2[2], FLOOR, 3112, 3028, 1488, 128, Vector4(0.5f, 0.5f, 0.5f, 0.f));
		CreateAndSetUpGameObject(Floor_3[0], FLOOR, 4240, 824, 768, 256, Vector4(0.5f, 0.5f, 0.5f, 0.f));
		CreateAndSetUpGameObject(Floor_3[1], FLOOR, 6016, 824, 768, 256, Vector4(0.5f, 0.5f, 0.5f, 0.f));
		CreateAndSetUpGameObject(Floor_3[2], FLOOR, 4848, 1396, 1472, 128, Vector4(0.5f, 0.5f, 0.5f, 0.f));
		CreateAndSetUpGameObject(Floor_3[3], FLOOR, 5600, 1904, 1344, 128, Vector4(0.5f, 0.5f, 0.5f, 0.f));
		CreateAndSetUpGameObject(Ceiling[0], FLOOR, 1992, 3536, 3728, 128, Vector4(0.5f, 0.5f, 0.5f, 0.f));
		CreateAndSetUpGameObject(Ceiling[1], FLOOR, 5192, 3536, 2160, 128, Vector4(0.5f, 0.5f, 0.5f, 0.f));
		CreateAndSetUpGameObject(StepBlock[0], FLOOR, 6144, 1206, 256, 128, Vector4(0.5f, 0.5f, 0.5f, 0.f));
		CreateAndSetUpGameObject(StepBlock[1], FLOOR, 4240, 1714, 256, 128, Vector4(0.5f, 0.5f, 0.5f, 0.f));
		CreateAndSetUpGameObject(StepBlock[2], FLOOR, 6144, 2220, 256, 128, Vector4(0.5f, 0.5f, 0.5f, 0.f));

		//--------------------------------------------------------
		//						벽 개체
		//--------------------------------------------------------
		const int StartWallCount = 3;
		const int WallCount = 4;
		const int DoorWallCount = 3;

		Wall* StartWall[StartWallCount];
		Wall* wall[WallCount];
		Wall* DoorWall[DoorWallCount];

		for (int i = 0; i < StartWallCount; i++)
			StartWall[i] = new Wall();
		for (int i = 0; i < WallCount; i++)
			wall[i] = new Wall();
		for (int i = 0; i < DoorWallCount; i++)
			DoorWall[i] = new Wall();

		// 개체 생성
		CreateAndSetUpGameObject(StartWall[0], WALL, 64, 476, 128, 440, Vector4(0.5f, 0.5f, 0.5f, 0.f));
		CreateAndSetUpGameObject(StartWall[1], WALL, 1536, 636, 128, 120, Vector4(0.5f, 0.5f, 0.5f, 0.f));
		CreateAndSetUpGameObject(StartWall[2], WALL, 2272, 636, 128, 120, Vector4(0.5f, 0.5f, 0.5f, 0.f));
		CreateAndSetUpGameObject(wall[0], WALL, 64, 2276, 128, 2648, Vector4(0.5f, 0.5f, 0.5f, 0.f));
		CreateAndSetUpGameObject(wall[1], WALL, 3984, 3282, 256, 636, Vector4(0.5f, 0.5f, 0.5f, 0.f));
		CreateAndSetUpGameObject(wall[2], WALL, 3984, 1650, 256, 1396, Vector4(0.5f, 0.5f, 0.5f, 0.f));
		CreateAndSetUpGameObject(wall[3], WALL, 6336, 2276, 128, 2648, Vector4(0.5f, 0.5f, 0.5f, 0.f));
		CreateAndSetUpGameObject(DoorWall[0], WALL, 3920, 636, 128, 120, Vector4(0.5f, 0.5f, 0.5f, 0.f));
		CreateAndSetUpGameObject(DoorWall[1], WALL, 6336, 636, 128, 120, Vector4(0.5f, 0.5f, 0.5f, 0.f));
		CreateAndSetUpGameObject(DoorWall[2], WALL, 4048, 2880, 128, 168, Vector4(0.5f, 0.5f, 0.5f, 0.f));

		//--------------------------------------------------------
		//					파괴되는 벽 개체
		//--------------------------------------------------------
		const int BreakableWallCount = 2;

		DestuctibleWall* BreakableWall[BreakableWallCount];

		for (int i = 0; i < BreakableWallCount; i++)
			BreakableWall[i] = new DestuctibleWall();

		// 개체 생성
		CreateAndSetUpGameObject(BreakableWall[0], WALL, 1536, 416, 128, 320, Vector4(0.5f, 0.5f, 0.5f, 0.f));
		CreateAndSetUpGameObject(BreakableWall[1], WALL, 2272, 416, 128, 320, Vector4(0.5f, 0.5f, 0.5f, 0.f));

		//--------------------------------------------------------
		//					배리어 개체
		//--------------------------------------------------------
		const int BarrierCount = 2;

		Barrier* barrier[BarrierCount];

		for (int i = 0; i < BarrierCount; i++)
			barrier[i] = new Barrier();

		// 개체 생성
		CreateAndSetUpGameObject(barrier[0], WALL, 4368, 1142, 96, 380, Vector4(0.5f, 0.5f, 0.5f, 0.f));
		CreateAndSetUpGameObject(barrier[1], WALL, 3632, 3282, 96, 380, Vector4(0.5f, 0.5f, 0.5f, 0.f));

		//--------------------------------------------------------
		//					스위치 개체
		//--------------------------------------------------------
		for (int i = 0; i < BarrierCount; i++)
			EventSwitch[i] = new DoorSwitch();

		// 개체 생성
		CreateAndSetUpGameObject(EventSwitch[0], WALL, 4144, 1142, 64, 128, Vector4(0.5f, 0.5f, 0.5f, 0.f));
		CreateAndSetUpGameObject(EventSwitch[1], WALL, 3824, 3282, 64, 128, Vector4(0.5f, 0.5f, 0.5f, 0.f));

		//--------------------------------------------------------
		//					잠긴 문 개체
		//--------------------------------------------------------
		EventTrap = new LockedDoor();

		for (int i = 0; i < EventDoorCount; i++)
			EventDoor[i] = new LockedDoor();

		EventTrap->SetTag(2);
		EventDoor[0]->SetTag(2);
		EventDoor[1]->SetTag(2);
		EventDoor[2]->SetTag(1);

		// 개체 생성
		CreateAndSetUpGameObject(EventTrap, WALL, 5128, 824, 1008, 256, Vector4(0.5f, 0.5f, 0.5f, 0.f));
		CreateAndSetUpGameObject(EventDoor[0], WALL, 3920, 416, 128, 320, Vector4(0.5f, 0.5f, 0.5f, 0.f));
		CreateAndSetUpGameObject(EventDoor[1], WALL, 6336, 416, 128, 320, Vector4(0.5f, 0.5f, 0.5f, 0.f));
		CreateAndSetUpGameObject(EventDoor[2], WALL, 4048, 2636, 128, 320, Vector4(0.5f, 0.5f, 0.5f, 0.f));

		#pragma endregion

		#pragma region Managers
		CollisionManager::CollisionLayerCheck(LAYER::PLAYER, LAYER::FLOOR, TRUE);
		CollisionManager::CollisionLayerCheck(LAYER::PLAYER, LAYER::WALL, TRUE);
		CollisionManager::CollisionLayerCheck(LAYER::BULLET, LAYER::WALL, TRUE);
		#pragma endregion
	}

	void Stage1_2::Update()
	{
		Scene::Update();

		if (EventSwitch[0]->GetSwitch())	UnlockDoor(2);
		if (EventSwitch[1]->GetSwitch())	UnlockDoor(1);
	}

	void Stage1_2::LateUpdate()
	{
		Scene::LateUpdate();
	}

	void Stage1_2::Render()
	{
		Scene::Render();
	}

	void Stage1_2::UnlockDoor(int tag)
	{
		if (EventTrap->GetTag() == tag)			EventTrap->SetLocked(false);

		for (int i = 0; i < EventDoorCount; i++)
		{
			if (EventDoor[i]->GetTag() == tag)	EventDoor[i]->SetLocked(false);
		}

	}

	void Stage1_2::CreateAndSetUpGameObject(GameObject* object, LAYER objectLayer, float xPixels, float yPixels, float widthInPixels, float heightInPixels, const Vector4& color)
	{
		Transform* objectTransform = object->AddComponent<Transform>();
		MeshRenderer* objectMeshRenderer = object->AddComponent<MeshRenderer>();
		Collider* objectCollider = object->AddComponent<Collider>();

		objectTransform->SetPositionInPixels(xPixels, yPixels, 0);
		objectTransform->SetScaleInPixels(widthInPixels, heightInPixels, 0);
		objectTransform->SetColor(color);

		objectMeshRenderer->SetMesh(ResourceManager::Find<Mesh>(L"RectangleMesh"));
		objectMeshRenderer->SetShader(ResourceManager::Find<Shader>(L"ColorTestShader"));

		objectCollider->SetScale(objectTransform->GetScale());

		switch (objectLayer) {
		case LAYER::FLOOR:
			AddGameObject(object, LAYER::FLOOR);
			break;
		case LAYER::WALL:
			AddGameObject(object, LAYER::WALL);
			break;
		}
	}
}
