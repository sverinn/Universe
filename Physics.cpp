#include "Constants.h"
#include "Objects.h"
#include <vector>
#include <mutex>

std::mutex ObjectPropertyMutex;

inline CType Force(const CType M1, const CType M2, const CType DistSq, const CType RadiusSum) //Calculate force between Object1 and Object2
{
	/*if (RadiusSum < EPS)
	{
		return 0;
	}
	else*/
	if (sqrtf(DistSq) < RadiusSum)
	{
		if ( DistSq < EPS)
			return 0;
		else
			return -((G * M1 * M2) / (RadiusSum * RadiusSum)) / M1;
		//return 0;
	}
	else
		return (G * M1 * M2) / DistSq;
};

inline CType DistSq(const CType X1, const CType Y1, const CType X2, const CType Y2)
{
	return (powf((X2 - X1), 2) + powf((Y2 - Y1), 2));
};

void MoveObject(PhysicalObject& TargetObject, std::vector<PhysicalObject*>& ObjectReg, const int& timescale)
{
	//Target object is the one we're moving during each iteration
	
	CType dX = 0.0; //Calculated dX increment
	CType dY = 0.0;	//Calculated dY increment
	CType tX = TargetObject.GetX(); //Target object X
	CType tY = TargetObject.GetY(); //Target object Y
	CType tdX = TargetObject.GetdX(); //Target object current dX
	CType tdY = TargetObject.GetdY(); //Target object current dY
	CType tMass = TargetObject.GetMass(); //Target object mass
	CType tSize = TargetObject.GetRadius(); //Target object size
	

	for (PhysicalObject* iObject : ObjectReg)
	{
		if (TargetObject.GetID() != iObject->GetID())
		{
			/*
			CType iX = iObject->GetX(); //Iterated object X
			CType iY = iObject->GetY(); //Iterated object Y
			CType iMass = iObject->GetMass(); //Iterated object Mass
			CType iSize = iObject->GetRadius(); //Target object size
			*/


			CType RSq = DistSq(TargetObject.GetX(), TargetObject.GetY(), iObject->GetX(), iObject->GetY()); //Square radius between TargetObject and iObject


			////--------SOME OLD CODE FOR MERGING & COLLISIONS-------/
			//if (sqrtf(RSq) < (TargetObject.GetRadius() + iObject->GetRadius()))
			//{
			//	TargetObject.SetAcc(-TargetObject.GetdX(), TargetObject.GetdY());
			//	iObject->SetAcc(-iObject->GetdX(), iObject->GetdY());

			//	iObject->SetAcc(iObject->GetdX(), -iObject->GetdY());
			//	TargetObject.SetAcc(TargetObject.GetdX(), -TargetObject.GetdY());
			//}
			//else

			{
				//CType F = Force(TargetObject.GetMass(), iObject->GetMass(), RSq, TargetObject.GetRadius() - iObject->GetRadius());

				//std::cout << "RadX: " << FindAccX(TargetObject, *iObject) / FindAccY(TargetObject, *iObject) / Radius << " RadY: " << FindAccY(TargetObject, *iObject) / FindAccX(TargetObject, *iObject) / Radius << std::endl;
				dX += 
					((iObject->GetX() - TargetObject.GetX())
					* Force(TargetObject.GetMass(), iObject->GetMass(), RSq, TargetObject.GetRadius() + iObject->GetRadius())
					* timescale)
					/ TargetObject.GetMass();
				dY += 
					((iObject->GetY() - TargetObject.GetY())
						* Force(TargetObject.GetMass(), iObject->GetMass(), RSq, TargetObject.GetRadius() + iObject->GetRadius())
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
}

void CheckCollisions(PhysicalObject& TargetObject, std::vector<PhysicalObject*>& ObjectReg, const int& timescale)
{

}

void ProcessPhysicsThread(int& iObjectID, int& iThread, const int& ThreadCount, std::vector<PhysicalObject*>& ObjectArray, const int& timescale)
{
	for (iObjectID; iObjectID < (int)(ObjectArray.size() / ThreadCount) * (iThread + 1) && iObjectID < ObjectArray.size(); iObjectID++)
	{
		//ObjectPropertyMutex.lock();
		MoveObject(*ObjectArray[iObjectID], ObjectArray, timescale);
		//ObjectPropertyMutex.unlock();
	}
}

void UpdatePhysics(std::vector<PhysicalObject*>& ObjectReg, const int& timescale, bool HT)
{
	const int ThreadCount = std::thread::hardware_concurrency() - 1;
	if (HT && ObjectReg.size() > ThreadCount)
	{
		std::vector<std::thread> Thread;
		int iObjectID = 0;
		for (int iThread = 0; iThread < ThreadCount;)
		{
			if (ObjectReg.size() > 1 && iObjectID < (int)(ObjectReg.size() / ThreadCount) * (iThread + 1) && iThread < ThreadCount && iObjectID < ObjectReg.size())
			{
				Thread.emplace_back([&]() {ProcessPhysicsThread(std::ref(iObjectID), iThread, ThreadCount, ObjectReg, timescale); });
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
	}
	else 
	{
		for (auto iObject : ObjectReg)
		{
			MoveObject(*iObject, ObjectReg, timescale);
		}
	}
};