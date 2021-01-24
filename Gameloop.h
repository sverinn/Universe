#pragma once
#include "Window.h"
#include "Objects.h"

void CreateRandomObject(Window& Wnd, std::vector<PhysicalObject*>& ObjectReg);
void CreateRandomObject(Window& Wnd, std::vector<PhysicalObject*>& ObjectReg, int X, int Y);
void CreateRandomObject(Window& Wnd, std::vector<PhysicalObject*>& ObjectReg, size_t particleCount);
void DoTick(Window& Wnd, std::vector<PhysicalObject*>& ObjectReg, CType timescale, bool HT);