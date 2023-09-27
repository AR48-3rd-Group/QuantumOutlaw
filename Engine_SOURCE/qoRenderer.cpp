#include "qoRenderer.h"
#include "qoApplication.h"
#include "qoResourceManager.h"

extern qo::Application application;

namespace qo::renderer
{

	D3D11_INPUT_ELEMENT_DESC InputLayouts[2];
	Mesh* TriangleMesh = nullptr;
	Mesh* RectangleMesh = nullptr;
	Shader* shader = nullptr;
	ConstantBuffer* constantBuffers[(UINT)graphics::eCBType::End];

	void SetUpStates()
	{
	}

	void LoadBuffer()
	{
		std::vector<Vertex> vertices;
		std::vector<UINT> indexes;

		// Triangle Vertex Buffer
		vertices.resize(3);
		vertices[0].pos = Vector3(0.f, 0.5f, 0.f);
		vertices[0].color = Vector4(0.f, 1.f, 0.f, 1.f);

		vertices[1].pos = Vector3(0.5f, -0.5f, 0.f);
		vertices[1].color = Vector4(1.f, 0.f, 0.f, 1.f);

		vertices[2].pos = Vector3(-0.5f, -0.5f, 0.f);
		vertices[2].color = Vector4(0.f, 0.f, 1.f, 1.f);

		indexes.push_back(0);
		indexes.push_back(2);
		indexes.push_back(3);

		indexes.push_back(0);
		indexes.push_back(1);
		indexes.push_back(2);

		TriangleMesh->CreateVertexBuffer(vertices.data(), 3);
		TriangleMesh->CreateIndexBuffer(indexes.data(), static_cast<UINT>(indexes.size()));
		ResourceManager::Insert(L"TriangleMesh", TriangleMesh);

		vertices.clear();
		indexes.clear();

		// RectangleMesh Vertex Buffer
		vertices.resize(4);
		vertices[0].pos = Vector3(-0.5f, 0.5f, 0.0f);
		vertices[0].color = Vector4(1.f, 0.f, 0.f, 1.f);

		vertices[1].pos = Vector3(0.5f, 0.5f, 0.0f);
		vertices[1].color = Vector4(0.f, 1.f, 0.f, 1.f);

		vertices[2].pos = Vector3(0.5f, -0.5f, 0.0f);
		vertices[2].color = Vector4(0.f, 0.f, 1.f, 1.f);

		vertices[3].pos = Vector3(-0.5f, -0.5f, 0.0f);
		vertices[3].color = Vector4(0.f, 1.f, 0.f, 1.f);

		indexes.push_back(0);
		indexes.push_back(1);
		indexes.push_back(2);

		indexes.push_back(0);
		indexes.push_back(2);
		indexes.push_back(3);

		RectangleMesh->CreateVertexBuffer(vertices.data(), 4);
		RectangleMesh->CreateIndexBuffer(indexes.data(), static_cast<UINT>(indexes.size()));
		ResourceManager::Insert(L"RectangleMesh", RectangleMesh);

		vertices.clear();
		indexes.clear();

		constantBuffers[(UINT)graphics::eCBType::Transform] = new ConstantBuffer();
		constantBuffers[(UINT)graphics::eCBType::Transform]->Create(sizeof(TransformCB));
	}

	void LoadShader()
	{
		shader->Create(eShaderStage::VS, L"TriangleVS.hlsl", "VS_Test");
		shader->Create(eShaderStage::PS, L"TrianglePS.hlsl", "PS_Test");
		ResourceManager::Insert(L"TriangleShader", shader);
		//GetDevice()->CreateShader(eShaderStage::NONE);
		//GetDevice()->CreateVertexShader();`
				// Input layout 정점 구조 정보
		InputLayouts[0].AlignedByteOffset = 0;
		InputLayouts[0].Format = DXGI_FORMAT_R32G32B32_FLOAT;
		InputLayouts[0].InputSlot = 0;
		InputLayouts[0].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
		InputLayouts[0].SemanticName = "POSITION";
		InputLayouts[0].SemanticIndex = 0;

		InputLayouts[1].AlignedByteOffset = 12;
		InputLayouts[1].Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
		InputLayouts[1].InputSlot = 0;
		InputLayouts[1].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
		InputLayouts[1].SemanticName = "COLOR";
		InputLayouts[1].SemanticIndex = 0;

		GetDevice()->CreateInputLayout(InputLayouts, 2,
			shader->GetVSCode()->GetBufferPointer()
			, shader->GetVSCode()->GetBufferSize()
			, shader->GetInputLayoutAddressOf());
	}

	void Initialize()
	{
		TriangleMesh = new Mesh();
		RectangleMesh = new Mesh();
		shader = new Shader();

		LoadShader();
		SetUpStates();
		LoadBuffer();
	}

	void Release()
	{
		delete TriangleMesh;
		delete RectangleMesh;
		delete shader;

		delete constantBuffers[(UINT)graphics::eCBType::Transform];
		//triangleVertexBuffer->Release();
		//errorBlob->Release();
		//triangleVSBlob->Release();
		//triangleVSShader->Release();
		//trianglePSBlob->Release();
		//trianglePSShader->Release();
		//triangleLayout->Release();
	}
}