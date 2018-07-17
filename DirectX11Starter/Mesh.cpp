#pragma once
#include "Mesh.h"




Mesh::Mesh()
{

}

void Mesh::CreateBasicGeometry(Vertex * vertices, int vertexCount, int * indices, int indexCount, ID3D11Device * device)
{
	//initializing is important apparently
	vertexBuffer = 0;
	indexBuffer = 0;
	this->indexCount = indexCount;

	//creating vertex buffer description
	D3D11_BUFFER_DESC vbd;
	vbd.Usage = D3D11_USAGE_IMMUTABLE;
	vbd.ByteWidth = sizeof(Vertex) * vertexCount; //3 is no. of vertices
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
	ibd.ByteWidth = sizeof(int) * indexCount; //no. of indices
	ibd.BindFlags = D3D11_BIND_INDEX_BUFFER;
	ibd.CPUAccessFlags = 0;
	ibd.MiscFlags = 0;
	ibd.StructureByteStride = 0;

	D3D11_SUBRESOURCE_DATA initialIndexData;
	initialIndexData.pSysMem = indices;

	device->CreateBuffer(&ibd, &initialIndexData, &indexBuffer);

}

Mesh::Mesh(Vertex * vertices, int vertexCount, int * indices, int indexCount, ID3D11Device * device)
{
	CreateBasicGeometry(vertices, vertexCount, indices, indexCount, device);
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


Mesh::~Mesh()
{
	if (vertexBuffer) { vertexBuffer->Release(); }
	if (indexBuffer) { indexBuffer->Release(); }
}

#pragma endregion

