#pragma once
#include <iostream>
#include <vector>
#include "Constants.h"
#include <d3dx9.h>


static int IDCounter = 0;

class PhysicalObject
{
private:
	int ID;
	CType Mass;
	CType Radius;
	CType X;
	CType Y;
	CType dX;
	CType dY;
	D3DXCOLOR RGBA;
public:

	PhysicalObject();
	PhysicalObject(CType MouseX, CType MouseY);
	PhysicalObject(CType MouseX, CType MouseY, CType InputMass);
	PhysicalObject(CType MouseX, CType MouseY, CType InputMass, CType InputRadius);
	PhysicalObject(CType MouseX, CType MouseY, CType InputMass, CType InputRadius, CType InputdX, CType InputdY);
	PhysicalObject(CType MouseX, CType MouseY, CType InputMass, CType InputRadius, CType InputdX, CType InputdY, D3DXCOLOR InputRGBA);

	const CType GetX();
	const CType GetY();
	const CType GetdX();
	const CType GetdY();
	const CType GetRadius();
	const CType GetMass();
	D3DXCOLOR GetColor();
	const int GetID();

	void SetAcc(CType NewdX, CType NewdY);
	void SetPos(CType NewX, CType NewY);

	void EchoCreate();
	const void ShowInfo();

	void MergeWith(PhysicalObject iObject);
	~PhysicalObject();
};