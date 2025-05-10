#include "../sudsy/Sudsy/Sudsy.h"

#if defined(_WIN64)

#pragma comment(lib,"sudsy_x64.lib")

#elif defined(_WIN32)

#pragma comment(lib,"sudsy_x86.lib")

#endif

void MainThread() {

	Vec2 offset(300, 300);
	Vec2 offset2(1300, 500);
	Vec2 offset3(600, 200);
	Vec2 offset4(400, 800);
	Vec2 offset5(800, 1300);
	Vec2 offset6(1200, 1400);
	Vec2 offset7(900, 1300);
	Vec2 offset8(400, 1200);
	Vec2 ten(100, 100);
	Vec2 corner(0);

	Color red(255, 0, 0, 255);

	Shapes::Rectangle box1(offset, offset + ten, red);
	Shapes::Rectangle box2(offset2, offset2 + ten, red);
	Shapes::Rectangle box3(offset3, offset3 + ten, red);
	Shapes::Rectangle box4(offset4, offset4 + ten, red);
	Shapes::Rectangle box5(offset5, offset5 + ten, red);
	Shapes::Rectangle box6(offset6, offset6 + ten, red);
	Shapes::Rectangle box7(offset7, offset7 + ten, red);
	Shapes::Rectangle box8(offset8, offset8 + ten, red);
	sudsy::Text debuginfo("", corner, red);

	sudsy::Init();

	while (true) {
		debuginfo = ("Average Time: " + std::to_string(sudsy::avg));
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
