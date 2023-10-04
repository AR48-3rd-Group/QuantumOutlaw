#pragma once
#include "qoItem.h"
#include "qoPlayer.h"

namespace qo
{
	class GunItem : public Item
	{
	public:
		GunItem(eGunType type);
		virtual ~GunItem();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

		virtual void OnCollisionEnter(class Collider* other) override;
		virtual void OnCollisionStay(class Collider* other) override;
		virtual void OnCollisionExit(class Collider* other) override;

		Vector4 GetColor() const { return mColor; }
	
	private:
		eGunType	mGunType;
		Vector4		mColor;
	};
}
