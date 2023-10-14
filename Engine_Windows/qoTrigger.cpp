#include "qoTrigger.h"
#include "qoCollider.h"
#include "qoPlayer.h"
#include "qoElevator.h"
#include "qoSceneManager.h"

namespace qo
{
	Trigger::Trigger()
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
		

		if (player == nullptr)
			return;

		SceneManager::LoadScene(mSceneName);
	}

	void Trigger::OnCollisionStay(Collider* other)
	{
	}

	void Trigger::OnCollisionExit(Collider* other)
	{
	}
}