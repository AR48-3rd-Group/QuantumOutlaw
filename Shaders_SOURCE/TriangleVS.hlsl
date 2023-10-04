#include "ConstantBuffer.hlsli"

struct VTX_IN
{
	float3 vPos : POSITION;
	float4 vColor : COLOR;
};

struct VTX_OUT
{
	float4 vPos : SV_Position;
	float4 vColor : COLOR;
};

VTX_OUT VS(VTX_IN _in)
{
	VTX_OUT output = (VTX_OUT) 0.f;
    
    output.vPos = float4(_in.vPos * cb0Scale, 1.f);
    output.vPos.xyz += cb0Pos.xyz;
    
    //output.vPos *= 5.5f;
	output.vColor = _in.vColor;
    
	return output;
}

VTX_OUT ColorSetVS(VTX_IN _in)
{
    VTX_OUT output = (VTX_OUT) 0.f;
    
    output.vPos = float4(_in.vPos * cb1Scale.xyz, 1.f);
    output.vPos.xyz += cb1Pos.xyz;
    output.vColor = cb1Color; // 상수버퍼의 색상값으로 셋팅

    return output;
}
