#pragma once
#include "qoEntity.h"
#include "qoGraphics.h"

namespace qo::graphics
{
	class ConstantBuffer : public GpuBuffer
	{
	public:
		//ConstantBuffer();
		ConstantBuffer(eCBType type);
		~ConstantBuffer();

		bool Create(size_t size);
		void SetData(void* data);
		void Bind(eShaderStage stage);

	private:
		const eCBType mType;
	};
}