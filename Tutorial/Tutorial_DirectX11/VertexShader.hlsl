
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
    
    float4 m_obj_pos;
    float4 m_obj_rot;
    float4 m_obj_scale;
    
}

VS_OUTPUT vsmain(VS_INPUT input)
{
    VS_OUTPUT output = (VS_OUTPUT)0;
    
    float3 obj_pos = input.position.xyz + m_obj_pos.xyz;
    
    float3 obj_rot = obj_pos.xyz * m_obj_rot.xyz;
    
    float3 obj_scale = obj_rot.xyz * m_obj_scale.xyz;
    
    float4 obj_transform = float4(obj_scale, 1.0f);
    
    output.position = mul(obj_transform, m_world); // WORLD SPACE
    
    output.position = mul(output.position, m_view); // VIEW SPACE
    
    output.position = mul(output.position, m_proj); // SCREEN SPACE
    
    
    output.texcoord = input.texcoord;
    output.normal = input.normal;
    return output;
}