#pragma once
#include <vector>
#include "ObjectHandler.h"

float Force(const float& m1, const float& m2, const float& r);
float Acc(const float& F, const float& m);
float FindAccX(PhysicalObject Obj1, PhysicalObject Obj2);
float FindAccY(PhysicalObject Obj1, PhysicalObject Obj2);
//float VDegCos(PhysicalObject Obj1, PhysicalObject Obj2, PhysicalObject Obj3);
//float FindSumAcc(float a1, float a2, float degreeCos);
void MoveObject(PhysicalObject &TargetObject, std::vector<PhysicalObject*> &ObjectReg);
void UpdatePhysics(std::vector<PhysicalObject*> &ObjectArray);
