#include "Constants.h"
#include "ObjectHandler.h"
#include <vector>
#include <mutex>

std::mutex ObjectPropertyMutex;

inline CType Force(const CType M1, const CType M2, const CType DistSq, const CType SizeSum) //Calculate force between Object1 and Object2
{
	if (DistSq < (SizeSum * SizeSum))
		return -(G * M1 * M2 / (SizeSum * SizeSum)) / M1;
	else
		return G * M1 * M2 / DistSq;
};

inline CType DistSq(CType X1, CType Y1, CType X2, CType Y2)
{
	return ((X2 - X1) * (X2 - X1) + (Y2 - Y1) * (Y2 - Y1));
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
	//Target object is the one we're moving during this iteration
	ObjectPropertyMutex.lock();
	
	CType dX = 0.0; //Calculated dX increment
	CType dY = 0.0;	//Calculated dY increment
	CType tX = TargetObject.GetX(); //Target object X
	CType tY = TargetObject.GetY(); //Target object Y
	CType tdX = TargetObject.GetdX(); //Target object current dX
	CType tdY = TargetObject.GetdY(); //Target object current dY
	CType tMass = TargetObject.GetMass(); //Target object mass
	CType tSize = TargetObject.GetSize(); //Target object size
	

	for (PhysicalObject* iObject : ObjectReg)
	{
		if (TargetObject.GetID() != iObject->GetID())
		{
			/*
			CType iX = iObject->GetX(); //Iterated object X
			CType iY = iObject->GetY(); //Iterated object Y
			CType iMass = iObject->GetMass(); //Iterated object Mass
			CType iSize = iObject->GetSize(); //Target object size
			*/


			CType RSq = DistSq(TargetObject.GetX(), TargetObject.GetY(), iObject->GetX(), iObject->GetY()); //Square radius between TargetObject and iObject


			/*/--------SOME OLD CODE FOR MERGING & COLLISIONS-------/
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
				//CType F = Force(TargetObject.GetMass(), iObject->GetMass(), RSq, TargetObject.GetSize() - iObject->GetSize());

				//std::cout << "RadX: " << FindAccX(TargetObject, *iObject) / FindAccY(TargetObject, *iObject) / Radius << " RadY: " << FindAccY(TargetObject, *iObject) / FindAccX(TargetObject, *iObject) / Radius << std::endl;
				dX += 
					((iObject->GetX() - TargetObject.GetX())
					* Force(TargetObject.GetMass(), iObject->GetMass(), RSq, TargetObject.GetSize() - iObject->GetSize())
					* timescale)
					/ TargetObject.GetMass();
				dY += 
					((iObject->GetY() - TargetObject.GetY())
						* Force(TargetObject.GetMass(), iObject->GetMass(), RSq, TargetObject.GetSize() - iObject->GetSize())
						* timescale)
					/ TargetObject.GetMass();
			}

			/* /--------SOME OLD CODE FOR IMPACT-------/
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
	// Now that Universe calculated the velocities sum, we add it to the object current velocity

	TargetObject.SetAcc(TargetObject.GetdX() + dX, TargetObject.GetdY() + dY);
	TargetObject.SetPos(TargetObject.GetX() + TargetObject.GetdX() * timescale + dX, TargetObject.GetY() + TargetObject.GetdY() * timescale + dY);

	ObjectPropertyMutex.unlock();
}

void ProcessPhysicsThread(int& iObjectID, int& iThread, const int& ThreadCount, std::vector<PhysicalObject*>& ObjectArray, const int& timescale)
{
	for (iObjectID; iObjectID < (int)(ObjectArray.size() / ThreadCount) * (iThread + 1) && iObjectID < ObjectArray.size(); iObjectID++)
	{
		MoveObject(*ObjectArray[iObjectID], ObjectArray, timescale);
	}
}

void UpdatePhysics(std::vector<PhysicalObject*>& ObjectArray, const int& timescale, const int& ThreadCount)
{
	std::vector<std::thread> Thread;
	int iObjectID = 0;
	for (int iThread = 0; iThread < ThreadCount;)
	{
		if (ObjectArray.size() > 1 && iObjectID < (int)(ObjectArray.size() / ThreadCount) * (iThread + 1) && iThread < ThreadCount && iObjectID < ObjectArray.size())
		{
			Thread.emplace_back([&]() {ProcessPhysicsThread(std::ref(iObjectID), iThread, ThreadCount, ObjectArray, timescale); });
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