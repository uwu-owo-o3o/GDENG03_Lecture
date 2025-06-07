
struct VS_INPUT
{
    float4 position : POSITION;
    float3 color : COLOR;
    float3 color1 : COLOR1;
};

struct VS_OUTPUT
{
    float4 position : SV_POSITION;
    float3 color : COLOR;
    float3 color1 : COLOR1;
};

cbuffer constant : register(b0)
{
    row_major float4x4 m_world;
    row_major float4x4 m_view;
    row_major float4x4 m_proj;
    unsigned int m_time;
}

VS_OUTPUT vsmain(VS_INPUT input)
{
    VS_OUTPUT output = (VS_OUTPUT)0;
    
    float4 scaled = input.position * float4(0.05f, 0.05f, 0.05f, 1.0f);
    
    output.position = mul(scaled, m_world); // WORLD SPACE
    
    output.position = mul(output.position, m_view); // VIEW SPACE
    
    output.position = mul(output.position, m_proj); // SCREEN SPACE
    
    
    output.color = input.color;
    output.color1 = input.color1;
    
    return output;
}