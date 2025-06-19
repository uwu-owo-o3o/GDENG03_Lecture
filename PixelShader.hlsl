struct PS_INPUT
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
    
    row_major float4x4 transform_matrix;
    
    float3 m_color;
    int isFlat;
}

float4 psmain(PS_INPUT input) : SV_TARGET
{
    
    if (isFlat == 0)
    {
        return float4(input.color, 1.0);
    }
    else
    {
        return float4(m_color, 1.0);

    }

}