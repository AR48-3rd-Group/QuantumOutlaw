#include "qoRenderer.h"
#include "qoApplication.h"
#include "qoResourceManager.h"

extern qo::Application application;

namespace qo::renderer
{

	D3D11_INPUT_ELEMENT_DESC InputLayouts[2];

	Mesh* TriangleMesh = nullptr;
	Mesh* RectangleMesh = nullptr;
	Mesh* CircleMesh = nullptr;
	Mesh* BasicRectangleMesh = nullptr;
	Mesh* TextureMesh = nullptr;

	Shader* shader = nullptr;
	Shader* ColorTestShader = nullptr;
	Shader* CircleShader = nullptr;
	Shader* ColorTestShader2 = nullptr;
	Shader* TextureShader = nullptr;

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

		TriangleMesh->CreateVertexBuffer(vertices.data(), 3, sizeof(renderer::Vertex));
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

		// 인덱스
		indexes.push_back(0);
		indexes.push_back(1);
		indexes.push_back(2);

		indexes.push_back(0);
		indexes.push_back(2);
		indexes.push_back(3);

		//// 테두리 사각형 인덱스
		//indexes.push_back(0);
		//indexes.push_back(1);

		//indexes.push_back(0);
		//indexes.push_back(3);

		//indexes.push_back(3);
		//indexes.push_back(2);

		//indexes.push_back(2);
		//indexes.push_back(1);

		RectangleMesh->CreateVertexBuffer(vertices.data(), 4, sizeof(renderer::Vertex));
		RectangleMesh->CreateIndexBuffer(indexes.data(), static_cast<UINT>(indexes.size()));
		ResourceManager::Insert(L"RectangleMesh", RectangleMesh);

		vertices.clear();
		indexes.clear();

		// CircleMesh Vertex Buffer
		Vertex center = {};
		center.pos = Vector3(0.0f, 0.0f, 0.0f);
		center.color = Vector4(1.0f, 1.0f, 1.0f, 1.0f);
		vertices.push_back(center);

		int degree = 360;
		float radian = XM_2PI / (float)degree;
		float radius = 0.5f;

		for (int i = 0; i < degree; ++i)
		{
			center.pos = Vector3(radius * cosf(radian * (float)i), radius * sinf(radian * (float)i), 0.0f);
			center.color = Vector4(0.0f, 1.0f, 0.0f, 1.f);
			vertices.push_back(center);
		}

		for (int i = 0; i < vertices.size() - 2; ++i)
		{
			indexes.push_back(i);
			indexes.push_back(1);
			indexes.push_back(i + 1);
		}

		CircleMesh->CreateVertexBuffer(vertices.data(), static_cast<UINT>(vertices.size()), sizeof(renderer::Vertex));
		CircleMesh->CreateIndexBuffer(indexes.data(), static_cast<UINT>(indexes.size()));
		ResourceManager::Insert(L"CircleMesh", CircleMesh);

		constantBuffers[(UINT)graphics::eCBType::Transform] = new ConstantBuffer(eCBType::Transform);
		constantBuffers[(UINT)graphics::eCBType::Transform]->Create(sizeof(TransformCB));

		constantBuffers[(UINT)graphics::eCBType::ColorSetTRANSFORM] = new ConstantBuffer(eCBType::ColorSetTRANSFORM);
		constantBuffers[(UINT)graphics::eCBType::ColorSetTRANSFORM]->Create(sizeof(ColorSetCB));

		vertices.clear();
		indexes.clear();

		// Basic Rentangle
		/*vertices.resize(4);
		vertices[0].pos = Vector3(-0.00125f, 0.002f, 0.0f);
		vertices[0].color = Vector4(1.f, 0.f, 0.f, 1.f);

		vertices[1].pos = Vector3(0.00125f, 0.002f, 0.0f);
		vertices[1].color = Vector4(0.f, 1.f, 0.f, 1.f);

		vertices[2].pos = Vector3(0.00125f, -0.002f, 0.0f);
		vertices[2].color = Vector4(0.f, 0.f, 1.f, 1.f);

		vertices[3].pos = Vector3(-0.00125f, -0.002f, 0.0f);
		vertices[3].color = Vector4(0.f, 1.f, 0.f, 1.f);*/

