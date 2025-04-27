```
#include "Sudsy.h"
#pragma comment(lib,"sudsy.lib")
```

Add this to any exe or dll, and you have access to an array of different rendering capabilities within any DirectX application.

Current Functionality:
 - Basic automation
	- DX9 Hooking
	- Object and rendering management
 - All basic shapes implemented
 - Text rendering

Heres an example:
```c++
#include "../sudsy/Sudsy/Sudsy.h"

#if defined(_WIN64)

#pragma comment(lib,"sudsy_x64.lib")

#elif defined(_WIN32)

#pragma comment(lib,"sudsy_x86.lib")

#endif

void MainThread() {

	Color blue(0, 0, 255, 255);
	Vec2  pos(300, 300);

	sudsy::Text example("example",13,blue);
	example.SetPos(pos);

	sudsy::Init();

	while (true) {
		Sleep(10);
	}

}

BOOL APIENTRY DllMain(HMODULE hModule, 
	DWORD  rfc,
	LPVOID lpr
)
{
	switch (rfc)
	{
	case DLL_PROCESS_ATTACH:
		CloseHandle(CreateThread(0, 0, (LPTHREAD_START_ROUTINE)MainThread, 0, 0, 0));
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}

```

This example will compile, and upon injecting into any DirectX9 application, will draw a line, a black line with a white outline, from the around the top left quarter to near the middle.

What I need to do next:
- Finish class definitions
- Implement proper WndProc hooking, or look into alternative method of capture mouse click/mouse pos.