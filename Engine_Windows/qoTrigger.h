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

	private:
		std::wstring mSceneName;
		eTriggerType mType;

		std::vector<GameObject*> mEnemies;
	};
}


