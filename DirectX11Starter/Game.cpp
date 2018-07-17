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
	delete vertexShader;
	delete pixelShader;

	delete mesh1;
	delete mesh2;
	delete mesh3;
}

void Game::Init()
{
	LoadShaders();
	CreateMatrices();
	CreateMesh();
	

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

void Game::CreateMesh()
{
	XMFLOAT4 red = XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f);
	XMFLOAT4 green = XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f);
	XMFLOAT4 blue = XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f);


	Vertex V1[] =
	{

	//for mesh1
	{ XMFLOAT3(+1.0f, +2.0f, +0.0f), blue },
	{ XMFLOAT3(+3.0f, +2.0f, +0.0f), red },
	{ XMFLOAT3(+3.0f, +1.0f, +0.0f), blue },
	{ XMFLOAT3(+1.0f, +1.0f, +0.0f), green },
	};

	Vertex V2[] =
	{
	//for mesh2
	{ XMFLOAT3(+1.0f, -1.0f, +0.0f), red },
	{ XMFLOAT3(+1.5f, -1.0f, +0.0f), blue },
	{ XMFLOAT3(+1.5f, -1.5f, +0.0f), green },
	{ XMFLOAT3(+1.0f, -1.5f, +0.0f), blue },

	};
	Vertex V3[] =
	{
	//for mesh3
	{ XMFLOAT3(-1.0f, 2.0f, +0.0f), red },
	{ XMFLOAT3(+0.0f, +0.0f, +0.0f), blue },
	{ XMFLOAT3(-2.0f, 0.0f, +0.0f), green },

	};

	int indices[] = { 0, 1, 2, 2, 3, 0 };


	mesh1 = new Mesh(V1, 4, indices, 6, device);

	mesh2 = new Mesh(V2, 4, indices, 6, device);

	mesh3 = new Mesh(V3, 3, indices, 3, device);

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


//BASIC GEOMETRY TO DRAW -- FOR THIS CASE, A TRIANGLE


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

	DrawMesh(mesh1);
	DrawMesh(mesh2);
	DrawMesh(mesh3);

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

void Game::DrawMesh(Mesh* mesh)
{
	UINT stride = sizeof(Vertex);
	UINT offset = 0;
	auto vertexBuffer = mesh->GetVertexBuffer();
	context->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);
	context->IASetIndexBuffer(mesh->GetIndexBuffer(), DXGI_FORMAT_R32_UINT, 0);

	context->DrawIndexed(mesh->GetIndexCount(), 0, 0);
}


#pragma endregion


