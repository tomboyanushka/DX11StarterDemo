#pragma once
#include "DXCore.h"
#include "SimpleShader.h"
#include <DirectXmath.h>
#include "Vertex.h"
#include "Mesh.h"


class Game : public DXCore

{
public:
	Game(HINSTANCE hInstance);
	~Game();

	void Init();
	void OnResize();
	void Update(float deltaTime, float TotalTime);
	void Draw(float deltaTime, float TotalTime);

	void OnMouseDown(WPARAM buttonState, int x, int y);
	void OnMouseUp(WPARAM buttonState, int x, int y);
	void OnMouseMove(WPARAM buttonState, int x, int y);
	void OnMouseWheel(float wheelDelta, int x, int y);


private:

	void LoadShaders();
	void CreateMatrices();
	void InitMesh();
	void DrawMesh(Mesh* mesh);
	

	ID3D11Buffer* vertexBuffer;
	ID3D11Buffer* indexBuffer;

	SimpleVertexShader* vertexShader;
	SimplePixelShader* pixelShader;

	DirectX::XMFLOAT4X4 worldMatrix;
	DirectX::XMFLOAT4X4 viewMatrix;
	DirectX::XMFLOAT4X4 projectionMatrix;


	Mesh* mesh1;
	Mesh* mesh2;
	Mesh* mesh3;
	POINT prevMousePos;
	

};

