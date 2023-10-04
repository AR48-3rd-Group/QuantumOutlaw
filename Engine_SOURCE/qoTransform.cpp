#include "qoTransform.h"
#include "qoGraphicsDevice_DX11.h"
#include "qoRenderer.h"
#include "qoCamera.h"
#include "qoApplication.h"

extern qo::Application application;

namespace qo
{
	Transform::Transform()
		: Component(COMPONENTTYPE::TRANSFORM)
		, mColor(math::Vector4(1.f, 1.f, 1.f, 0.f))
		, mAffectedCamera(true)
	{

	}

	Transform::~Transform()
	{
	}

	void Transform::Initialize()
	{
	}

	void Transform::Update()
	{
	}

	void Transform::LateUpdate()
	{
	}

	void Transform::Render()
	{
	}

	void Transform::SetConstantBuffer()
	{
		// 레지스터 0번 상수 버퍼 셋팅
		{
			ConstantBuffer* Register0Cb = renderer::constantBuffers[(UINT)graphics::eCBType::Transform];

			renderer::TransformCB data = {};
			math::Vector3 temp;
			temp.x = mPosition.x;
			temp.y = mPosition.y;
			temp.z = mPosition.z;

			if(mAffectedCamera)
				temp = Camera::CaculatePos(temp);

			data.pos = temp;
			data.scale = mScale;
			Register0Cb->SetData(&data);

			Register0Cb->Bind(graphics::eShaderStage::VS);
		}


		// 레지스터 1번 상수 버퍼 셋팅
		{
			ConstantBuffer* Register1Cb = renderer::constantBuffers[(UINT)graphics::eCBType::ColorSetTRANSFORM];

			renderer::ColorSetCB data = {};
			math::Vector3 temp;
			temp.x = mPosition.x;
			temp.y = mPosition.y;
			temp.z = mPosition.z;
			
			if (mAffectedCamera)
				temp = Camera::CaculatePos(temp);

			data.pos = math::Vector4(temp.x, temp.y, temp.z, 0.f);
			data.scale = math::Vector4(mScale.x, mScale.y, mScale.z, 0.f);
			data.color = mColor;
			Register1Cb->SetData(&data);

			Register1Cb->Bind(graphics::eShaderStage::VS);
		}		
	}

	void Transform::SetPositionInPixels(float xPixels, float yPixels, float z)
	{
		float normalizedX = (2.0f * xPixels) / static_cast<float>(application.GetWidth()) - 1.0f;
		float normalizedY = (2.0f * yPixels) / static_cast<float>(application.GetHeight()) - 1.0f;

		SetPosition(Vector3(normalizedX, normalizedY, z));
	}

	void Transform::SetScaleInPixels(float widthInPixels, float heightInPixels, float z)
	{
		float normalizedScaleX = (2.0f * widthInPixels) / static_cast<float>(application.GetWidth());
		float normalizedScaleY = (2.0f * heightInPixels) / static_cast<float>(application.GetHeight());

		SetScale(Vector3(normalizedScaleX, normalizedScaleY, z));
	}
}