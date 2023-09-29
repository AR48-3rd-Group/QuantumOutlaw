#include "qoLayer.h"

namespace qo
{
	Layer::Layer()
	{
	}
	Layer::~Layer()
	{
		for (GameObject* gameObject : mGameObjects)
		{
			delete gameObject;
			gameObject = nullptr;
		}
	}

	void Layer::Initialize()
	{
		for (size_t i = 0; i < mGameObjects.size(); i++)
		{
			mGameObjects[i]->Initialize();
		}
	}

	void Layer::Update()
	{
		for (size_t i = 0; i < mGameObjects.size(); i++)
		{
			mGameObjects[i]->Update();
		}
	}

	void Layer::LateUpdate()
	{
		for (size_t i = 0; i < mGameObjects.size(); i++)
		{
			mGameObjects[i]->LateUpdate();
		}

		std::vector<GameObject*>::iterator iter = mGameObjects.begin();

		for (;iter != mGameObjects.end();)
		{
			if ((*iter)->GetGameObjectState() == GameObject::eState::Dead)
			{
				GameObject* obj = *iter;
				iter = mGameObjects.erase(iter);
				delete obj;
				obj = nullptr;
			}
			else
			{
				iter++;
			}
		}
	}

	void Layer::Render()
	{
		for (size_t i = 0; i < mGameObjects.size(); i++)
		{
			mGameObjects[i]->Render();
		}
	}

	void Layer::AddGameObject(GameObject* gameObject)
	{
		mGameObjects.push_back(gameObject);
	}
}