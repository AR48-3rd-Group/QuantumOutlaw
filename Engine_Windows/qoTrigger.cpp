#include "qoTrigger.h"
#include "qoCollider.h"
#include "qoRigidbody.h"
#include "qoPlayer.h"
#include "qoElevator.h"
#include "qoSceneManager.h"

namespace qo
{
	Trigger::Trigger()
		: mType(eTriggerType::None)
	{
	}

	Trigger::~Trigger()
	{
	}

	void Trigger::Initialize()
	{
		
	}

	void Trigger::Update()
	{
		GameObject::Update();

		// Dead Object Á¦¿Ü
		std::vector<GameObject*>::iterator iter = mEnemies.begin();

		for (; iter != mEnemies.end();)
		{
			if ((*iter)->GetGameObjectState() == GameObject::eState::Dead)
			{
				iter = mEnemies.erase(iter);
			}
			else
			{
				iter++;
			}
		}
	}

	void Trigger::LateUpdate()
	{
		GameObject::LateUpdate();
	}

	void Trigger::Render()
	{
		GameObject::Render();
	}

	void Trigger::OnCollisionEnter(Collider* other)
	{
		Player* player = dynamic_cast<Player*>(other->GetOwner());
		Elevator* elvator = dynamic_cast<Elevator*>(other->GetOwner());

		if (player == nullptr && elvator == nullptr)
			return;

		if(mType==eTriggerType::SceneChanger)
			SceneManager::LoadScene(mSceneName);
		else if (mType == eTriggerType::EnemyFall)
		{
			for (size_t i = 0; i < mEnemies.size(); i++)
			{
				if (mEnemies[i] != nullptr && mEnemies[i]->GetGameObjectState() != eState::Dead)
					mEnemies[i]->GetComponent<Rigidbody>()->SetActive(true);
			}
		}
	}

	void Trigger::OnCollisionStay(Collider* other)
	{
	}

	void Trigger::OnCollisionExit(Collider* other)
	{
	}
}