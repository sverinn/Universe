#pragma once
#include "Window.h"
#include "Objects.h"

void CreateRandomObjects(Window& Wnd, std::vector<PhysicalObject*>& ObjectReg, size_t particleCount);
void DoTick(Window& Wnd, std::vector<PhysicalObject*>& ObjectReg, CType timescale, bool HT);