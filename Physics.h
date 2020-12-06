#pragma once
#include <vector>
#include "ObjectHandler.h"

inline CType Force(const CType M1, const CType M2, const CType DistSq, const CType SizeSum);
inline CType DistSq(CType X1, CType Y1, CType X2, CType Y2);
void MoveObject(PhysicalObject& TargetObject, std::vector<PhysicalObject*>& ObjectReg, const int& timescale);
void UpdatePhysics(std::vector<PhysicalObject*>& ObjectArray, const int& timescale, const int& CoreCount);
