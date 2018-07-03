#include "Mesh.h"
#


using namespace DirectX;


Mesh::Mesh(Vertex * vertices, int vertexCount, int * indices, int indexCount, ID3D11Device * device)
{
	CreateBasicGeometry(vertices, vertexCount, indices, indexCount, device);
}

Mesh::~Mesh()
{
	if (vertexBuffer) { vertexBuffer->Release(); }
	if (indexBuffer) { indexBuffer->Release(); }
}

ID3D11Buffer * Mesh::GetVertexBuffer()
{
	return vertexBuffer;
}

ID3D11Buffer * Mesh::GetIndexBuffer()
{
	return indexBuffer;
}

int Mesh::GetIndexCount()
{
	return indexCount;
}

void Mesh::CreateBasicGeometry(Vertex * vertices, int vertexCount, int * indices, int indexCount, ID3D11Device * device)
{

		CreateMesh();
		//creating vertex buffer description
		D3D11_BUFFER_DESC vbd;
		vbd.Usage = D3D11_USAGE_IMMUTABLE;
		vbd.ByteWidth = sizeof(Vertex) * 3; //3 is no. of vertices
		vbd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		vbd.CPUAccessFlags = 0;
		vbd.MiscFlags = 0;
		vbd.StructureByteStride = 0;

		// Create the proper struct to hold the initial vertex data
		// - This is how we put the initial data into the buffer
		D3D11_SUBRESOURCE_DATA initialVertexData;
		initialVertexData.pSysMem = vertices;

		// Actually create the buffer with the initial data
		// - Once we do this, we'll NEVER CHANGE THE BUFFER AGAIN
		device->CreateBuffer(&vbd, &initialVertexData, &vertexBuffer);


		//Index buffer desc
		D3D11_BUFFER_DESC ibd;

		//We end up going with D3D11_USAGE_IMMUTABLE, which signifies that we’ll never change the data stored in the buffer, and that the buffer will be read only by the GPU. 
		//This is one of the fastest options, resulting in the drivers storing the data directly in GPU memory
		ibd.Usage = D3D11_USAGE_IMMUTABLE;
		ibd.ByteWidth = sizeof(int) * 3; //no. of indices
		ibd.BindFlags = D3D11_BIND_INDEX_BUFFER;
		ibd.CPUAccessFlags = 0;
		ibd.MiscFlags = 0;
		ibd.StructureByteStride = 0;

		D3D11_SUBRESOURCE_DATA initialIndexData;
		initialIndexData.pSysMem = indices;

		device->CreateBuffer(&ibd, &initialIndexData, &indexBuffer);

}

void Mesh::CreateMesh()
{
	XMFLOAT4 red = XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f);
	XMFLOAT4 green = XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f);
	XMFLOAT4 blue = XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f);

	Vertex V1[]
	{
		{ XMFLOAT3(+1.0f,+2.0f,+0.0f), blue },
		{ XMFLOAT3(+3.0f, +2.0f, +0.0f), red },
		{ XMFLOAT3(+3.0f, +1.0f, +0.0f), blue },
		{ XMFLOAT3(+1.0f, +1.0f, +0.0f), green },
	};

	Vertex V2[]
	{
		{ XMFLOAT3(+1.0f, -1.0f, +0.0f), red },
		{ XMFLOAT3(+1.5f, -1.0f, +0.0f), blue },
		{ XMFLOAT3(+1.5f, -1.5f, +0.0f), green },
		{ XMFLOAT3(+1.0f, -1.5f, +0.0f), blue },

	};
	Vertex V3[]
	{
		{ XMFLOAT3(-1.0f, 2.0f, +0.0f), red },
		{ XMFLOAT3(+0.0f, +0.0f, +0.0f), blue },
		{ XMFLOAT3(-2.0f, 0.0f, +0.0f), green },

	};

	int indices[] = { 0,1,2,2,3,0 };

	

	
}



