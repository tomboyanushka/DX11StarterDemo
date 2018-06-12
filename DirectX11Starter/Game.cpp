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
}

void Game::Update(float deltaTime, float TotalTime)
{
}

void Game::Draw(float deltaTime, float TotalTime)
{
}

void Game::OnMouseDown(WPARAM buttonState, int x, int y)
{
}

void Game::OnMouseUp(WPARAM buttonState, int x, int y)
{
}

void Game::OnMouseMove(WPARAM buttonState, int x, int y)
{
}

void Game::OnMouseWheel(float wheelDelta, int x, int y)
{
}

void Game::CreateBasicGeometry()
{
}



