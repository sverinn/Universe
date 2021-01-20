#include <iostream>
#include "Graphics.h"
#include "Resources.h"
#include "Constants.h"

Graphics::Graphics(HWND g_hWnd)
{
	RECT rect;
	GetWindowRect(g_hWnd, &rect);

	g_iWidth = rect.right - rect.left;
	g_iHeight = rect.bottom - rect.top;

	g_pD3D = Direct3DCreate9(D3D_SDK_VERSION);

	//HRESULT hr = NULL;

	D3DDISPLAYMODE DisplayMode;
	g_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &DisplayMode);



	D3DPRESENT_PARAMETERS d3dpp;

	memset(&d3dpp, 0, sizeof(D3DPRESENT_PARAMETERS));
	d3dpp.BackBufferWidth = g_iWidth;
	d3dpp.BackBufferHeight = g_iHeight;
	d3dpp.BackBufferCount = 1;
	d3dpp.Windowed = TRUE;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.MultiSampleType = D3DMULTISAMPLE_NONE;
	d3dpp.MultiSampleQuality = 0;

	g_pD3D->CreateDevice(
		D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		g_hWnd,
		D3DCREATE_HARDWARE_VERTEXPROCESSING,
		&d3dpp,
		&d3dDevice);

	d3dDevice->SetRenderState(D3DRS_LIGHTING, TRUE);  // �� �� ����� ������������ ���������
	d3dDevice->SetRenderState(D3DRS_ZENABLE, FALSE); // � ����� ������� ����
}
/*
void Graphics::DrawCircle(int X, int Y, int radius, int numSides, DWORD Color)
{
	D3DXVECTOR2 Line[128];
	float Step = Pi * 2.0 / numSides;
	int Count = 0;
	for (float a = 0; a < Pi * 2.0; a += Step)
	{
		float X1 = radius * cos(a) + X;
		float Y1 = radius * sin(a) + Y;
		float X2 = radius * cos(a + Step) + X;
		float Y2 = radius * sin(a + Step) + Y;
		Line[Count].x = X1;
		Line[Count].y = Y1;
		Line[Count + 1].x = X2;
		Line[Count + 1].y = Y2;
		Count += 2;
	}
}
*/
Graphics::~Graphics()
{
	if (d3dDevice != NULL)
	{
		d3dDevice->Release();
		d3dDevice = NULL;
	}

	if (g_pD3D != NULL)
	{
		g_pD3D->Release();
		g_pD3D = NULL;
	}
}

IDirect3DDevice9* Graphics::pDevice()
{
	return d3dDevice;
}