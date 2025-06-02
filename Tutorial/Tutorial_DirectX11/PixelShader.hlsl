
Texture2D Texture : register(t0);
sampler TextureSampler : register(s0);


struct PS_INPUT
{
    float4 position : SV_POSITION;
    float2 texcoord : TEXCOORD0;
    float3 normal : TEXCOORD1;
};

cbuffer constant : register(b0)
{
    row_major float4x4 m_world;
    row_major float4x4 m_view;
    row_major float4x4 m_proj;
    float4 m_light_direction;
}

float4 psmain(PS_INPUT input) : SV_TARGET
{
    float ka = 0.2f;
    float3 ia = float3(1.0f, 1.0f, 1.0f);
    
    float3 ambient_light = ka * ia;
    
    float kd = 1.0f;
    float3 id = float3(1.0f, 1.0f, 1.0f);
    
    float amount_diffuse_light = max(0.0, dot(m_light_direction.xyz, input.normal));
    
    float3 diffuse_light = kd * amount_diffuse_light * id;
    
    float3 final_light = ambient_light + diffuse_light;
    
    //return Texture.Sample(TextureSampler, input.texcoord * 0.5f);
    return float4(final_light, 1.0f);

}