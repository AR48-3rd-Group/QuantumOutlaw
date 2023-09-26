#pragma once
#include "qoEnums.h"
#include "CommonInclude.h"
#include "qoEngine.h"
#include "qoMath.h"
#include "qoGraphicsDevice_DX11.h"

#include "qoMesh.h"
#include "qoShader.h"
#include "qoConstantBuffer.h"

using namespace qo::graphics;
using namespace qo::enums;
using namespace qo::math;

namespace qo::renderer
{
	struct Vertex
	{
		Vector3 pos;
		Vector4 color;
	};

	CBUFFER(TransformCB, CBSLOT_TRANSFORM)
	{
		Vector3 pos;
		int padd1;

		Vector3 scale;
		int padd2;
	};

	extern Mesh* mesh;
	extern Shader* shader;
	extern ConstantBuffer* constantBuffers[];

	// Initialize the renderer
	void Initialize();
	void Release();
}
