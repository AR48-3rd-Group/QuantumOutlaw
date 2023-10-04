#include "qoItem.h"


namespace qo
{
	Item::Item()
	{
	}

	Item::~Item()
	{
	}

	void Item::Initialize()
	{
		GameObject::Initialize();
	}

	void Item::Update()
	{
		GameObject::Update();
	}

	void Item::LateUpdate()
	{
		GameObject::LateUpdate();
	}

	void Item::Render()
	{
		GameObject::Render();
	}

	void Item::OnCollisionEnter(Collider* other)
	{
	}

	void Item::OnCollisionStay(Collider* other)
	{
	}

	void Item::OnCollisionExit(Collider* other)
	{
	}
}