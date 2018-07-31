#pragma once
#include <DirectXMath.h>
#include "Mesh.h"
#include "SImpleShader.h"


using namespace DirectX;

class GameEntity
{


public:
	GameEntity(Mesh *mesh);
	~GameEntity();

	SimpleVertexShader* vertexShader;
	SimplePixelShader* pixelShader;

	void SetTranslation(XMFLOAT3 setPos);
	void SetScale(XMFLOAT3 setScale);
	void SetRotation(float setRotation);

	void Move(float position);
	Mesh* GetMesh();
	XMFLOAT4X4 GetMatrix();

	

private:

	XMFLOAT4X4 worldMatrix;
	XMFLOAT3 position;
	XMFLOAT3 rotation;
	XMFLOAT3 scale;
	Mesh* meshObject;



};

