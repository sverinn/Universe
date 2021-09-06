#pragma once
#include "Window.h"

void CreateRandomObject(Window& Wnd, std::vector<PhysicalObject*>& ObjectReg);
void CreateRandomObject(Window& Wnd, std::vector<PhysicalObject*>& ObjectReg, int X, int Y);
void CreateRandomObject(Window& Wnd, std::vector<PhysicalObject*>& ObjectReg, size_t particleCount);
void CreateRandomObject(Window& Wnd, std::vector<PhysicalObject*>& ObjectReg, size_t particleCount);
void CreateRandomAcceleratedObject(Window& Wnd, std::vector<PhysicalObject*>& ObjectReg, size_t particleCount);