#include "../sudsy/Sudsy/Sudsy.h"

#if defined(_WIN64)

#pragma comment(lib,"sudsy_x64.lib")

#elif defined(_WIN32)

#pragma comment(lib,"sudsy_x86.lib")

#endif

void MainThread() {

	Vec2 ten(100, 100);
	Vec2 corner(0);

	Color red(255, 0, 0, 255);
	Color green(0, 255, 0, 255);
	Color blue(0, 0, 255, 255);

	Shapes::Rectangle r(ten, 50, 50, red);
	Shapes::Rectangle crosshairvert(pd::VEC2ZERO,2,40,red);
	Shapes::Rectangle crosshairhorz(pd::VEC2ZERO,40,2,red);

	r.SetMoveable(true);
	r.SetLockedToScreen(true);

	sudsy::Text debuginfo("", corner, pd::COLOR_WHITE);

	sudsy::Init();

	ScreenPos stupid;
	while (true) {
		stupid.start = sudsy::WRes/2;
		//debuginfo = sudsy::WRes;
		crosshairvert.SetPos(stupid);
		crosshairhorz.SetPos(stupid);
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
