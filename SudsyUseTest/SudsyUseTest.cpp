#include <iostream>

#include "../sudsy/Sudsy/Sudsy.h"

void MainThread() {

	Color red(255, 0, 0, 255);

	Shapes::Rectangle rect(Vec2(95, 295), Vec2(505, 305));
	rect.SetColor(red);
	Shapes::Line line(Vec2(95, 300), Vec2(505, 300), 25.f, COLOR_WHITE);
	rect.AddChild(line);
	Shapes::Line child(Vec2(100, 300), Vec2(500, 300), 20.f, COLOR_BLACK);
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
