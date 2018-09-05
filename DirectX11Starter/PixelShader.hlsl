struct VertexToPixel
{
	float4 position			: SV_POSITION;
	float3 normal		: NORMAL;
	float2 uv           : TEXCOORD;

};

float4 main(VertexToPixel input)  : SV_TARGET
{
	return float4(0,0,1,1);
}