#include "qoTransform.h"
#include "qoGraphicsDevice_DX11.h"
#include "qoRenderer.h"
#include "qoCamera.h"

namespace qo
{

	Transform::Transform()
		: Component(COMPONENTTYPE::TRANSFORM)
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
		ConstantBuffer* cb = renderer::constantBuffers[(UINT)graphics::eCBType::Transform];

		renderer::TransformCB data = {};
		math::Vector3 temp;
		temp.x = mPosition.x;
		temp.y = mPosition.y;
		temp.z = mPosition.z;
		temp = Camera::CaculatePos(temp);

		data.pos = temp;
		data.scale = mScale;
		cb->SetData(&data);

		cb->Bind(graphics::eShaderStage::VS);
	}

}