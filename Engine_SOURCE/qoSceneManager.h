#pragma once
#include "qoScene.h"

namespace qo
{
	class SceneManager
	{
	public:
		static void Initialize();
		static void Update();
		static void LateUpdate();
		static void Render();
		static void Release();

		template <typename T>
		static bool CreateScene(const std::wstring name)
		{
			std::map<std::wstring, Scene*>::iterator iter
				= mScenes.find(name);

			if (iter != mScenes.end())
				return false;

			T* scene = new T();
			mScenes.insert(std::make_pair(name, scene));
			scene->SetName(name);
			scene->Initialize();
			mActiveScene = scene;

			return true;
		}
		static Scene* LoadScene(const std::wstring name);

		static Scene* GetActiveScene() { return mActiveScene; }

		template <typename T>
		static void ReStartScene(const std::wstring name)
		{
			mActiveScene->Exit();

			std::map<std::wstring, Scene*>::iterator iter
				= mScenes.find(name);

			// ������ �޸� ����
			delete iter->second;
			iter->second = nullptr;

			// ���� ���� Scene���� �����Ѵ�
			mScenes.erase(iter);

			CreateScene<T>(name);

			mActiveScene->Enter();
		}

	private:
		static Scene* mActiveScene;
		static std::map<std::wstring, Scene*> mScenes;

		static bool mbRender;
	};
}
