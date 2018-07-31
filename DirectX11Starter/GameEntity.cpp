#include "GameEntity.h"


GameEntity::GameEntity(Mesh * mesh)
{

	this->meshObject = mesh;

	//delcarung the floats
	position = XMFLOAT3(1.0f, 1.0f, 0.0f);
	rotation = XMFLOAT3(0.0f, 0.0f, 0.0f);
	scale = XMFLOAT3(1.5f, 0.5f, 0.0f);

	GetMatrix();

}

GameEntity::~GameEntity()
{
}

void GameEntity::SetTranslation(XMFLOAT3 setPos)
{
	position = setPos;
}

void GameEntity::SetScale(XMFLOAT3 setScale)
{
	scale = setScale;
}

void GameEntity::SetRotation(float setRotation)
{
	rotation.z = setRotation;
}

void GameEntity::Move(float position)
{
}

Mesh * GameEntity::GetMesh()
{
	return meshObject;
}

XMFLOAT4X4 GameEntity::GetMatrix()
{
	//coverting them to vectors
	XMVECTOR vPosition = XMLoadFloat3(&position);
	XMVECTOR vRotation = XMLoadFloat3(&rotation);
	XMVECTOR vScale = XMLoadFloat3(&scale);

	//coverting to matrices
	XMMATRIX mPosition = XMMatrixTranslationFromVector(vPosition);
	XMMATRIX mRotation = XMMatrixRotationZ(rotation.z);
	XMMATRIX mScale = XMMatrixScalingFromVector(vScale);

	
	XMMATRIX wake = XMMatrixIdentity();

	//calculte world matrix
	XMMATRIX world = mPosition * mRotation * mScale;

	//storing the world matrix

	XMStoreFloat4x4(&worldMatrix, XMMatrixTranspose(world));

	return worldMatrix;
}
