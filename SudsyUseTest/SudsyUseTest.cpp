#include <iostream>

#include "../sudsy/Sudsy/Sudsy.h"

void MainThread() {
	
	Vec2 start(0, 0);
	Vec2 end(100, 100);
	auto line = Shapes::Line(start, end, 100, 100);
	
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
