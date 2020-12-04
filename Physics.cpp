#include "Constants.h"
#include "ObjectHandler.h"
#include <vector>

float Force(PhysicalObject& Obj1, PhysicalObject& Obj2, const float& DistSq) //Calculate force between Object1 and Object2
{
	if (sqrtf(DistSq) < (Obj1.GetSize() + Obj2.GetSize()))
		return 0;
	else
		return G * Obj1.GetMass() * Obj2.GetMass() / DistSq;;
};

float DistSq(PhysicalObject& Obj1, PhysicalObject& Obj2)
{
	return pow(Obj2.GetX() - Obj1.GetX(), 2) + pow(Obj2.GetY() - Obj1.GetY(), 2);
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
/*
float FindRadius(PhysicalObject Obj1, PhysicalObject Obj2)
{
	float Radius = (Obj2.GetX() - Obj1.GetX()) + (Obj2.GetY() - Obj1.GetY());
	return Radius;
}
*/

void MoveObject(PhysicalObject& TargetObject, std::vector<PhysicalObject*>& ObjectReg, const int& timescale)
{
	float dX = 0.0;
	float dY = 0.0;
	float Radius = 0.0;
	float tX = TargetObject.GetX();
	float tY = TargetObject.GetY();

	for (PhysicalObject* iObject : ObjectReg)
	{
		if (TargetObject.GetID() != iObject->GetID())
		{


			//int TObjectID = TargetObject.GetID();

			float iX = iObject->GetX();
			float iY = iObject->GetY();



			//float a1 = FindAcc(TargetObject, *iObject);
			/*
			std::cout << "Acceleration of object with ID " << TargetObject.GetID()
				<< " towards the object with ID " << iObject->GetID()
				<< std::endl;
			*/

			float RSq = DistSq(TargetObject, *iObject);
			if (sqrtf(RSq) < (TargetObject.GetSize() + iObject->GetSize()))
			{
				TargetObject.MergeWith(*iObject);
				if (ObjectReg.size() > 0)
				{
					for (int i = iObject->GetID()+1; i < ObjectReg.size(); i++)
						ObjectReg[i]->DecrID();
					ObjectReg.erase(ObjectReg.begin() + iObject->GetID());
				}
				return;
			}
			float F = Force(TargetObject, *iObject, RSq);

			//std::cout << "RadX: " << FindAccX(TargetObject, *iObject) / FindAccY(TargetObject, *iObject) / Radius << " RadY: " << FindAccY(TargetObject, *iObject) / FindAccX(TargetObject, *iObject) / Radius << std::endl;
			dX += (iX - tX) * F * timescale / TargetObject.GetMass();
			dY += (iY - tY) * F * timescale / TargetObject.GetMass();


			/*
			std::cout << "Acceleration of object with ID " << TargetObject.GetID()
				<< " towards the object with ID " << iObject->GetID()
				<< " is dX: " << dX << " dY: " << dY
				<< std::endl;
				*/
				/*
				if (TargetObject.GetX() > iObject->GetX())
					dX = -dX;
				if (TargetObject.GetY() > iObject->GetY())
					dY = -dY;
					*/
		}
	}

	//if (TargetObject.GetX() > 0 && TargetObject.GetX() < ScreenWidth)
	{
		TargetObject.SetAcc(TargetObject.GetdX() + dX , TargetObject.GetdY());
		TargetObject.SetX(tX + TargetObject.GetdX() + dX);
	}
	//if (TargetObject.GetY() > 0 && TargetObject.GetY() < ScreenHeight)
	{
		TargetObject.SetAcc(TargetObject.GetdX(), TargetObject.GetdY() + dY);
		TargetObject.SetY(tY + TargetObject.GetdY() + dY);
	}

}

void UpdatePhysics(std::vector<PhysicalObject*>& ObjectArray, const int& timescale)
{
	if (ObjectArray.size() > 1)
		for (PhysicalObject* iObject : ObjectArray)
		{
			MoveObject(*iObject, ObjectArray, timescale);
			//std::cout << "Physics updated." << std::endl;
		}
};