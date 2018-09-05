cbuffer externalData : register(b0)
{
	matrix world;
	matrix view;
	matrix projection;
};

struct VertexShaderInput
{
	// Data type
	//  |
	//  |   Name          Semantic
	//  |    |                |
	//  v    v                v
	float3 position		: POSITION;     // XYZ position
	float3 normal		: NORMAL;        // Normals
	float2 uv           : TEXCOORD;     //UVs

};


//must match pixel shader's input
struct VertexToPixel
{
	float4 position		: SV_POSITION;
	float3 normal		: NORMAL;        
	float2 uv           : TEXCOORD;
};

VertexToPixel main(VertexShaderInput input)
{
	VertexToPixel output;

	matrix worldViewProj = mul(mul(world, view), projection);

	output.position = mul(float4(input.position, 1.0f), worldViewProj);

	//output.color = input.color;

	return output;
}