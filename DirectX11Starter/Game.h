#pragma once
#include "DXCore.h"
#include "SimpleShader.h"
#include <DirectXmath.h>
#include "Vertex.h"
#include "Mesh.h"
#include "GameEntity.h"
#include "Camera.h"
#include "Lights.h"

using namespace DirectX;


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


	void DrawMesh(Mesh* mesh);


private:

	void LoadShaders();
	void CreateMatrices();
	void CreateMesh();
	
	

	ID3D11Buffer* vertexBuffer;
	ID3D11Buffer* indexBuffer;

	SimpleVertexShader* vertexShader;
	SimplePixelShader* pixelShader;

	XMFLOAT4X4 worldMatrix;
	XMFLOAT4X4 viewMatrix;
	XMFLOAT4X4 projectionMatrix;


	Mesh* chaletMesh;

	GameEntity* chaletEntity;

	Camera* camera;

	DirectionalLight light1;
	DirectionalLight light2;

	GameEntity* gameEntity1;
	GameEntity* gameEntity2;
	GameEntity* gameEntity3;
	GameEntity* gameEntity4;
	GameEntity* gameEntity5;

	void DrawEntity(GameEntity* gameEntityObject);

	POINT prevMousePos;
	

};

