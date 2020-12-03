#include "Constants.h"
#include "ObjectHandler.h"
#include <vector>
#include <SFML/System/Sleep.hpp>
#include <cmath>

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
	float Radius = (Obj2.GetX() - Obj1.GetX());
	//if (Radius < 1)
	//	Radius = 1;
	float iForce = Force(Obj1.GetMass(), Obj2.GetMass(), Radius);
	return Acc(iForce, Obj1.GetMass());
};

float FindAccY(PhysicalObject Obj1, PhysicalObject Obj2)
{
	float Radius = (Obj2.GetY() - Obj1.GetY());
	//if (Radius < 1)
	//	Radius = 1;
	float iForce = Force(Obj1.GetMass(), Obj2.GetMass(), Radius);
	return Acc(iForce, Obj1.GetMass());
};

float FindRadius(PhysicalObject Obj1, PhysicalObject Obj2)
{
	float Radius = sqrt(powf((Obj2.GetX() - Obj1.GetX()), 2) + powf((Obj2.GetY() - Obj1.GetY()), 2));
	return Radius;
}

void MoveObject(PhysicalObject& TargetObject, std::vector<PhysicalObject*>& ObjectReg)
{
	float dX = 0.0;
	float dY = 0.0;
	float Radius = 0.0;
	
	for (PhysicalObject* iObject : ObjectReg)
	{
		if (iObject->GetID() != TargetObject.GetID())
		{
			
			//float a1 = FindAcc(TargetObject, *iObject);
			/*
			std::cout << "Acceleration of object with ID " << TargetObject.GetID()
				<< " towards the object with ID " << iObject->GetID()
				<< std::endl;
			*/

			Radius = FindRadius(TargetObject, *iObject);

			if ((TargetObject.GetSize() + iObject->GetSize()) > Radius)
			{
				std::cout << "Collision detected! ID " << TargetObject.GetID() << " & " << iObject->GetID() << std::endl;
				Radius = TargetObject.GetSize() + iObject->GetSize();
				continue;
			}

			std::cout << "RadX: " << FindAccX(TargetObject, *iObject) / FindAccY(TargetObject, *iObject) / Radius << " RadY: " << FindAccY(TargetObject, *iObject) / FindAccX(TargetObject, *iObject) / Radius << std::endl;
			dX = cos(FindAccX(TargetObject, *iObject)/ FindAccY(TargetObject, *iObject)/Radius)*timescale;
			dY = sin(FindAccY(TargetObject, *iObject)/ FindAccX(TargetObject, *iObject)/Radius)*timescale;
			std::cout << "Acceleration of object with ID " << TargetObject.GetID()
				<< " towards the object with ID " << iObject->GetID()
				<< " is dX: " << dX << " dY: " << dY
				<< std::endl;

			if (TargetObject.GetX() > iObject->GetX())
				dX = -dX;
			if (TargetObject.GetY() > iObject->GetY())
				dY = -dY;
		}
	}

	//if (TargetObject.GetX() > 0 && TargetObject.GetX() < ScreenWidth)
	{
		TargetObject.SetAcc(TargetObject.GetdX() + dX , TargetObject.GetdY());
		TargetObject.SetX(TargetObject.GetX() + TargetObject.GetdX() + dX);
	}
	//if (TargetObject.GetY() > 0 && TargetObject.GetY() < ScreenHeight)
	{
		TargetObject.SetAcc(TargetObject.GetdX(), TargetObject.GetdY() + dY);
		TargetObject.SetY(TargetObject.GetY() + TargetObject.GetdY() + dY);
	}


}

void UpdatePhysics(std::vector<PhysicalObject*> &ObjectArray)
{
	if (ObjectArray.size() > 1)
		for (PhysicalObject* iObject : ObjectArray)
		{
			MoveObject(*iObject, ObjectArray);
			//std::cout << "Physics updated." << std::endl;
			//sf::sleep(sf::milliseconds(1/timescale));
		}
};