#pragma once
#include "Windows.h"
#include <memory>
#include "Graphics.h"

class Window
{
private:
	class WindowClass
	{
	public:
		static const wchar_t* ClassName();
		static HINSTANCE Instance();
	private:
		HINSTANCE hInstance;
		static WindowClass wndClass;
		WindowClass();
		WindowClass(const WindowClass&) = delete;
		WindowClass operator=(const WindowClass&) = delete;
		~WindowClass();
		static constexpr const wchar_t* wndClassNameW = L"Universe";
	};
private:
	HWND g_hWnd;
	int g_iWindowWidth;
	int g_iWindowHeight;
	bool g_bApplicationState;
	std::unique_ptr<Graphics> pGfx;
private:

	static LRESULT CALLBACK HandleMsgSetup(HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam);
	static LRESULT CALLBACK HandleMsgThunk(HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam);
	LRESULT HandleMsg(HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam);
public:
	Window(int Width, int Height, LPCWSTR Name);
	Window(const Window&) = delete;
	Window& operator=(const Window&) = delete;
	~Window();
	Graphics& Gfx();
	MSG msg;
	int ProcessMessages();
	bool ApplicationState();
	HWND hWnd();
	int Width();
	int Height();
};

