// HLSL 로 VertexShader 작성하기

SamplerState SampleType;
Texture2D ShaderTexture;

struct VTX_OUT
{
    float4 vPos : SV_Position;
    float2 vUv : TEXCOORD;
};

float4 PS(VTX_OUT _in) : SV_Target
{
    float4 color = ShaderTexture.Sample(SampleType, _in.vUv);
   
    return color;
}