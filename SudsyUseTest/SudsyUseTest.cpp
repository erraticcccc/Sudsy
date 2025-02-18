#include "../sudsy/Sudsy/Sudsy.h"

#if defined(_WIN64)

#pragma comment(lib,"sudsy_x64.lib")

#elif defined(_WIN32)

#pragma comment(lib,"sudsy_x86.lib")

#endif

void MainThread() {

	Color red(255, 0, 0, 255);
	Color blue(0, 0, 255, 255);
	Color rainbow(255, 255, 255, 255);
	Vec2  pos(300, 300);
	
	Shapes::Circle circle(pos,150,red);
	Shapes::Circle circle2(pos,148,blue);
	Shapes::Circle circle3(pos,100,rainbow);

	sudsy::Init();

	float g = 0;
	while (true) {
		g++;
		rainbow.HSLToColor(g, 1, 0.4);
		circle3.SetColor(rainbow);
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
