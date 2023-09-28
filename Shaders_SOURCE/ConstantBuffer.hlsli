
cbuffer TRANSFORM : register(b0)
{
    float3 cbPos;
    int padd1;
    float3 cbScale;
    int padd2;
};

cbuffer ColorTEST : register(b1)
{
    float4 Test_Pos;
    float4 Test_Scale;
    float4 Test_Color;
};
