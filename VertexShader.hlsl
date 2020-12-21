struct VS_OUTPUT
{
    float4 Pos : POSITION;
    float4 Color : COLOR0;
};
 
void vertex_shader(float3 Pos : POSITION, float4 Color : COLOR0, out VS_OUTPUT Out)
{
    Out.Pos = float4(Pos, 1);
    Out.Color = Color;
}