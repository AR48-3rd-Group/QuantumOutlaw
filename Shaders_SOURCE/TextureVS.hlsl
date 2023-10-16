#include "ConstantBuffer.hlsli"

struct VTX_IN
{
    float3 vPos : POSITION;
    float2 vUv : TEXCOORD;
};

struct VTX_OUT
{
    float4 vPos : SV_Position;
    float2 vUv : TEXCOORD;
};

VTX_OUT VS(VTX_IN _in)
{
    VTX_OUT output = (VTX_OUT) 0.f;
    
    output.vPos = float4(_in.vPos * cb0Scale, 1.f);
    output.vPos.xyz += cb0Pos.xyz;
    
    //output.vPos *= 5.5f;
    output.vUv = _in.vUv;
    
    return output;
}