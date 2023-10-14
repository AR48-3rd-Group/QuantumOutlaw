#include "qoScene.h"
#include "qoTransform.h"
#include "qoMeshRenderer.h"
#include "qoCollider.h"
#include "qoRigidbody.h"
#include "qoResourceManager.h"

namespace qo
{
	Scene::Scene()
	{
	}

	Scene::~Scene()
	{
	}

	void Scene::Initialize()
	{
		for (Layer& layer : mLayers)
		{
			layer.Initialize();
		}
	}

	void Scene::Update()
	{
		for (Layer& layer : mLayers)
		{
			layer.Update();
		}
	}

	void Scene::LateUpdate()
	{
		for (Layer& layer : mLayers)
		{
			layer.LateUpdate();
		}
	}

	void Scene::Render()
	{
		for (Layer& layer : mLayers)
		{
			layer.Render();
		}
	}

	void Scene::AddGameObject(GameObject* gameObject, UINT layerIndex)
	{
		mLayers[layerIndex].AddGameObject(gameObject);
	}

	void Scene::CreateAndSetUpGameObject(GameObject* object, LAYER objectLayer, float xPixels, float yPixels, float widthInPixels, float heightInPixels, const Vector4& color)
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
		case LAYER::ITEM:
			AddGameObject(object, LAYER::ITEM);
			break;
		case LAYER::ENEMY:
			AddGameObject(object, LAYER::ENEMY);
			break;
		case LAYER::TRIGGER:
			AddGameObject(object, LAYER::TRIGGER);
			break;
		}
	}
}