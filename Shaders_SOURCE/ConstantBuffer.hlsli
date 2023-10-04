
cbuffer TRANSFORM : register(b0)
{
    float3 cb0Pos;
    int padd1;
    float3 cb0Scale;
    int padd2;
};

cbuffer ColorSetTRANSFORM: register(b1)
{
    float4 cb1Pos;
    float4 cb1Scale;
    float4 cb1Color;
};