
Texture2D Texture : register(t0);
sampler TextureSampler : register(s0);


struct PS_INPUT
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
    float4 m_light_direction;
}

float4 psmain(PS_INPUT input) : SV_TARGET
{
    
    float4 objTexture = Texture.Sample(TextureSampler, input.texcoord * 1.0f);
    float4 tintColor = float4(1, 0, 0, 0);
    return objTexture * tintColor;

}