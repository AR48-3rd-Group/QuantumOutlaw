#include "qoTrigger.h"
#include "qoCollider.h"
#include "qoRigidbody.h"
#include "qoPlayer.h"
#include "qoElevator.h"
#include "qoSceneManager.h"
#include "qoTime.h"
#include "qoTransform.h"

namespace qo
{
	Trigger::Trigger()
		: mType(eTriggerType::None)
		, mSceneClearImage1(nullptr)
		, mSceneClearImage2(nullptr)
		, mSceneClearImage3(nullptr)
		, mSceneImageIdx(0)
		, mCheckTime(0.f)
		, mCheck(false)
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

		if (mSceneImageIdx == 1)
		{
			if (mCheckTime >= 1.5f && !mCheck)
			{
				SceneManager::LoadScene(mSceneName);
				mCheck = false;
			}

			Vector3 pos = mSceneClearImage1->GetComponent<Transform>()->GetPosition();
			if (pos.y<=0.5f)
			{
				pos.y += Time::DeltaTime() * 10.f;
				mSceneClearImage1->GetComponent<Transform>()->SetPosition(pos);
			}
			else
			{
				mCheckTime += Time::DeltaTime();
			}
		}
		else if (mSceneImageIdx == 2)
		{
			if (mCheckTime >= 1.5f && !mCheck)
			{
				SceneManager::LoadScene(mSceneName);
				mCheck = false;
			}

			Vector3 pos = mSceneClearImage2->GetComponent<Transform>()->GetPosition();
			if (pos.y <= 0.5f)
			{
				pos.y += Time::DeltaTime() * 10.f;
				mSceneClearImage2->GetComponent<Transform>()->SetPosition(pos);
			}
			else
			{
				mCheckTime += Time::DeltaTime();
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

		if (mType == eTriggerType::SceneChanger)
		{
			if (mSceneName == L"Stage1_2")
			{
				mSceneImageIdx = 1;
			}
			else if (mSceneName == L"Stage1_3")
			{
				mSceneImageIdx = 2;
			}
		}
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