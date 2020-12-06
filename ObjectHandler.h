#pragma once
#include <iostream>
#include <vector>
#include "Constants.h"


static int IDCounter = 0;

static class PhysicalObject
{
private:
	int ID;
	CType Mass;
	CType Size;
	CType X;
	CType Y;
	CType dX;
	CType dY;
public:

	PhysicalObject()
	{
		ID = IDCounter++;
		Mass = 1;
		Size = 1;
		X = 0.0;
		Y = 0.0;
		dX = 0.0;
		dY = 0.0;
	};

	PhysicalObject(CType MouseX, CType MouseY)
	{
		ID = IDCounter++;
		Mass = 1000000;
		Size = 1;
		X = MouseX;
		Y = MouseY;
		dX = 0.0;
		dY = 0.0;
	};

	PhysicalObject(CType MouseX, CType MouseY, CType InputMass)
	{
		ID = IDCounter++;
		Mass = InputMass;
		Size = 1;
		X = MouseX;
		Y = MouseY;
		dX = 0.0;
		dY = 0.0;
	};

	PhysicalObject(CType MouseX, CType MouseY, CType InputMass, CType InputSize)
	{
		ID = IDCounter++;
		Mass = InputMass;
		Size = InputSize;
		X = MouseX;
		Y = MouseY;
		dX = 0.0;
		dY = 0.0;
	};

	PhysicalObject(CType MouseX, CType MouseY, CType InputMass, CType InputSize, CType InputdX, CType InputdY)
	{
		ID = IDCounter++;
		Mass = InputMass;
		Size = InputSize;
		X = MouseX;
		Y = MouseY;
		dX = InputdX;
		dY = InputdY;
	};

	const CType GetX()
	{
		return X;
	}

	const CType GetY()
	{
		return Y;
	}

	const CType GetdX()
	{
		return dX;
	}

	const CType GetdY()
	{
		return dY;
	}

	void SetAcc(CType NewdX, CType NewdY)
	{
		//if (abs(dX - NewdX) > EPS || abs(dY - NewdY) > EPS) return;
		//if (abs(NewdX) < 299792458.0)
			dX = NewdX;
		//else dX = 299792458.0;
		//if (abs(NewdY) < 299792458.0)
			dX = NewdY;
		//else dY = 299792458.0;
	}

	void SetPos(CType NewX, CType NewY)
	{
		//if (!isinf(NewX) && abs(X - NewX) > EPS)
			X = NewX;
		//if (!isinf(NewY) && abs(Y - NewY) > EPS)
			Y = NewY;
	}

	/*
	void SetY(CType NewY)
	{
		if (!isinf(NewY) && abs(Y - NewY) > EPS)
			Y = NewY;
	}
	*/

	const int GetID()
	{
		return ID;
	}


	void DecrID()
	{
		ID--;
	}

	void Echo()
	{
		std::cout << "Created object instance with"
			<< " ID " << ID
			<< ", Mass = " << Mass
			<< ", Size = " << Size
			<< " at [" << X << ", " << Y << "]." << std::endl;
	}

	const CType GetSize()
	{
		return Size;
	}

	const CType GetMass()
	{
		return Mass;
	}

	const void ShowInfo()
	{
		std::cout << "Physical object with"
			<< " ID " << ID
			<< ", Mass = " << Mass
			<< ", Size = " << Size
			<< " at [" << X << ", " << Y << "]."
			<< " dX = " << dX << ", dY = " << dY
			<< ", vertex at [" << (float)X << ", " << (float)Y << "]."
			<< std::endl;
	}

	void MergeWith(PhysicalObject iObject)
	{
		Mass += iObject.Mass;
		Size += iObject.Size;
		dX = (dX + iObject.dX) / 2;
		dY = (dY + iObject.dY) / 2;
	}

	~PhysicalObject()
	{
		ID = -1;
	};
};