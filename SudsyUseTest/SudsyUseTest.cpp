#include "../sudsy/Sudsy/Sudsy.h"

void MainThread() {

	Color red(255, 0, 0, 255);
	Vec2  pos(300, 300);
	Vec2  pos2(450, 300);
	Vec2  offset(10,0);

	Shapes::Line ball(pos, pos2, 20, red);
	Shapes::Line core(offset, offset, 10, red + pd::COLOR_WHITE);
	ball.AddChild(core);

	sudsy::Init();

	int ballx = 0, bally = 0;
	bool xdir = true, ydir = true;

	while (true) {
		ball.start.bounds(1, 2559, ball.start.x, xdir);
		ball.start.bounds(1, 1439, ball.start.y, ydir);
		xdir ? ballx++ : ballx--;
		ydir ? bally++ : bally--;
		ball.start.Set(ballx * 3.f, bally * 2.f);
		ball.end.Set(ball.start.x + 150, ball.start.y);
		Sleep(5);
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
