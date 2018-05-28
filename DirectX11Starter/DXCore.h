#pragma once
#include <Windows.h>
#include <d3d11.h>
#include <string>
#pragma comment(lib, "d3d11.lib")

class DXCore
{
public:
	DXCore(
	HINSTANCE hInstance,
		char* titleBarText,
		unsigned int windowWidth,
		unsigned int windowHeight,
		bool debugTitleBarStats);
	~DXCore();

	static DXCore* DXCoreInstance;
	static LRESULT CALLBACK WindowProc(
		HWND hWnd,
		UINT uMsg,
		WPARAM wParam,
		LPARAM lParam);

protected:
	HINSTANCE	hInstance;

	//WindowProc sends it to ProcessMessage if something needs to be done
	LRESULT ProcessMessage(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

	HRESULT InitWndow(); //before we can initialize DirectX 
	HRESULT InitDirectX();
	HRESULT Run();
	void Quit();
	virtual void OnResize();

};