		vertices.resize(4);
		vertices[0].pos = Vector3(-0.5f, 0.5f, 0.0f);
		vertices[0].color = Vector4(1.f, 0.f, 0.f, 1.f);

		vertices[1].pos = Vector3(0.5f, 0.5f, 0.0f);
		vertices[1].color = Vector4(0.f, 1.f, 0.f, 1.f);

		vertices[2].pos = Vector3(0.5f, -0.5f, 0.0f);
		vertices[2].color = Vector4(0.f, 0.f, 1.f, 1.f);

		vertices[3].pos = Vector3(-0.5f, -0.5f, 0.0f);
		vertices[3].color = Vector4(0.f, 1.f, 0.f, 1.f);

		// 인덱스
		/*indexes.push_back(0);
		indexes.push_back(1);
		indexes.push_back(2);

		indexes.push_back(0);
		indexes.push_back(2);
		indexes.push_back(3);*/

		//// 테두리 사각형 인덱스
		indexes.push_back(0);
		indexes.push_back(1);

		indexes.push_back(0);
		indexes.push_back(3);

		indexes.push_back(3);
		indexes.push_back(2);

		indexes.push_back(2);
		indexes.push_back(1);

		BasicRectangleMesh->CreateVertexBuffer(vertices.data(), 4, sizeof(renderer::Vertex));
		BasicRectangleMesh->CreateIndexBuffer(indexes.data(), static_cast<UINT>(indexes.size()));
		ResourceManager::Insert(L"BasicRectangleMesh", BasicRectangleMesh);

		vertices.clear();
		indexes.clear();

		std::vector<TextureVertex> texturevertex;
		texturevertex.resize(4);

		texturevertex[0].pos = Vector3(-0.5f, 0.5f, 0.0f);
		texturevertex[0].uv = Vector2(0.f, 0.f);

		texturevertex[1].pos = Vector3(0.5f, 0.5f, 0.0f);
		texturevertex[1].uv = Vector2(1.f, 0.f);

		texturevertex[2].pos = Vector3(0.5f, -0.5f, 0.0f);
		texturevertex[2].uv = Vector2(1.f, 1.f);

		texturevertex[3].pos = Vector3(-0.5f, -0.5f, 0.0f);
		texturevertex[3].uv = Vector2(0.f, 1.f);

		indexes.push_back(0);
		indexes.push_back(1);
		indexes.push_back(2);

		indexes.push_back(0);
		indexes.push_back(2);
		indexes.push_back(3);

		TextureMesh->CreateVertexBuffer(texturevertex.data(), 4, sizeof(TextureVertex));
		TextureMesh->SetBufferType(buffertype::Texture);
		TextureMesh->CreateIndexBuffer(indexes.data(), static_cast<UINT>(indexes.size()));
		ResourceManager::Insert(L"TextureMesh", TextureMesh);

