
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
    // AMBIENT LIGHT
    float ka = 0.1f;
    float3 ia = float3(1.0f, 1.0f, 1.0f);
    
    float3 ambient_light = ka * ia;
    
    //DIFFUSE LIGHT
    float kd = 0.7f;
    float3 id = float3(1.0f, 1.0f, 1.0f);
    
    float amount_diffuse_light = max(0.0, dot(m_light_direction.xyz, input.normal));
    
    float3 diffuse_light = kd * amount_diffuse_light * id;
    
    //SPECULAR LIGHT
    float ks = 1.0f;
    float3 is = float3(1.0f, 1.0f, 1.0f);
    float3 reflected_light = reflect(m_light_direction.xyz, input.normal);
    float shininess = 100.0f;
    float amount_spec_light = pow(max(0.0, dot(reflected_light, input.dir_to_cam)), shininess);
    
    float spec_light = ks * amount_spec_light * is;
    
    
    float3 final_light = ambient_light + diffuse_light + spec_light;
    
    //return Texture.Sample(TextureSampler, input.texcoord * 0.5f);
    return float4(final_light, 1.0f);

}