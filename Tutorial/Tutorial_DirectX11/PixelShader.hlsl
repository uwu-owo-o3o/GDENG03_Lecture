
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
   
    float4 m_cam_pos;
    
    float3 currentColor;
    int isFlat;
    
    row_major float4x4 transform_matrix;
}

float4 psmain(PS_INPUT input) : SV_TARGET
{
    
    float4 objTexture = Texture.Sample(TextureSampler, input.texcoord * 0.5f);
    float4 tintColor = float4(currentColor, 1.0);
    
    if (isFlat == 1)
    {
        return tintColor;
    }
    else
    {
        return tintColor * objTexture;
    }
}