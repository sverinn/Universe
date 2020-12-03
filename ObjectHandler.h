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
	float cos;
	int Z;
public:

	PhysicalObject()
	{
		Id = IdCounter++;
		IsInitialized = false;
		Mass = 1;
		Size = 20;
		X = 0.0;
		Y = 0.0;
	};

	PhysicalObject(int MouseX, int MouseY)
	{
		Id = IdCounter++;
		IsInitialized = true;
		Mass = 10000000;
		Size = 20;
		X = MouseX;
		Y = MouseY;
		dX = 0.0;
		dY = 0.0;
		cos = 0.0;
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
		cos = 0.0;
	};

	float GetX()
	{
		return X;
	}

	float GetY()
	{
		return Y;
	}

	float GetdX()
	{
		return dX;
	}

	float GetdY()
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

	int GetID()
	{
		return Id;
	}

	void Echo()
	{
		std::cout << "Created object instance with"
			<< " ID " << Id
			<< ", Mass = " << Mass
			<< ", Size = " << Size
			<< " at [" << X << ", " << Y << "]." << std::endl;
	}

	bool Init()
	{
		return IsInitialized;
	}

	void Initialize()
	{
		IsInitialized = true;
	}

	float GetSize()
	{
		return Size;
	}

	float GetMass()
	{
		return Mass;
	}

	void ShowInfo()
	{
		std::cout << "Physical object with"
			<< " ID " << Id
			<< ", Mass = " << Mass
			<< ", Size = " << Size
			<< " at [" << X << ", " << Y << "]." 
			<< " dX = " << dX << ", dY = " << dY
			<< std::endl;
	}

	~PhysicalObject()
	{
	};
};