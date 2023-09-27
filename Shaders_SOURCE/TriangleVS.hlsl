
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

cbuffer TRANSFORM : register(b0)
{
	float3 cbPos;
	int padd1;
	float3 cbScale;
	int padd2;
};

VTX_OUT VS_Test(VTX_IN _in)
{
	VTX_OUT output = (VTX_OUT) 0.f;
    
    output.vPos = float4(_in.vPos * cbScale, 1.f);
    output.vPos.xyz += cbPos.xyz;
    
    //output.vPos *= 5.5f;
	output.vColor = _in.vColor;
    
	return output;
}

// 색상 테스트용 상수버퍼, 버텍스 쉐이더
cbuffer ColorTEST : register(b1) // 레지스터 번호 주의
{
    float4 Test_Pos;
    float4 Test_Scale;
    float4 Test_Color;
};

VTX_OUT VS_Color_Test(VTX_IN _in)
{
    VTX_OUT output = (VTX_OUT) 0.f;
    
    output.vPos = float4(_in.vPos * Test_Scale.xyz, 1.f);
    output.vPos.xyz += Test_Pos.xyz;
    output.vColor = Test_Color; // 상수버퍼의 색상값으로 셋팅
    
    return output;
}
