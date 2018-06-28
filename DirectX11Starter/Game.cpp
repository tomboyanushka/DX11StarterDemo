#include "Game.h"
#include "DirectXMath.h"


using namespace DirectX;

Game::Game(HINSTANCE hInstance) 
	: DXCore(
	hInstance,								//handle
	"DirectX Game (Good Lord Save Me)",		//text for Title Bar
	1280,									//width
	720,									//height
	true)									//show extra stats
{

	vertexBuffer = 0;
	indexBuffer = 0;
	vertexShader = 0;
	pixelShader = 0;

#if defined(DEBUG) || defined(_DEBUG)

	CreateConsoleWindow(500, 120, 32, 120);
	printf("Console window created successfully. Feel free to printf() here ");

#endif
}

//cleaning everything, even memory leaks
Game::~Game()
{

	if (vertexBuffer) { vertexBuffer->Release(); }
	if (indexBuffer) { indexBuffer->Release(); }

	delete vertexShader;
	delete pixelShader;
}

void Game::Init()
{
	LoadShaders();
	CreateMatrices();
	CreateBasicGeometry();

	//what kind of shape do you want to draw?
	context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

}



//Load shaders from compile shader object (.cso) 
//and send data to individual variables on GPU
void Game::LoadShaders()
{
	vertexShader = new SimpleVertexShader(device, context);
	vertexShader->LoadShaderFile(L"VertexShader.cso");

	pixelShader = new SimplePixelShader(device, context);
	pixelShader->LoadShaderFile(L"PixelShader.cso");
}

//initialized matrices necessary for geometry
void Game::CreateMatrices()
{
	//setting up the world matrix
	//transpose happens Because HLSL expects a different matrix than the DirectX Math Library
	XMMATRIX W = XMMatrixIdentity();
	XMStoreFloat4x4(&worldMatrix, XMMatrixTranspose(W));

	// view matrix
	XMVECTOR pos = XMVectorSet(0, 0, -5, 0);
	XMVECTOR dir = XMVectorSet(0, 0, 1, 0);
	XMVECTOR up = XMVectorSet(0, 1, 0, 0);
	XMMATRIX V = XMMatrixLookToLH(
		pos,
		dir,
		up);

	XMStoreFloat4x4(&viewMatrix, XMMatrixTranspose(V));

	//Projection Matrix
	XMMATRIX P = XMMatrixPerspectiveFovLH(
		0.25f * XM_PI,			//fov(field of view angle)
		(float)width / height,
		0.1f,
		100.0f);

	XMStoreFloat4x4(&projectionMatrix, XMMatrixTranspose(P));

}

void Game::OnResize()
{
	DXCore::OnResize();

	//update projection matrix since window size has changed
	XMMATRIX P = XMMatrixPerspectiveFovLH(
		0.25f * 3.1415926535f,
		(float)width / height,
		0.1f,
		100.0f);

	XMStoreFloat4x4(&projectionMatrix, XMMatrixTranspose(P));
}

void Game::Update(float deltaTime, float TotalTime)
{
	//quit if escape is hit
	if (GetAsyncKeyState(VK_ESCAPE))
		Quit();

}

void Game::Draw(float deltaTime, float TotalTime)
{

	//bg color
	const float color[4] = { 0.4f, 0.6f, 0.75f, 0.0f };

	//do this before drawing ANYTHING

	context->ClearRenderTargetView(backBufferRTV, color);
	context->ClearDepthStencilView(
		depthStencilView,
		D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL,
		1.0f,
		0);

	//send data to shader variables
	vertexShader->SetMatrix4x4("world", worldMatrix);
	vertexShader->SetMatrix4x4("view", viewMatrix);
	vertexShader->SetMatrix4x4("projection", projectionMatrix);

	//send to GPU
	vertexShader->CopyAllBufferData();

	//set vertex and pixel shaders to use for next Draw() call
	vertexShader->SetShader();
	pixelShader->SetShader();

	//set buffers in input assembler, do once for each object
	UINT stride = sizeof(Vertex);
	UINT offset = 0;
	context->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);
	context->IASetIndexBuffer(indexBuffer, DXGI_FORMAT_R32_UINT, 0);

	//finally do the actual drawing
	context->DrawIndexed(
		3,
		0,
		0);

	swapChain->Present(0, 0);

}

#pragma region Mouse Input

void Game::OnMouseDown(WPARAM buttonState, int x, int y)
{
	prevMousePos.x = x;
	prevMousePos.y = y;

	SetCapture(hWnd);
}

void Game::OnMouseUp(WPARAM buttonState, int x, int y)
{
	ReleaseCapture();
}

void Game::OnMouseMove(WPARAM buttonState, int x, int y)
{
	prevMousePos.x = x;
	prevMousePos.y = y;
}

void Game::OnMouseWheel(float wheelDelta, int x, int y)
{
	//add custom code for scrolling
}

//BASIC GEOMETRY TO DRAW -- FOR THIS CASE, A TRIANGLE

void Game::CreateBasicGeometry()
{
	XMFLOAT4 red = XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f);
	XMFLOAT4 green = XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f);
	XMFLOAT4 blue = XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f);

	Vertex vertices[] =
	{
		{ XMFLOAT3(+0.0f, +1.0f, 0.0f), red },
		{ XMFLOAT3(+1.5f, -1.0f, 0.0f), green },
		{ XMFLOAT3(-1.5f, -1.0f, 0.0f), blue },

	};

	int indices[] = { 0, 1, 2 };


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
	ibd.Usage = D3D11_USAGE_IMMUTABLE; //A resource that can only be read by the GPU. It cannot be written by the GPU, and cannot be accessed at all by the CPU. This type of resource must be initialized when it is created, since it cannot be changed after creation.
	ibd.ByteWidth = sizeof(int) * 3; //no. of indices
	ibd.BindFlags = D3D11_BIND_INDEX_BUFFER;
	ibd.CPUAccessFlags = 0;
	ibd.MiscFlags = 0;
	ibd.StructureByteStride = 0;

	D3D11_SUBRESOURCE_DATA initialIndexData;
	initialIndexData.pSysMem = indices;

	device->CreateBuffer(&ibd, &initialIndexData, &indexBuffer);

}



