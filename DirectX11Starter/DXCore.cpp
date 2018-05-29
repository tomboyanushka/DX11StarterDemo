#include "DXCore.h"
#include <WindowsX.h>
#include <sstream>

DXCore* DXCore::DXCoreInstance = 0;

LRESULT DXCore::WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	return DXCoreInstance->ProcessMessage(hWnd, uMsg, wParam, lParam);
}

DXCore::DXCore(
HINSTANCE hInstance,
char* titleBarText,
unsigned int windowWidth,
unsigned int windowHeight,
bool debugTitleBarStats)
{
	DXCoreInstance = this;

	// Save params
	this->hInstance = hInstance;
	this->titleBartext = titleBarText;
	this->width = windowWidth;
	this->height = windowHeight;
	this->titleBarStats = debugTitleBarStats;

	// Initialize fields
	fpsFrameCount = 0;
	fpsTimeElapsed = 0.0f;

	device = 0;
	context = 0;
	swapChain = 0;
	backBufferRTV = 0;
	depthStencilView = 0;

	// Query performance counter for accurate timing information
	__int64 perfFreq;
	QueryPerformanceFrequency((LARGE_INTEGER*)&perfFreq);
	perfCounterSeconds = 1.0 / (double)perfFreq;
}


DXCore::~DXCore()
{
	//release stuff.. but what?
	if (depthStencilView) { depthStencilView->Release(); }
	if (backBufferRTV) { backBufferRTV->Release(); }

	if (swapChain) { swapChain->Release(); }
	if (context) { context->Release(); }
	if (device) { device->Release(); }
}

LRESULT DXCore::ProcessMessage(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	return LRESULT();
}

HRESULT DXCore::InitWndow()
{
	WNDCLASS wndClass = {};
	wndClass.style = CS_HREDRAW | CS_VREDRAW;
	wndClass.lpfnWndProc = DXCore::WindowProc;
	wndClass.cbClsExtra = 0;
	wndClass.cbWndExtra = 0;
	wndClass.hInstance = hInstance;
	wndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndClass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wndClass.lpszMenuName = NULL;
	wndClass.lpszClassName = "Direct3DWindowClass";

	if (!RegisterClass(&wndClass))
	{
		DWORD error = GetLastError();
		if (error != ERROR_CLASS_ALREADY_EXISTS)
			return HRESULT_FROM_WIN32(error);
	}
	RECT clientRect;
	SetRect(&clientRect, 0, 0, width, height);
	AdjustWindowRect(&clientRect, WS_OVERLAPPEDWINDOW, false);

	RECT desktopRect;
	GetClientRect(GetDesktopWindow(), &desktopRect);
	int centeredX = (desktopRect.right / 2) - (clientRect.right / 2);
	int ceneteredY = (desktopRect.bottom / 2) - (clientRect.bottom / 2);

	hWnd = CreateWindow(
		wndClass.lpszClassName,
		titleBartext.c_str(),
		WS_OVERLAPPEDWINDOW,
		centeredX,
		ceneteredY,
		clientRect.right - clientRect.left,
		clientRect.bottom - clientRect.top,
		0,
		0,
		hInstance,
		0);

	if (hWnd == NULL)
	{
		DWORD error = GetLastError();
		return HRESULT_FROM_WIN32(error);
	}


	ShowWindow(hWnd, SW_SHOW);

	return S_OK;
}

