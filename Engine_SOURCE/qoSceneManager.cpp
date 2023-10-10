#include "qoSceneManager.h"

#include "qoResourceManager.h"

#include "qoGameObject.h"
#include "qoTransform.h"
#include "qoMeshRenderer.h"
#include "qoInput.h"
#include "qoCollider.h"

namespace qo
{
	Scene* SceneManager::mActiveScene = nullptr;
	std::map<std::wstring, Scene*> SceneManager::mScenes = {};
	bool SceneManager::mbRender = false;

	void SceneManager::Initialize()
	{
		//mActiveScene = new Scene();



		//{
		//	GameObject* object = new GameObject();
		//	Transform* tr = new Transform();
		//	tr->SetPosition(Vector3(-0.5f, -0.2f, 0.0f));
		//	object->AddComponent(tr);

		//	MeshRenderer* meshRenderer = new MeshRenderer();
		//	meshRenderer->SetMesh(ResourceManager::Find<Mesh>(L"TriangleMesh"));
		//	meshRenderer->SetShader(ResourceManager::Find<Shader>(L"TriangleShader"));
		//	object->AddComponent(meshRenderer);

		//	mActiveScene->AddGameObject(object, LAYER::NONE);
		//}
	}

	void SceneManager::Update()
	{
		mActiveScene->Update();
	}

	void SceneManager::LateUpdate()
	{
		mActiveScene->LateUpdate();
		
		if (Input::GetKeyState(KEY_CODE::P) == KEY_STATE::DOWN)
		{
			mbRender = !mbRender;
		}

		for (UINT layer = 1;layer < (UINT)LAYER::MAX;layer++)
		{
			std::vector<GameObject*>& GameObjects = mActiveScene->GetLayer(layer)->GetGameObjects();

			for (GameObject* obj : GameObjects)
			{
				if (obj->GetComponent<Collider>() == nullptr)
					continue;

				obj->GetComponent<Collider>()->SetRender(mbRender);
			}
		}
	}

	void SceneManager::Render()
	{
		mActiveScene->Render();
	}
	
	void SceneManager::Release()
	{
		for (auto iter : mScenes)
		{
			delete iter.second;
			iter.second = nullptr;
		}
	}

	Scene* SceneManager::LoadScene(const std::wstring name)
	{
		std::map<std::wstring, Scene*>::iterator iter
			= mScenes.find(name);

		if (iter == mScenes.end())
			return nullptr;
		mActiveScene->Exit();
		mActiveScene = iter->second;
		mActiveScene->Enter();
		return iter->second;
	}
}
