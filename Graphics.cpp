#include "stdafx.h"
#include <iostream>
#include "Graphics.h"
#include "Resources.h"

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

	d3dDevice->SetRenderState(D3DRS_LIGHTING, FALSE);  // Мы не будем использовать освещение
	d3dDevice->SetRenderState(D3DRS_ZENABLE, FALSE); // И буфер глубины тоже

	/*
	if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, g_hWnd,
		D3DCREATE_SOFTWARE_VERTEXPROCESSING,
		&d3dpp, &d3dDevice)))
		return E_FAIL;
	*/

}

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