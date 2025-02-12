#include <iostream>

#include "../sudsy/Sudsy/Sudsy.h"

void MainThread() {

	Shapes::Line line(Vec2(100,100),Vec2(1200,1200),50.f,Color(255,0,0,255));

	sudsy::Hook hk;
	sudsy::Init(hk);
	while (true) {	Sleep(50);	}

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
