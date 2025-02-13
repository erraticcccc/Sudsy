#include <iostream>

#include "../sudsy/Sudsy/Sudsy.h"

void MainThread() {

	Color red(255, 0, 0, 255);

	Shapes::Line line(Vec2(95, 300), Vec2(505, 300), 25.f, COLOR_WHITE);
	Shapes::Line child(Vec2(5, 0), Vec2(5, 0), 20.f, COLOR_BLACK);
	line.AddChild(child);

	sudsy::Init();
	while (true) {
		Sleep(50);	
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
