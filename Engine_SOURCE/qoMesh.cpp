#include "qoMesh.h"
#include "qoRenderer.h"

namespace qo
{
    Mesh::Mesh()
        :mbufferType(buffertype::Vertex)
    {
    }

    Mesh::~Mesh()
    {
    }

    HRESULT Mesh::Load(const std::wstring& path)
    {
        return E_NOTIMPL;
    }

    bool Mesh::CreateVertexBuffer(void* data, UINT Count, unsigned long long Size)
    {
        mVBDesc.ByteWidth = static_cast<UINT>(Size * Count);
        mVBDesc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_VERTEX_BUFFER;
        mVBDesc.Usage = D3D11_USAGE_DEFAULT;
        mVBDesc.CPUAccessFlags = 0;

        D3D11_SUBRESOURCE_DATA subData = {};
        subData.pSysMem = data;

        if (!(GetDevice()->CreateBuffer(&mVBDesc, &subData, mVertexBuffer.GetAddressOf())))
            return false;

        return true;
    }

    bool Mesh::CreateIndexBuffer(void* data, UINT Count)
    {
        mIndexCount = Count;
        mIBDesc.ByteWidth = sizeof(UINT) * Count;
        mIBDesc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_INDEX_BUFFER;
        mIBDesc.Usage = D3D11_USAGE_DEFAULT;
        mIBDesc.CPUAccessFlags = 0;

        D3D11_SUBRESOURCE_DATA subData = {};
        subData.pSysMem = data;

        if (!(GetDevice()->CreateBuffer(&mIBDesc, &subData, mIndexBuffer.GetAddressOf())))
            return false;

        return true;
    }

    void Mesh::BindBuffer()
    {
       /* UINT stride = sizeof(renderer::Vertex);
        UINT offset = 0;

        GetDevice()->BindVertexBuffer(0, 1, mVertexBuffer.GetAddressOf(), stride, offset);
        GetDevice()->BindIndexBuffer(mIndexBuffer.Get(), DXGI_FORMAT_R32_UINT, 0);*/
        if (mbufferType == buffertype::Vertex)
        {
            UINT stride = sizeof(renderer::Vertex);
            UINT offset = 0;
            GetDevice()->BindVertexBuffer(0, 1, mVertexBuffer.GetAddressOf(), stride, offset);
            GetDevice()->BindIndexBuffer(mIndexBuffer.Get(), DXGI_FORMAT_R32_UINT, 0);
        }
        else if (mbufferType == buffertype::Texture)
        {
            UINT stride = sizeof(renderer::TextureVertex);
            UINT offset = 0;
            GetDevice()->BindVertexBuffer(0, 1, mVertexBuffer.GetAddressOf(), stride, offset);
            GetDevice()->BindIndexBuffer(mIndexBuffer.Get(), DXGI_FORMAT_R32_UINT, 0);
        }

        /*Vector4 pos(0.5f, 0.2f, 0.0f, 0.0f);
        GetDevice()->BindConstantBuffer(mConstantBuffer.Get(), &pos, sizeof(Vector4));*/
    }

    void Mesh::Render()
    {
        //set costant buffer 
        //renderer::constantBuffers[(UINT)graphics::CBTYPES::TRANSFORM]->Bind(eShaderStage::VS);

        //// Input Assembeler 단계에 버텍스버퍼 정보 지정
        BindBuffer();
        //Vector4 pos(0.5f, 0.2f, 0.0f, 0.0f);
        //renderer::constantBuffers[(UINT)graphics::CBTYPES::TRANSFORM]->SetData(&pos);

        // Set Inputlayout, shader
        //renderer::shader->Update();

        GetDevice()->DrawIndexed(mIndexCount, 0, 0);
    }
}