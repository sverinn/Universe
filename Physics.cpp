#include "Constants.h"
#include "ObjectHandler.h"
#include <vector>
#include <mutex>

std::mutex ObjectPropertyMutex;

double Force(PhysicalObject& Obj1, PhysicalObject& Obj2, const double& DistSq) //Calculate force between Object1 and Object2
{
	if ((DistSq) < pow((Obj1.GetSize() + Obj2.GetSize()), 2))
		return 0;
	else
		return G * Obj1.GetMass() * Obj2.GetMass() / DistSq;;
};

double DistSq(PhysicalObject& Obj1, PhysicalObject& Obj2)
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
	//ObjectPropertyMutex.lock();
	double dX = 0.0;
	double dY = 0.0;
	double Radius = 0.0;
	double tX = TargetObject.GetX();
	double tY = TargetObject.GetY();

	for (PhysicalObject* iObject : ObjectReg)
	{
		if (TargetObject.GetID() != iObject->GetID())
		{


			//int TObjectID = TargetObject.GetID();

			double iX = iObject->GetX();
			double iY = iObject->GetY();



			//float a1 = FindAcc(TargetObject, *iObject);
			/*
			std::cout << "Acceleration of object with ID " << TargetObject.GetID()
				<< " towards the object with ID " << iObject->GetID()
				<< std::endl;
			*/

			double RSq = DistSq(TargetObject, *iObject);

			/*
			bool EnableMerge = false;
			if (sqrtf(RSq) < (TargetObject.GetSize() + iObject->GetSize()))
			{
				if(EnableMerge)
					TargetObject.MergeWith(*iObject);
				std::cout << "Object " << iObject->GetID() << " collided with " << TargetObject.GetID() << std::endl;
				if (EnableMerge)
					if (ObjectReg.size() > 0)
					{
						for (int i = iObject->GetID() + 1; i < ObjectReg.size(); i++)
							ObjectReg[i]->DecrID();
						ObjectReg.erase(ObjectReg.begin() + iObject->GetID());
					}
				TargetObject.SetAcc(-TargetObject.GetdX(), TargetObject.GetdY());
				iObject->SetAcc(-iObject->GetdX(), iObject->GetdY());

				iObject->SetAcc(iObject->GetdX(), -iObject->GetdY());
				TargetObject.SetAcc(TargetObject.GetdX(), -TargetObject.GetdY());
			}
			else */
			{
				double F = Force(TargetObject, *iObject, RSq);

				//std::cout << "RadX: " << FindAccX(TargetObject, *iObject) / FindAccY(TargetObject, *iObject) / Radius << " RadY: " << FindAccY(TargetObject, *iObject) / FindAccX(TargetObject, *iObject) / Radius << std::endl;
				dX += ((iX - tX) * F) / TargetObject.GetMass();
				dY += ((iY - tY) * F) / TargetObject.GetMass();
			}
			
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

	//if (TargetObject.GetX() < 0 || TargetObject.GetX() > 1024)
	//	TargetObject.SetAcc(-TargetObject.GetdX(), TargetObject.GetdY());
	{
		TargetObject.SetAcc(TargetObject.GetdX() + dX , TargetObject.GetdY());
		TargetObject.SetX(tX + (TargetObject.GetdX() + dX) * timescale);
	}

	//if (TargetObject.GetY() < 0 || TargetObject.GetY() > 768)
	//	TargetObject.SetAcc(TargetObject.GetdX(), -TargetObject.GetdY());
	{
		TargetObject.SetAcc(TargetObject.GetdX(), TargetObject.GetdY() + dY);
		TargetObject.SetY(tY + (TargetObject.GetdY() + dY) * timescale);
	}

	//ObjectPropertyMutex.unlock();
}

void ProcessPhysicsThread(int& iObjectID, int& iThread, const int& CoreCount, std::vector<PhysicalObject*>& ObjectArray, const int& timescale)
{
	for (iObjectID; iObjectID < (int)(ObjectArray.size() / CoreCount) * (iThread + 1) && iObjectID < ObjectArray.size(); iObjectID++)
	{
		MoveObject(*ObjectArray[iObjectID], ObjectArray, timescale);
	}
}

void UpdatePhysics(std::vector<PhysicalObject*>& ObjectArray, const int& timescale)
{
	int CoreCount = std::thread::hardware_concurrency()-5;
	std::vector<std::thread> Thread;
	int iObjectID = 0;
	for (int iThread = 0; iThread < CoreCount;)
	{
		if (ObjectArray.size() > 1 && iObjectID < (int)(ObjectArray.size() / CoreCount) * (iThread + 1) && iThread < CoreCount && iObjectID < ObjectArray.size())
		{
			Thread.emplace_back([&]() {ProcessPhysicsThread(std::ref(iObjectID), iThread, CoreCount, ObjectArray, timescale); });
			//std::cout << "Created a new physics thread." << std::endl;
		}
		//std::cout << "Physics updated." << std::endl;
		//std::cout << "Creating a new thread, Thread " << iThread << " last object ID: " << iObjectID << std::endl;
		iThread++;
		continue;
	}
	for (auto& t : Thread)
	{
		t.join();
		//std::cout << "Joined a physics thread." << std::endl;
	}
};