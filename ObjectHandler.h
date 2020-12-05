#pragma once
#include <iostream>
#include <vector>
#include "Constants.h"

static int IDCounter = 0;

static class PhysicalObject
{
private:
	int ID;
	double Mass;
	double Size;
	double X;
	double Y;
	double dX;
	double dY;
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

	PhysicalObject(double MouseX, double MouseY)
	{
		ID = IDCounter++;
		Mass = 1000000;
		Size = 1;
		X = MouseX;
		Y = MouseY;
		dX = 0.0;
		dY = 0.0;
	};

	PhysicalObject(double MouseX, double MouseY, double InputMass)
	{
		ID = IDCounter++;
		Mass = InputMass;
		Size = 1;
		X = MouseX;
		Y = MouseY;
		dX = 0.0;
		dY = 0.0;
	};

	PhysicalObject(double MouseX, double MouseY, double InputMass, double InputSize)
	{
		ID = IDCounter++;
		Mass = InputMass;
		Size = InputSize;
		X = MouseX;
		Y = MouseY;
		dX = 0.0;
		dY = 0.0;
	};

	PhysicalObject(double MouseX, double MouseY, double InputMass, double InputSize, double InputdX, double InputdY)
	{
		ID = IDCounter++;
		Mass = InputMass;
		Size = InputSize;
		X = MouseX;
		Y = MouseY;
		dX = InputdX;
		dY = InputdY;
	};

	const double GetX()
	{
		return X;
	}

	const double GetY()
	{
		return Y;
	}

	const double GetdX()
	{
		return dX;
	}

	const double GetdY()
	{
		return dY;
	}

	void SetAcc(double NewdX, double NewdY)
	{
		if (abs(NewdX) < 299792458.0 && abs(dX - NewdX) >= EPS)
			dX = NewdX;
		if (abs(NewdY) < 299792458.0 && abs(dY - NewdY) >= EPS)
			dX = NewdY;
	}

	void SetX(double NewX)
	{
		if (!isinf(NewX) && abs(X - NewX) >= EPS)
			X = NewX;
	}

	void SetY(double NewY)
	{
		if (!isinf(NewY) && abs(Y - NewY) >= EPS)
			Y = NewY;
	}

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

	const double GetSize()
	{
		return Size;
	}

	const double GetMass()
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