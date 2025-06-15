#include "../sudsy/Sudsy/Sudsy.h"

#if defined(_WIN64)

#pragma comment(lib,"sudsy_x64.lib")

#elif defined(_WIN32)

#pragma comment(lib,"sudsy_x86.lib")

#endif

void MainThread() {

	Vec2 ten(100, 100);
	Vec2 corner(0);

	Color blue(0, 0, 255, 255);

	Shapes::Rectangle crosshairvert(ten,20,40,blue);
	crosshairvert.SetMoveable(true);

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
