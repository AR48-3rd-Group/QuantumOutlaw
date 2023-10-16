#pragma once
#include "qoResource.h"
#include "qoGraphics.h"

namespace qo
{
	enum class buffertype
	{
		Vertex
		, Texture
		, None
	};

	class Mesh : public Resource
	{
	public:
		Mesh();
		~Mesh();

		virtual HRESULT Load(const std::wstring& path) override;

		bool CreateVertexBuffer(void* data, UINT Count, unsigned long long Size);
		bool CreateIndexBuffer(void* data, UINT Count);
		void BindBuffer();
		void Render();

		void SetBufferType(buffertype buffertype) { mbufferType = buffertype; }

	private:
		Microsoft::WRL::ComPtr<ID3D11Buffer> mVertexBuffer;
		D3D11_BUFFER_DESC mVBDesc;

		Microsoft::WRL::ComPtr<ID3D11Buffer> mIndexBuffer;
		D3D11_BUFFER_DESC mIBDesc;
		UINT mIndexCount;

		// ���� ����
		buffertype mbufferType;
	};
}
