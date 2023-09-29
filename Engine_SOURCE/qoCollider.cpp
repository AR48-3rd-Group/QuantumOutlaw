#include "qoCollider.h"
#include "qoGameObject.h"
#include "qoTransform.h"
#include "qoResourceManager.h"
#include "qoConstantBuffer.h"
#include "qoRenderer.h"
#include "qoCamera.h"

namespace qo
{
	UINT Collider::mCollisionCount = 0;

	Collider::Collider()
		:
		Component(COMPONENTTYPE::COLLIDER)
		, mScale(math::Vector3(0.f, 0.f, 0.f))
		, mOffset(math::Vector3(0.f, 0.f, 0.f))
		, mAffectedCamera(true)
		, mbIsCollision(false)
		, mCollisionNumber(mCollisionCount++)
	{
		mMesh = ResourceManager::Find<Mesh>(L"BasicRectangleMesh");
		mShader = ResourceManager::Find<Shader>(L"ColorTestShader2");
	}

	Collider::~Collider()
	{
	}

	void Collider::Initialize()
	{
	}

	void Collider::Update()
	{
	}

	void Collider::LateUpdate()
	{
	}

	void Collider::Render()
	{
		if (mbIsCollision)
		{
			ConstantBuffer* Register1Cb = renderer::constantBuffers[(UINT)graphics::eCBType::Color_Test];
			Vector3 OwnerPostion = GetOwner()->GetComponent<Transform>()->GetPosition();

			renderer::ColorTestCB data = {};
			math::Vector3 temp;
			temp.x = OwnerPostion.x;
			temp.y = OwnerPostion.y;
			temp.z = OwnerPostion.z;
			temp = Camera::CaculatePos(temp);

			data.pos = math::Vector4(temp.x, temp.y, temp.z, 0.f);
			data.scale = math::Vector4(mScale.x, mScale.y, mScale.z, 0.f);
			data.color = math::Vector4(1.f, 0.f, 0.f, 0.f);
			Register1Cb->SetData(&data);

			Register1Cb->Bind(graphics::eShaderStage::VS);
		}
		else
		{
			ConstantBuffer* Register1Cb = renderer::constantBuffers[(UINT)graphics::eCBType::Color_Test];
			Vector3 OwnerPostion = GetOwner()->GetComponent<Transform>()->GetPosition();

			renderer::ColorTestCB data = {};
			math::Vector3 temp;
			temp.x = OwnerPostion.x;
			temp.y = OwnerPostion.y;
			temp.z = OwnerPostion.z;
			temp = Camera::CaculatePos(temp);

			data.pos = math::Vector4(temp.x, temp.y, temp.z, 0.f);
			data.scale = math::Vector4(mScale.x, mScale.y, mScale.z, 0.f);
			data.color = math::Vector4(0.f, 1.f, 0.f, 0.f);
			Register1Cb->SetData(&data);

			Register1Cb->Bind(graphics::eShaderStage::VS);
		}

		mShader->Update();
		mMesh->Render();
	}

	void Collider::OnCollisionEnter(Collider* other)
	{
		GetOwner()->OnCollisionEnter(other);
		mbIsCollision = true;
	}

	void Collider::OnCollisionStay(Collider* other)
	{
		GetOwner()->OnCollisionStay(other);
	}

	void Collider::OnCollisionExit(Collider* other)
	{
		GetOwner()->OnCollisionExit(other);
		mbIsCollision = false;
	}
}