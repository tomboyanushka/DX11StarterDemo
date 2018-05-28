#include "Main.h"
#include <Windows.h>
#include <crtdbg.h>



Main::Main()
{
}


Main::~Main()
{
}


int WINAPI WinMain(HINSTANCE hInstance,
					HINSTANCE hPrevInstance,
					LPSTR lpCmdLine,
					int nCmdShow)
{

	//MessageBox(NULL,
	//	"whatever",
	//	"whatever",
	//	MB_ICONEXCLAMATION | MB_OK);

#if defined(DEBUG) | defined(_DEBUG)
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif
	{
		char currentDir[1024] = {};
		GetModuleFileName(0, currentDir, 1024);
		char*lastSlash = strrchr(currentDir, '\\');
		if (lastSlash)
		{
			*lastSlash = 0;
			SetCurrentDirectory(currentDir);
		}
	}

	
}