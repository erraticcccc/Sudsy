#include "../sudsy/Sudsy/Sudsy.h"

#if defined(_WIN32) && !defined(_WIN64)

#pragma comment(lib,"Win32/Debug/sudsy_x86.lib")

#elif defined(_WIN64)

#pragma comment(lib,"x64/Debug/sudsy_x64.lib")

#endif

void MainThread() {

	Color red(255, 0, 0, 255);
	Vec2  pos(30, 30);
	Vec2  pos2(450, 300);
	Vec2  offset(10, 0);

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
