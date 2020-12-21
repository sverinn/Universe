#include "Objects.h"

PhysicalObject::PhysicalObject()
{
	srand(clock());

	ID = IDCounter++;
	Mass = rand() % 10000000;
	Radius = pow(((Mass / (rand() % 20)) / 0.5236), 1 / 3) / 2;
	X = rand() % 100;
	Y = rand() % 100;
	dX = rand() % 2;
	dY = rand() % 2;
}

PhysicalObject::PhysicalObject(CType MouseX, CType MouseY)
{
		ID = IDCounter++;
		Mass = rand() % 10000000;
		Radius = pow(((Mass / (rand() % 20)) / 0.5236), 1 / 3) / 2;
		X = MouseX;
		Y = MouseY;
		dX = 0.0;
		dY = 0.0;
}

PhysicalObject::PhysicalObject(CType MouseX, CType MouseY, CType InputMass)
{
		ID = IDCounter++;
		Mass = InputMass;
		Radius = pow(((Mass / (rand() % 20)) / 0.5236), 1 / 3) / 2;
		X = MouseX;
		Y = MouseY;
		dX = 0.0;
		dY = 0.0;
}

PhysicalObject::PhysicalObject(CType MouseX, CType MouseY, CType InputMass, CType InputRadius)
{

	ID = IDCounter++;
	Mass = InputMass;
	Radius = InputRadius;
	X = MouseX;
	Y = MouseY;
	dX = 0.0;
	dY = 0.0;
}

PhysicalObject::PhysicalObject(CType MouseX, CType MouseY, CType InputMass, CType InputRadius, CType InputdX, CType InputdY)
{
		ID = IDCounter++;
		Mass = InputMass;
		Radius = InputRadius;
		X = MouseX;
		Y = MouseY;
		dX = InputdX;
		dY = InputdY;
}

PhysicalObject::PhysicalObject(CType MouseX, CType MouseY, CType InputMass, CType InputRadius, CType InputdX, CType InputdY, D3DXCOLOR InputRGBA)
{
	ID = IDCounter++;
	Mass = InputMass;
	Radius = InputRadius;
	X = MouseX;
	Y = MouseY;
	dX = InputdX;
	dY = InputdY;
	RGBA = InputRGBA;
}

const CType PhysicalObject::GetX()
{
	return X;
}

const CType PhysicalObject::GetY()
{
	return Y;
}

const CType PhysicalObject::GetdX()
{
	return dX;
}

const CType PhysicalObject::GetdY()
{
	return dY;
}

const CType PhysicalObject::GetRadius()
{
	return Radius;
}

const CType PhysicalObject::GetMass()
{
	return Mass;
}

D3DXCOLOR PhysicalObject::GetColor()
{
	return RGBA;
}

const int PhysicalObject::GetID()
{
	return ID;
}

void PhysicalObject::SetAcc(CType NewdX, CType NewdY)
{


	//if (abs(dX - NewdX) > EPS || abs(dY - NewdY) > EPS) return;
	//if (abs(NewdX) < 299792458.0)
	dX = NewdX;
	//else dX = 299792458.0;
	//if (abs(NewdY) < 299792458.0)
	dY = NewdY;
	//else dY = 299792458.0;
}

void PhysicalObject::SetPos(CType NewX, CType NewY)
{

	//if (!isinf(NewX) && abs(X - NewX) > EPS)
	X = NewX;
	//if (!isinf(NewY) && abs(Y - NewY) > EPS)
	Y = NewY;
}

void PhysicalObject::EchoCreate()
{
	std::cout << "Created object instance with"
		<< " ID " << ID
		<< ", Mass = " << Mass
		<< ", Radius = " << Radius
		<< " at [" << X << ", " << Y << "]." << std::endl;

}

const void PhysicalObject::ShowInfo()
{
	std::cout << "Physical object with"
		<< " ID " << ID
		<< ", Mass = " << Mass
		<< ", Radius = " << Radius
		<< " at [" << X << ", " << Y << "]."
		<< " dX = " << dX << ", dY = " << dY
		<< ", vertex at [" << (float)X << ", " << (float)Y << "]."
		<< std::endl;
}

void PhysicalObject::MergeWith(PhysicalObject iObject)
{
	Mass += iObject.Mass;
	Radius += iObject.Radius;
	dX = (dX + iObject.dX) / 2;
	dY = (dY + iObject.dY) / 2;
}

PhysicalObject::~PhysicalObject()
{
	ID = -1;
};