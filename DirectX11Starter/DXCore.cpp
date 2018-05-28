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
}


DXCore::~DXCore()
{
	//release stuff.. but what?
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
}

