#include "qoGunItem.h"
#include "qoPlayer.h"
#include "qoCollider.h"

namespace qo
{
	GunItem::GunItem(eGunType type)
		: mGunType(type)
		, mColor(Vector4::Zero)
	{
		if (mGunType == eGunType::Superposition)
		{
			mColor = Vector4(1.0f, 0.f, 0.f, 0.f);
		}
		else if (mGunType == eGunType::Entanglement)
		{
			mColor = Vector4(0.f, 1.f, 0.f, 0.f);
		}
		else if (mGunType == eGunType::Teleportation)
		{
			mColor = Vector4(0.f, 0.f, 1.f, 0.f);
		}
	}

	GunItem::~GunItem()
	{
	}

	void GunItem::Initialize()
	{
		Item::Initialize();
	}

	void GunItem::Update()
	{
		Item::Update();
	}

	void GunItem::LateUpdate()
	{
		Item::LateUpdate();
	}

	void GunItem::Render()
	{
		Item::Render();
	}

	void GunItem::OnCollisionEnter(Collider* other)
	{
		Player* player = dynamic_cast<Player*>(other->GetOwner());

		if (player == nullptr)
			return;

		Destroy(this);
		player->AddGun(mGunType);
	}

	void GunItem::OnCollisionStay(Collider* other)
	{
	}

	void GunItem::OnCollisionExit(Collider* other)
	{
	}
}