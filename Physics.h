#pragma once
#include <vector>
#include "ObjectHandler.h"

float Force(const float& m1, const float& m2, const float& r);
float Acc(const float& F, const float& m);
void MoveObject(PhysicalObject &TargetObject, std::vector<PhysicalObject*> &ObjectReg);
void UpdatePhysics(std::vector<PhysicalObject*> &ObjectArray);
