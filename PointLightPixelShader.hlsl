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
    float strength_ambient = 1.5f;
    float3 ambient_color = float3(0.08f, 0.0f, 0.0f);
    ambient_color *= (tex_color.rgb);
    
    float3 ambient_light = strength_ambient * ambient_color;
    
    //DIFFUSE LIGHT
    float strength_diffuse = 0.7f;
    float3 light_dir = normalize(m_light_position.xyz - input.world_pos.xyz);
    float distance_light_object = length(m_light_position.xyz - input.world_pos.xyz);
    
    float fade_area = max(0, distance_light_object - m_light_radius);
    
    float attenuation = 1.0 + fade_area;
    
    float3 diffuse_color = float3(1.0f, 1.0f, 1.0f);
    
    float amount_diffuse_light = max(0.0, dot(light_dir.xyz, input.normal));
    
    float3 diffuse_light = (strength_diffuse * diffuse_color * amount_diffuse_light) / attenuation;
    
    //SPECULAR LIGHT
    float spec_strength = 1.0f;
    float3 dir_to_cam = normalize(input.world_pos.xyz - m_cam_pos.xyz);
    
    float3 strength_color = float3(1.0f, 1.0f, 1.0f);
    float3 reflected_light = reflect(light_dir.xyz, input.normal);
    float shininess = 30.0f;
    float amount_spec_light = pow(max(0.0, dot(reflected_light, dir_to_cam)), shininess);
    
    float spec_light = (spec_strength * amount_spec_light * strength_color) / attenuation;
    
    //BOUNCED LIGHT
    
    
    float3 final_light = ambient_light + diffuse_light + spec_light;
    
    //return Texture.Sample(TextureSampler, input.texcoord * 0.5f);
    return float4(final_light, 1.0f);

}