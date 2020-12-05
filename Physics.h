#pragma once
#include <vector>
#include "ObjectHandler.h"

double Force(PhysicalObject& Obj1, PhysicalObject& Obj2, const double& DistSq);
double DistSq(PhysicalObject& Obj1, PhysicalObject& Obj2);
void MoveObject(PhysicalObject& TargetObject, std::vector<PhysicalObject*>& ObjectReg, const int& timescale);
void UpdatePhysics(std::vector<PhysicalObject*>& ObjectArray, const int& timescale);
