#include <iostream>

#include "../sudsy/Sudsy/Sudsy.h"

void MainThread() {

	Color red(255, 0, 0, 255);

	Shapes::Line ball(Vec2(95, 300), Vec2(505, 300), 15.f, red);

	sudsy::Init();
	
	bool xdir = false, ydir = false;
	int ballx = 0, bally = 0;

	while (true) {
		ball.start.bounds(1, 1919, ball.start.x, xdir);
		ball.start.bounds(1, 1080, ball.start.y, ydir);
		xdir ? ballx++ : ballx--;
		ydir ? bally++ : bally--;
		ball.start.Set(ballx * 9.f, bally * 8.f);
		ball.end.Set(ball.start.x + 20, ball.start.y);
		Sleep(15);
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
