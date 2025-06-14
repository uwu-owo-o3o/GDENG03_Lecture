//[numthreads(1, 1, 1)]
//void main( uint3 DTid : SV_DispatchThreadID )
//{
    
//}

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
    float3 normal : NORMAL0;
    float3 world_pos : TEXCOORD1;
};

cbuffer constant : register(b0)
{
    row_major float4x4 m_world;
    row_major float4x4 m_view;
    row_major float4x4 m_proj;
    float4 m_light_direction;
    float4 m_cam_pos;
    
    float4 m_light_position;
    float m_light_radius;
}

VS_OUTPUT vsmain(VS_INPUT input)
{
    VS_OUTPUT output = (VS_OUTPUT) 0;
    
    output.position = mul(input.position, m_world); // WORLD SPACE
    
    //output.dir_to_cam = normalize(output.position.xyz - m_cam_pos.xyz);
    output.world_pos = output.position.xyz;
    
    
    output.position = mul(output.position, m_view); // VIEW SPACE
    
    output.position = mul(output.position, m_proj); // SCREEN SPACE
    
    
    output.texcoord = input.texcoord;
    output.normal = input.normal;
    return output;
}