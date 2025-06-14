
struct VS_INPUT
{
    float4 position : POSITION0;
    float2 texcoord : TEXCOORD0;
    float3 normal : NORMAL0;
};

struct VS_OUTPUT
{
    float4 position : SV_POSITION;
    float2 texcoord : TEXCOORD0;
    float3 normal : TEXCOORD1;
    float3 dir_to_cam : TEXCOORD2;
};

cbuffer constant : register(b0)
{
    row_major float4x4 m_world;
    row_major float4x4 m_view;
    row_major float4x4 m_proj;
    
    float4 m_cam_pos;
    
    float3 currentColor;
    
    row_major float4x4 transform_matrix;
    
}

VS_OUTPUT vsmain(VS_INPUT input)
{
    VS_OUTPUT output = (VS_OUTPUT)0;
    
    float4 m_transform = mul(input.position, transform_matrix);
    
    output.position = mul(m_transform, m_world); // WORLD SPACE
    
    output.position = mul(output.position, m_view); // VIEW SPACE
    
    output.position = mul(output.position, m_proj); // SCREEN SPACE
    
    
    output.texcoord = input.texcoord;
    output.normal = input.normal;
    return output;
}