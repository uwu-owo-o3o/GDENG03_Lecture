Texture2D TextureColor : register(t0);
sampler TextureColorSampler : register(s0);


struct PS_INPUT
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

float4 psmain(PS_INPUT input) : SV_TARGET
{
    float4 tex_color = float4(1, 1, 1, 1);
    
    // AMBIENT LIGHT
    float ka = 1.5f;
    float3 ia = float3(0.09f, 0.082f, 0.082f);
    ia *= (tex_color.rgb);
    
    float3 ambient_light = ka * ia;
    
    //DIFFUSE LIGHT
    float kd = 0.7f;
    float3 light_dir = normalize(m_light_position.xyz - input.world_pos.xyz);
    float distance_light_object = length(m_light_position.xyz - input.world_pos.xyz);
    
    float fade_area = max(0, distance_light_object - m_light_radius);
    
    float constant_func = 1.0;
    float linear_func = 2.0;
    float quadratic_func = 2.0;
    
    float attenuation = constant_func + linear_func * fade_area + quadratic_func * fade_area * fade_area;
    
    
    float3 id = float3(1.0f, 1.0f, 1.0f);
    
    float amount_diffuse_light = max(0.0, dot(light_dir.xyz, input.normal));
    
    float3 diffuse_light = (kd * id * amount_diffuse_light) / attenuation;
    
    //SPECULAR LIGHT
    float ks = 1.0f;
    float3 dir_to_cam = normalize(input.world_pos.xyz - m_cam_pos.xyz);
    
    float3 is = float3(1.0f, 1.0f, 1.0f);
    float3 reflected_light = reflect(light_dir.xyz, input.normal);
    float shininess = 30.0f;
    float amount_spec_light = pow(max(0.0, dot(reflected_light, dir_to_cam)), shininess);
    
    float spec_light = (ks * amount_spec_light * is) / attenuation;
    
    
    float3 final_light = ambient_light + diffuse_light + spec_light;
    
    //return Texture.Sample(TextureSampler, input.texcoord * 0.5f);
    return float4(final_light, 1.0f);

}