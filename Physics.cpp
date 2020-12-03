#include "Constants.h"
#include "ObjectHandler.h"
#include <vector>
#include <SFML/System/Sleep.hpp>

float Force(const float &m1, const float &m2, const float &r)
{
	float Force = 0.0;
	Force = G * ((m1 * m2) / (r * r));
	return Force;
};

float Acc(const float &F, const float &m)
{
	float a = F / m;
	return a;
};
/*
float FindAcc(PhysicalObject Obj1, PhysicalObject Obj2)
{
	//for (auto i = 0; i < ObjectArray.size() - 1; i++)
	//{
		float Radius = sqrt(powf((Obj1.GetX() - Obj2.GetX()), 2) + powf((Obj1.GetY() - Obj2.GetY()), 2));
		float iForce = Force(Obj1.GetMass(), Obj2.GetMass(), Radius);
		return Acc(iForce, Obj1.GetMass());
	//}
};
*/
float FindAccX(PhysicalObject Obj1, PhysicalObject Obj2)
{
	float Radius = (Obj1.GetX() - Obj2.GetX());
	//if (Radius < 1)
	//	Radius = 1;
	float iForce = Force(Obj1.GetMass(), Obj2.GetMass(), Radius);
	return Acc(iForce, Obj1.GetMass());
};

float FindAccY(PhysicalObject Obj1, PhysicalObject Obj2)
{
	float Radius = (Obj1.GetY() - Obj2.GetY());
	//if (Radius < 1)
	//	Radius = 1;
	float iForce = Force(Obj1.GetMass(), Obj2.GetMass(), Radius);
	return Acc(iForce, Obj1.GetMass());
};

float FindRadius(PhysicalObject Obj1, PhysicalObject Obj2)
{
	float Radius = sqrt(powf((Obj1.GetX() - Obj2.GetX()), 2) + powf((Obj1.GetY() - Obj2.GetY()), 2));
	return Radius;
}

/*
float VDegCos(PhysicalObject Obj1, PhysicalObject Obj2)
{
	float aX = Obj2.GetX() - Obj1.GetX();
	float aY = Obj2.GetY() - Obj1.GetY();
	float bX = Obj1.GetX() - Obj2.GetX();
	float bY = Obj1.GetY() - Obj2.GetY();
	return acosf((aX * bX + aY * bY) / (sqrtf(powf(aX, 2) + powf(aY, 2)) * sqrtf(powf(bX, 2) * powf(bY, 2))));
};
*/

float FindSumAcc(float a1, float a2, float degreeCos)
{
	return a1 * a2 * degreeCos;
}

void MoveObject(PhysicalObject& TargetObject, std::vector<PhysicalObject*>& ObjectReg)
{
	float AccX = 0.0;
	float AccY = 0.0;
	float dX = 0.0;
	float dY = 0.0;
	float propX = 0.0;
	float propY = 0.0;
	float Radius = 0.0;
	bool movedX = false;
	bool movedY = false;
	
	for (PhysicalObject* iObject : ObjectReg)
	{
		if (iObject->GetID() != TargetObject.GetID())
		{
			
			//float a1 = FindAcc(TargetObject, *iObject);
			std::cout << "Acceleration of object with ID " << TargetObject.GetID()
				<< " towards the object with ID " << iObject->GetID()
				<< std::endl;

			Radius = FindRadius(TargetObject, *iObject);

			dX = acosf(FindAccX(TargetObject, *iObject) / Radius);
			dY = acosf(FindAccY(TargetObject, *iObject) / Radius);

			if (TargetObject.GetX() > iObject->GetX())
				dX = -dX;
			std::cout << "dX is " << dX << std::endl;

			if (TargetObject.GetY() > iObject->GetY())
				dY = -dY;
			std::cout << "dX is " << dX << std::endl;
			std::cout << "dY is " << dY << std::endl;
		}
	}


	if (TargetObject.GetX() > 0 && TargetObject.GetX() < 800)
	{
		TargetObject.SetAcc(TargetObject.GetdX() + (dX * timescale), TargetObject.GetdY());
		TargetObject.SetX(TargetObject.GetX() + TargetObject.GetdX() + (dX * timescale));
	}
	if (TargetObject.GetY() > 0 && TargetObject.GetY() < 600)
	{
		TargetObject.SetAcc(TargetObject.GetdX(), TargetObject.GetdY() + (dY * timescale));
		TargetObject.SetY(TargetObject.GetY() + TargetObject.GetdY() + (dY * timescale));
	}
}

void UpdatePhysics(std::vector<PhysicalObject*> &ObjectArray)
{
	if (ObjectArray.size() > 1)
		for (PhysicalObject* iObject : ObjectArray)
		{
			MoveObject(*iObject, ObjectArray);
			std::cout << "Physics updated." << std::endl;
			//sf::sleep(sf::milliseconds(100));
		}
};