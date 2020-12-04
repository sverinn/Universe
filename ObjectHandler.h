#pragma once
#include <iostream>
#include <vector>

static int IdCounter = 0;

static class PhysicalObject
{
private:
	int Id;
	bool IsInitialized;
	float Mass;
	float Size;
	float X;
	float Y;
	float dX;
	float dY;
public:

	PhysicalObject()
	{
		Id = IdCounter++;
		IsInitialized = false;
		Mass = 1;
		Size = 1;
		X = 0.0;
		Y = 0.0;
		dX = 0.0;
		dY = 0.0;
	};

	PhysicalObject(int MouseX, int MouseY)
	{
		Id = IdCounter++;
		IsInitialized = true;
		Mass = 1000000;
		Size = 1;
		X = MouseX;
		Y = MouseY;
		dX = 0.0;
		dY = 0.0;
	};

	PhysicalObject(int MouseX, int MouseY, float InputMass)
	{
		Id = IdCounter++;
		IsInitialized = true;
		Mass = InputMass;
		Size = 1;
		X = MouseX;
		Y = MouseY;
		dX = 0.0;
		dY = 0.0;
	};

	PhysicalObject(int MouseX, int MouseY, float InputMass, float InputSize)
	{
		Id = IdCounter++;
		IsInitialized = true;
		Mass = InputMass;
		Size = InputSize;
		X = MouseX;
		Y = MouseY;
		dX = 0.0;
		dY = 0.0;
	};

	const float GetX()
	{
		return X;
	}

	const float GetY()
	{
		return Y;
	}

	const float GetdX()
	{
		return dX;
	}

	const float GetdY()
	{
		return dY;
	}

	void SetAcc(float NewdX, float NewdY)
	{
		dX = NewdX;
		dY = NewdY;
	}

	void SetX(float NewX)
	{
		X = NewX;
	}

	void SetY(float NewY)
	{
		Y = NewY;
	}

	const int GetID()
	{
		return Id;
	}


	void DecrID()
	{
		Id--;
	}

	void Echo()
	{
		std::cout << "Created object instance with"
			<< " ID " << Id
			<< ", Mass = " << Mass
			<< ", Size = " << Size
			<< " at [" << X << ", " << Y << "]." << std::endl;
	}

	const bool Init()
	{
		return IsInitialized;
	}

	void Initialize()
	{
		IsInitialized = true;
	}

	const float GetSize()
	{
		return Size;
	}

	const float GetMass()
	{
		return Mass;
	}

	const void ShowInfo()
	{
		std::cout << "Physical object with"
			<< " ID " << Id
			<< ", Mass = " << Mass
			<< ", Size = " << Size
			<< " at [" << X << ", " << Y << "]." 
			<< " dX = " << dX << ", dY = " << dY
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
		Id = -1;
	};
};