		vertices.clear();
		indexes.clear();
	}

	void LoadShader()
	{
		shader->Create(eShaderStage::VS, L"TriangleVS.hlsl", "VS");
		shader->Create(eShaderStage::PS, L"TrianglePS.hlsl", "PS");
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

		// Color Test Shader 쉐이더 코드 컴파일 InputLayouts은 위와 같으므로 설정안함
		ColorTestShader->Create(eShaderStage::VS, L"TriangleVS.hlsl", "ColorSetVS");
		ColorTestShader->Create(eShaderStage::PS, L"TrianglePS.hlsl", "PS");
		ResourceManager::Insert(L"ColorTestShader", ColorTestShader);

		GetDevice()->CreateInputLayout(InputLayouts, 2,
			ColorTestShader->GetVSCode()->GetBufferPointer()
			, ColorTestShader->GetVSCode()->GetBufferSize()
			, ColorTestShader->GetInputLayoutAddressOf());

		//
		ColorTestShader2->Create(eShaderStage::VS, L"TriangleVS.hlsl", "ColorSetVS");
		ColorTestShader2->Create(eShaderStage::PS, L"TrianglePS.hlsl", "PS");
		ColorTestShader2->SetTopology(D3D11_PRIMITIVE_TOPOLOGY::D3D10_PRIMITIVE_TOPOLOGY_LINELIST);
		ResourceManager::Insert(L"ColorTestShader2", ColorTestShader2);

		GetDevice()->CreateInputLayout(InputLayouts, 2,
			ColorTestShader2->GetVSCode()->GetBufferPointer()
			, ColorTestShader2->GetVSCode()->GetBufferSize()
			, ColorTestShader2->GetInputLayoutAddressOf());

		// Circle Shader
		CircleShader->Create(eShaderStage::VS, L"CircleVS.hlsl", "VS");
		CircleShader->Create(eShaderStage::PS, L"CirclePS.hlsl", "PS");
		CircleShader->SetTopology(D3D11_PRIMITIVE_TOPOLOGY::D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		ResourceManager::Insert(L"CircleShader", CircleShader);

		GetDevice()->CreateInputLayout(InputLayouts, 2,
			CircleShader->GetVSCode()->GetBufferPointer()
			, CircleShader->GetVSCode()->GetBufferSize()
			, CircleShader->GetInputLayoutAddressOf());


		// Texture Shader
		TextureShader->Create(eShaderStage::VS, L"TextureVS.hlsl", "VS");
		TextureShader->Create(eShaderStage::PS, L"TexturePS.hlsl", "PS");
		TextureShader->CreateSamplerState();
		TextureShader->ResourceViewCreate(L"..\\Resources\\NPC_Commander0.png");
		ResourceManager::Insert(L"TextureShader", TextureShader);

		D3D11_INPUT_ELEMENT_DESC inputElementDesc2[] =
		{
			{"POSITION",0,DXGI_FORMAT_R32G32B32_FLOAT,0,0,D3D11_INPUT_PER_VERTEX_DATA,0},
			{"TEXCOORD",0,DXGI_FORMAT_R32G32_FLOAT,0,D3D11_APPEND_ALIGNED_ELEMENT,D3D11_INPUT_PER_VERTEX_DATA,0}
		};

		GetDevice()->CreateInputLayout(
			inputElementDesc2
			, ARRAYSIZE(inputElementDesc2)
			, TextureShader->GetVSCode()->GetBufferPointer()
			, TextureShader->GetVSCode()->GetBufferSize()
			, TextureShader->GetInputLayoutAddressOf());
	}

	void Initialize()
	{
		TriangleMesh = new Mesh();
		RectangleMesh = new Mesh();
		CircleMesh = new Mesh();
		BasicRectangleMesh = new Mesh();
		TextureMesh = new Mesh();

		shader = new Shader();
		ColorTestShader = new Shader();
		CircleShader = new Shader();
		ColorTestShader2 = new Shader();
		TextureShader = new Shader();

		LoadShader();
		SetUpStates();
		LoadBuffer();
	}

	void Release()
	{
		// ------------------
		// ResourceManger에서 메모리 해제
		// ------------------
		/*delete TriangleMesh;
		delete RectangleMesh;
		delete CircleMesh;
		delete BasicRectangleMesh;

		delete shader;
		delete ColorTestShader;
		delete CircleShader;
		delete ColorTestShader2;*/

		delete constantBuffers[(UINT)graphics::eCBType::Transform];
		delete constantBuffers[(UINT)graphics::eCBType::ColorSetTRANSFORM];
		//triangleVertexBuffer->Release();
		//errorBlob->Release();
		//triangleVSBlob->Release();
		//triangleVSShader->Release();
		//trianglePSBlob->Release();
		//trianglePSShader->Release();
		//triangleLayout->Release();
	}
}