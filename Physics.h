#pragma once
#include <vector>
#include "Objects.h"

inline CType Force(const CType M1, const CType M2, const CType DistSq, const CType SizeSum);
inline CType DistSq(CType X1, CType Y1, CType Z1, CType X2, CType Y2, CType Z2);
void MoveObject(PhysicalObject& TargetObject, std::vector<PhysicalObject*>& ObjectReg, const int& timescale);
void UpdatePhysics(std::vector<PhysicalObject*>& ObjectReg, const int& timescale, bool HT);
