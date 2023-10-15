#pragma once

#include "qoGameObject.h"

namespace qo
{
	enum class eTriggerType
	{
		  SceneChanger
		, EnemyFall
		, None
	};

	class Trigger : public GameObject
	{
	public:
		Trigger();
		virtual ~Trigger();

		void Initialize() override;
		void Update() override;
		void LateUpdate() override;
		void Render() override;

		void OnCollisionEnter(class Collider* other) override;
		void OnCollisionStay(class Collider* other) override;
		void OnCollisionExit(class Collider* other) override;

		void SetSceneName(std::wstring scenename) { mSceneName = scenename; }
		void SetType(eTriggerType type) { mType = type; }

		void SetEnemyObject(GameObject* enemy) { mEnemies.push_back(enemy); }

		void SetSceneClearImage1(GameObject* SceneImage) { mSceneClearImage1 = SceneImage; }
		void SetSceneClearImage2(GameObject* SceneImage) { mSceneClearImage2 = SceneImage; }
		void SetSceneClearImage3(GameObject* SceneImage) { mSceneClearImage3 = SceneImage; }

	private:
		std::wstring mSceneName;
		eTriggerType mType;

		std::vector<GameObject*> mEnemies;

		// Scene Clear
		float mCheckTime;
		UINT mSceneImageIdx;
		bool mCheck;
		GameObject* mSceneClearImage1;
		GameObject* mSceneClearImage2;
		GameObject* mSceneClearImage3;
	};
}


