#include <iostream>

#include "../sudsy/Sudsy/Sudsy.h"

void MainThread() {
	
	sudsy::Init();

	Vec2 start(0, 0);
	Vec2 end(100, 100);

	auto line = Shapes::Line(start, end, 100, 100);

}


// Defines DLLMain() which is required for Windows DLLs

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved) {
	switch (ul_reason_for_call) {
	case DLL_PROCESS_ATTACH:
		CreateThread(0, 0, (LPTHREAD_START_ROUTINE)MainThread, 0, 0, 0);
		break;
	case DLL_THREAD_ATTACH:
		break;
	case DLL_THREAD_DETACH:
		break;
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}