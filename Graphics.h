#pragma once
#include "stdafx.h"
#include "Resources.h"

class Graphics
{
public:
	Graphics(HWND hWnd);
	Graphics(const Graphics&) = delete;
	Graphics& operator = (const Graphics&) = delete;
	~Graphics();
	static Graphics Gfx;

	IDirect3DDevice9* pDevice();
	int Width() { return g_iWidth; };
	int Height() { return g_iHeight; };


	void DrawFrame(size_t VertexCount);
	void ClearBuffer(float Red, float Green, float Blue);
	void EndFrame();


private:
    IDirect3D9* g_pD3D = NULL;      //Интерфейс для создания устройства рендеринга
    IDirect3DDevice9* d3dDevice = NULL; //Устройство
	int g_iWidth;
	int g_iHeight;
};



