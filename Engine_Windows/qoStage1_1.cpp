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
#include "qoGunItem.h"
#include "qoHPUI.h"
#include "qoHPUIBackGround.h"
#include "qoHPUIScript.h"

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

		#pragma region Item
		GunItem* gunItem = new GunItem(eGunType::Superposition);
		CreateAndSetUpGameObject(gunItem, ITEM, 1200, 300, 100, 100, gunItem->GetColor());
		#pragma endregion

		#pragma region Map Layout
		// 바닥 개체
		Floor* StageFloor = new Floor();
		Floor* Ceiling_1 = new Floor();
		Floor* Ceiling_2 = new Floor();
		Floor* Ceiling_3 = new Floor();
		Floor* Ceiling_4 = new Floor();

		Transform* StageFloorTransform = StageFloor->AddComponent<Transform>();
		Transform* Ceiling_1_Transform = Ceiling_1->AddComponent<Transform>();
		Transform* Ceiling_2_Transform = Ceiling_2->AddComponent<Transform>();
		Transform* Ceiling_3_Transform = Ceiling_3->AddComponent<Transform>();
		Transform* Ceiling_4_Transform = Ceiling_4->AddComponent<Transform>();

		// 좌표(위치) 설정
		StageFloorTransform->SetPositionInPixels(3200, 128, 0);
		Ceiling_1_Transform->SetPositionInPixels(1760, 1256, 0);
		Ceiling_2_Transform->SetPositionInPixels(4960, 1612, 0);
		Ceiling_3_Transform->SetPositionInPixels(4256, 900, 0);
		Ceiling_4_Transform->SetPositionInPixels(5440, 964, 0);
		
		// 크기 설정
		StageFloorTransform->SetScaleInPixels(6400, 256, 0);
		Ceiling_1_Transform->SetScaleInPixels(3520, 840, 0);
		Ceiling_2_Transform->SetScaleInPixels(2880, 128, 0);
		Ceiling_3_Transform->SetScaleInPixels(448, 128, 0);
		Ceiling_4_Transform->SetScaleInPixels(1920, 256, 0);
		
		// 색상 설정
		StageFloorTransform->SetColor(Vector4(0.5f, 0.5f, 0.5f, 0.f));
		Ceiling_1_Transform->SetColor(Vector4(0.5f, 0.5f, 0.5f, 0.f));
		Ceiling_2_Transform->SetColor(Vector4(0.5f, 0.5f, 0.5f, 0.f));
		Ceiling_3_Transform->SetColor(Vector4(0.5f, 0.5f, 0.5f, 0.f));
		Ceiling_4_Transform->SetColor(Vector4(0.5f, 0.5f, 0.5f, 0.f));
		
		MeshRenderer* StageFloorMeshRenderer = StageFloor->AddComponent<MeshRenderer>();
		MeshRenderer* Ceiling_1_MeshRenderer = Ceiling_1->AddComponent<MeshRenderer>();
		MeshRenderer* Ceiling_2_MeshRenderer = Ceiling_2->AddComponent<MeshRenderer>();
		MeshRenderer* Ceiling_3_MeshRenderer = Ceiling_3->AddComponent<MeshRenderer>();
		MeshRenderer* Ceiling_4_MeshRenderer = Ceiling_4->AddComponent<MeshRenderer>();

		StageFloorMeshRenderer->SetMesh(ResourceManager::Find<Mesh>(L"RectangleMesh"));
		Ceiling_1_MeshRenderer->SetMesh(ResourceManager::Find<Mesh>(L"RectangleMesh"));
		Ceiling_2_MeshRenderer->SetMesh(ResourceManager::Find<Mesh>(L"RectangleMesh"));
		Ceiling_3_MeshRenderer->SetMesh(ResourceManager::Find<Mesh>(L"RectangleMesh"));
		Ceiling_4_MeshRenderer->SetMesh(ResourceManager::Find<Mesh>(L"RectangleMesh"));

		StageFloorMeshRenderer->SetShader(ResourceManager::Find<Shader>(L"ColorTestShader"));
		Ceiling_1_MeshRenderer->SetShader(ResourceManager::Find<Shader>(L"ColorTestShader"));
		Ceiling_2_MeshRenderer->SetShader(ResourceManager::Find<Shader>(L"ColorTestShader"));
		Ceiling_3_MeshRenderer->SetShader(ResourceManager::Find<Shader>(L"ColorTestShader"));
		Ceiling_4_MeshRenderer->SetShader(ResourceManager::Find<Shader>(L"ColorTestShader"));

		Collider* StageFloorCollider = StageFloor->AddComponent<Collider>();
		Collider* Ceiling_1_Collider = Ceiling_1->AddComponent<Collider>();
		Collider* Ceiling_2_Collider = Ceiling_2->AddComponent<Collider>();
		Collider* Ceiling_3_Collider = Ceiling_3->AddComponent<Collider>();
		Collider* Ceiling_4_Collider = Ceiling_4->AddComponent<Collider>();

		StageFloorCollider->SetScale(StageFloorTransform->GetScale());
		Ceiling_1_Collider->SetScale(Ceiling_1_Transform->GetScale());
		Ceiling_2_Collider->SetScale(Ceiling_2_Transform->GetScale());
		Ceiling_3_Collider->SetScale(Ceiling_3_Transform->GetScale());
		Ceiling_4_Collider->SetScale(Ceiling_4_Transform->GetScale());

		AddGameObject(StageFloor, LAYER::FLOOR);
		AddGameObject(Ceiling_1, LAYER::FLOOR);
		AddGameObject(Ceiling_2, LAYER::FLOOR);
		AddGameObject(Ceiling_3, LAYER::FLOOR);
		AddGameObject(Ceiling_4, LAYER::FLOOR);

		// 벽 개체
		Wall* StartWall = new Wall();
		Wall* Wall_1 = new Wall();
		Wall* Wall_2 = new Wall();
		Wall* Wall_3 = new Wall();
		Wall* SwitchWall = new Wall();
		Wall* StepBlock = new Wall();

		Transform* StartWallTransform = StartWall->AddComponent<Transform>();
		Transform* Wall_1_Transform = Wall_1->AddComponent<Transform>();
		Transform* Wall_2_Transform = Wall_2->AddComponent<Transform>();
		Transform* Wall_3_Transform = Wall_3->AddComponent<Transform>();
		Transform* SwitchWallTransform = SwitchWall->AddComponent<Transform>();
		Transform* StepBlockTransform = StepBlock->AddComponent<Transform>();

		StartWallTransform->SetPositionInPixels(32, 546, 0);
		Wall_1_Transform->SetPositionInPixels(1664, 706, 0);
		Wall_2_Transform->SetPositionInPixels(3456, 706, 0);
		Wall_3_Transform->SetPositionInPixels(6336, 706, 0);
		SwitchWallTransform->SetPositionInPixels(6368, 1320, 0);
		StepBlockTransform->SetPositionInPixels(3584, 640, 0);

		StartWallTransform->SetScaleInPixels(64, 580, 0);
		Wall_1_Transform->SetScaleInPixels(128, 260, 0);
		Wall_2_Transform->SetScaleInPixels(128, 260, 0);
		Wall_3_Transform->SetScaleInPixels(128, 260, 0);
		SwitchWallTransform->SetScaleInPixels(64, 456, 0);
		StepBlockTransform->SetScaleInPixels(128, 128, 0);

		StartWallTransform->SetColor(Vector4(0.5f, 0.5f, 0.5f, 0.f));
		Wall_1_Transform->SetColor(Vector4(0.5f, 0.5f, 0.5f, 0.f));
		Wall_2_Transform->SetColor(Vector4(0.5f, 0.5f, 0.5f, 0.f));
		Wall_3_Transform->SetColor(Vector4(0.5f, 0.5f, 0.5f, 0.f));
		SwitchWallTransform->SetColor(Vector4(0.5f, 0.5f, 0.5f, 0.f));
		StepBlockTransform->SetColor(Vector4(0.5f, 0.5f, 0.5f, 0.f));

		MeshRenderer* StartWallMeshRenderer = StartWall->AddComponent<MeshRenderer>();
		MeshRenderer* Wall_1_MeshRenderer = Wall_1->AddComponent<MeshRenderer>();
		MeshRenderer* Wall_2_MeshRenderer = Wall_2->AddComponent<MeshRenderer>();
		MeshRenderer* Wall_3_MeshRenderer = Wall_3->AddComponent<MeshRenderer>();
		MeshRenderer* SwitchWallMeshRenderer = SwitchWall->AddComponent<MeshRenderer>();
		MeshRenderer* StepBlockMeshRenderer = StepBlock->AddComponent<MeshRenderer>();

		StartWallMeshRenderer->SetMesh(ResourceManager::Find<Mesh>(L"RectangleMesh"));
		Wall_1_MeshRenderer->SetMesh(ResourceManager::Find<Mesh>(L"RectangleMesh"));
		Wall_2_MeshRenderer->SetMesh(ResourceManager::Find<Mesh>(L"RectangleMesh"));
		Wall_3_MeshRenderer->SetMesh(ResourceManager::Find<Mesh>(L"RectangleMesh"));
		SwitchWallMeshRenderer->SetMesh(ResourceManager::Find<Mesh>(L"RectangleMesh"));
		StepBlockMeshRenderer->SetMesh(ResourceManager::Find<Mesh>(L"RectangleMesh"));

		StartWallMeshRenderer->SetShader(ResourceManager::Find<Shader>(L"ColorTestShader"));
		Wall_1_MeshRenderer->SetShader(ResourceManager::Find<Shader>(L"ColorTestShader"));
		Wall_2_MeshRenderer->SetShader(ResourceManager::Find<Shader>(L"ColorTestShader"));
		Wall_3_MeshRenderer->SetShader(ResourceManager::Find<Shader>(L"ColorTestShader"));
		SwitchWallMeshRenderer->SetShader(ResourceManager::Find<Shader>(L"ColorTestShader"));
		StepBlockMeshRenderer->SetShader(ResourceManager::Find<Shader>(L"ColorTestShader"));

		Collider* StartWallCollider = StartWall->AddComponent<Collider>();
		Collider* Wall_1_Collider = Wall_1->AddComponent<Collider>();
		Collider* Wall_2_Collider = Wall_2->AddComponent<Collider>();
		Collider* Wall_3_Collider = Wall_3->AddComponent<Collider>();
		Collider* SwitchWallCollider = SwitchWall->AddComponent<Collider>();
		Collider* StepBlockCollider = StepBlock->AddComponent<Collider>();

		StartWallCollider->SetScale(StartWallTransform->GetScale());
		Wall_1_Collider->SetScale(Wall_1_Transform->GetScale());
		Wall_2_Collider->SetScale(Wall_2_Transform->GetScale());
		Wall_3_Collider->SetScale(Wall_3_Transform->GetScale());
		SwitchWallCollider->SetScale(SwitchWallTransform->GetScale());
		StepBlockCollider->SetScale(StepBlockTransform->GetScale());

		AddGameObject(StartWall, LAYER::WALL);
		AddGameObject(Wall_1, LAYER::WALL);
		AddGameObject(Wall_2, LAYER::WALL);
		AddGameObject(Wall_3, LAYER::WALL);
		AddGameObject(SwitchWall, LAYER::WALL);
		AddGameObject(StepBlock, LAYER::WALL);

		// 파괴되는 벽 개체
		DestuctibleWall* DWall = new DestuctibleWall();

		Transform* DWallTransform = DWall->AddComponent<Transform>();
		DWallTransform->SetPositionInPixels(1664, 416, 0);
		DWallTransform->SetScaleInPixels(128, 320, 0);
		DWallTransform->SetColor(Vector4(0.5f, 0.5f, 0.5f, 0.f));

		MeshRenderer* DWallMeshRenderer = DWall->AddComponent<MeshRenderer>();
		DWallMeshRenderer->SetMesh(ResourceManager::Find<Mesh>(L"RectangleMesh"));
		DWallMeshRenderer->SetShader(ResourceManager::Find<Shader>(L"ColorTestShader"));

		Collider* DWallCollider = DWall->AddComponent<Collider>();
		DWallCollider->SetScale(DWallTransform->GetScale());

		AddGameObject(DWall, LAYER::WALL);

		// 배리어 개체
		Barrier* SwitchBarrier = new Barrier();

		Transform* SwitchBarrierTransform = SwitchBarrier->AddComponent<Transform>();
		SwitchBarrierTransform->SetPositionInPixels(5984, 1320, 0);
		SwitchBarrierTransform->SetScaleInPixels(96, 456, 0);
		SwitchBarrierTransform->SetColor(Vector4(0.5f, 0.5f, 0.5f, 0.f));

		MeshRenderer* SwitchBarrierMeshRenderer = SwitchBarrier->AddComponent<MeshRenderer>();
		SwitchBarrierMeshRenderer->SetMesh(ResourceManager::Find<Mesh>(L"RectangleMesh"));
		SwitchBarrierMeshRenderer->SetShader(ResourceManager::Find<Shader>(L"ColorTestShader"));

		Collider* SwitchBarrierCollider = SwitchBarrier->AddComponent<Collider>();
		SwitchBarrierCollider->SetScale(SwitchBarrierTransform->GetScale());

		AddGameObject(SwitchBarrier, LAYER::WALL);

		// 잠긴 문 스위치 개체
		OpenSwitch = new DoorSwitch();

		Transform* OpenSwitchTransform = OpenSwitch->AddComponent<Transform>();
		OpenSwitchTransform->SetPositionInPixels(6336, 1320, 0);
		OpenSwitchTransform->SetScaleInPixels(64, 128, 0);
		OpenSwitchTransform->SetColor(Vector4(0.5f, 0.5f, 0.5f, 0.f));

		MeshRenderer* OpenSwitchMeshRenderer = OpenSwitch->AddComponent<MeshRenderer>();
		OpenSwitchMeshRenderer->SetMesh(ResourceManager::Find<Mesh>(L"RectangleMesh"));
		OpenSwitchMeshRenderer->SetShader(ResourceManager::Find<Shader>(L"ColorTestShader"));

		Collider* OpenSwitchCollider = OpenSwitch->AddComponent<Collider>();
		OpenSwitchCollider->SetScale(OpenSwitchTransform->GetScale());

		AddGameObject(OpenSwitch, LAYER::WALL);

		// 잠긴 문 개체
		Goal = new LockedDoor();
		Goal->SetTag(1);

		Transform* GoalTransform = Goal->AddComponent<Transform>();
		GoalTransform->SetPositionInPixels(6336, 416, 0);
		GoalTransform->SetScaleInPixels(128, 320, 0);
		GoalTransform->SetColor(Vector4(0.5f, 0.5f, 0.5f, 0.f));

		MeshRenderer* GoalMeshRenderer = Goal->AddComponent<MeshRenderer>();
		GoalMeshRenderer->SetMesh(ResourceManager::Find<Mesh>(L"RectangleMesh"));
		GoalMeshRenderer->SetShader(ResourceManager::Find<Shader>(L"ColorTestShader"));

		Collider* GoalCollider = Goal->AddComponent<Collider>();
		GoalCollider->SetScale(GoalTransform->GetScale());

		AddGameObject(Goal, LAYER::WALL);
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
		#pragma endregion
	}

	void Stage1_1::Update()
	{
		Scene::Update();

		if (OpenSwitch->GetSwitch())
		{
			Goal->SetLocked(false);
		}
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
	}

	void Stage1_1::Enter()
	{
		Camera::SetTarget(mPlayer);
	}

	void Stage1_1::Exit()
	{
	}

}
