#include "qoStage1_3.h"
#include "qoResourceManager.h"
#include "qoCollisionManager.h"
#include "ArchitectureInclude.h"
#include "qoApplication.h"

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

#include "qoInput.h"
#include "qoSceneManager.h"

extern qo::Application application;

namespace qo
{
	Stage1_3::Stage1_3()
	{
	}

	Stage1_3::~Stage1_3()
	{
	}

	void Stage1_3::Initialize()
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

		// ÃÑ »ý¼º
		mPlayer->AddGun(eGunType::Superposition);
		mPlayer->ChangeActiveGun(eGunType::Superposition);

		mPlayer->Initialize();

		AddGameObject(mPlayer, LAYER::PLAYER);
		Camera::SetTarget(mPlayer);
		#pragma endregion

		#pragma region Image
		GameObject* ChamjalImage = new GameObject();
		Transform* ChamjalTransform = ChamjalImage->AddComponent<Transform>();
		ChamjalTransform->SetPositionInPixels(application.GetWidth() / 2.f, application.GetHeight() / 2.f + 60 , 0);
		ChamjalTransform->SetScaleInPixels(application.GetWidth(), application.GetHeight() * 0.9f, 0);

		MeshRenderer* ChamjalRenderer = ChamjalImage->AddComponent<MeshRenderer>();
		ChamjalRenderer->SetMesh(ResourceManager::Find<Mesh>(L"ChamjalMesh"));
		ChamjalRenderer->SetShader(ResourceManager::Find<Shader>(L"ChamjalShader"));

		ChamjalImage->GetComponent<Transform>()->SetAffectedCamera(false);
		AddGameObject(ChamjalImage, LAYER::BACKGROUND);
		#pragma endregion

		#pragma region Floor
		Floor* floor = new Floor();
		CreateAndSetUpGameObject(floor, FLOOR, 3200, 64, 6400, 128, Vector4(0.5f, 0.5f, 0.5f, 0.f));
		#pragma endregion

		#pragma region Managers
		CollisionManager::CollisionLayerCheck(LAYER::PLAYER, LAYER::FLOOR, TRUE);
		#pragma endregion
	}

	void Stage1_3::Update()
	{
		Scene::Update();
	}

	void Stage1_3::LateUpdate()
	{
		Scene::LateUpdate();

		if (mPlayer->GetCurHP() <= 0.f
			|| Input::GetKeyState(KEY_CODE::L) == KEY_STATE::DOWN)
		{
			SceneManager::ReStartScene<Stage1_3>(GetName());
		}
	}

	void Stage1_3::Render()
	{
		Scene::Render();
	}

	void Stage1_3::Enter()
	{
		Camera::SetTarget(mPlayer);
	}

	void Stage1_3::Exit()
	{
	}

}