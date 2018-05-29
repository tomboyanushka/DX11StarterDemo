#pragma once
#include <Windows.h>
#include <WindowsX.h>
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
	static LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

	//WindowProc sends it to ProcessMessage if something needs to be done
	LRESULT ProcessMessage(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

	HRESULT InitWndow(); //before we can initialize DirectX 
	HRESULT InitDirectX();
	HRESULT Run();
	/*void Quit();
	virtual void OnResize();*/

	virtual void Init() = 0;
	virtual void Update(float deltaTime, float totalTime) = 0;
	virtual void Draw(float deltaTime, float totalTime) = 0;

	virtual void OnMouseDown(WPARAM buttonState, int x, int y) { }
	virtual void OnMouseUp(WPARAM buttonState, int x, int y) { }
	virtual void OnMouseMove(WPARAM buttonState, int x, int y) { }
	virtual void OnMouseWheel(float wheelDelta, int x, int y) { }


protected:
	HINSTANCE	hInstance;
	HWND hWnd;
	std::string titleBartext;
	bool titleBarStats;

	unsigned int width;
	unsigned int height;

	D3D_FEATURE_LEVEL		dxFeatureLevel;
	IDXGISwapChain*			swapChain;
	ID3D11Device*			device;
	ID3D11DeviceContext*	context;

	ID3D11RenderTargetView* backBufferRTV;
	ID3D11DepthStencilView* depthStencilView;

	void CreateConsoleWindow(int bufferLines, int bufferColumns, int windowLines, int windowColumns);


private:
	// Timing related data
	double perfCounterSeconds;
	float totalTime;
	float deltaTime;
	__int64 startTime;
	__int64 currentTime;
	__int64 previousTime;

	// FPS calculation
	int fpsFrameCount;
	float fpsTimeElapsed;

	void UpdateTimer();			// Updates the timer for this frame
	void UpdateTitleBarStats();
	

};

