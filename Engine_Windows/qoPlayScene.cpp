#include "qoPlayScene.h"
#include "qoResourceManager.h"

#include "qoGameObject.h"
#include "qoTransform.h"
#include "qoMeshRenderer.h"
#include "qoPlayerScript.h"
#include "qoPlayer.h"

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
		Transform* tr = player->AddComponent<Transform>();
		tr->SetPosition(Vector3(0.0f, 0.0f, 0.0f));
		tr->SetScale(Vector3(0.3f, 0.3f, 0.3f));

		MeshRenderer* meshRenderer = player->AddComponent<MeshRenderer>();
		meshRenderer->SetMesh(ResourceManager::Find<Mesh>(L"RectangleMesh"));
		meshRenderer->SetShader(ResourceManager::Find<Shader>(L"TriangleShader"));

		player->AddComponent<PlayerScript>();

		// ÃÑ ÇÏ³ª »ý¼º
		player->AddGun();

		player->Initialize();

		AddGameObject(player, LAYER::NONE);

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
