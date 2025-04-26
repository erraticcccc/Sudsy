#include "../sudsy/Sudsy/Sudsy.h"

#if defined(_WIN64)

#pragma comment(lib,"sudsy_x64.lib")

#elif defined(_WIN32)

#pragma comment(lib,"sudsy_x86.lib")

#endif

void MainThread() {

	Color red(255, 0, 0, 255);
	Color blue(0, 0, 255, 255);
	Vec2  pos(300, 300);
	Vec2  tl(0);
	Vec2  br(0);

	sudsy::Text t("",13,red);
	sudsy::Text other("",13,blue);
	other.SetPos(pos);

	sudsy::Init();

	int hello = 0;
	while (true) {
		hello++;
		t = (int)sudsy::test;
		other = hello;

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
