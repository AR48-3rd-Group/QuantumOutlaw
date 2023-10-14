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
			for (GameObject* enemy : mEnemies)
			{
				if(enemy!=nullptr)
					enemy->GetComponent<Rigidbody>()->SetActive(true);
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