#pragma once
#include "qoComponent.h" 
#include "qoMesh.h"
#include "qoShader.h"

namespace qo
{
	using namespace graphics;
	class Collider : public Component
	{
	public:
		Collider();
		virtual ~Collider();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

		virtual void OnCollisionEnter(Collider* other);
		virtual void OnCollisionStay(Collider* other);
		virtual void OnCollisionExit(Collider* other);

		void SetScale(math::Vector3 scale) { mScale = scale; }
		math::Vector3 GetScale() { return mScale; }

		math::Vector3 SetAffectedCamera(bool affectedcamera) { mAffectedCamera = affectedcamera; }

		void SetOffset(math::Vector3 offset) { mOffset = offset; }
		math::Vector3 GetOffset() { return mOffset; }

		UINT GetCollisionNumber() const { return mCollisionNumber; }

		void SetActive(bool active) { mIsActive = active; }

	private:
		static UINT mCollisionCount;
		UINT mCollisionNumber;

		math::Vector3 mScale;
		math::Vector3 mOffset;
		bool mbIsCollision;
		bool mAffectedCamera;

		// 충돌 상자 작동 여부
		bool mIsActive;

		// Collider Render
		Mesh* mMesh;
		Shader* mShader;
	};
}


