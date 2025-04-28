#include "../sudsy/Sudsy/Sudsy.h"

#if defined(_WIN64)

#pragma comment(lib,"sudsy_x64.lib")

#elif defined(_WIN32)

#pragma comment(lib,"sudsy_x86.lib")

#endif

void MainThread() {

	Color blue(0, 0, 255, 255);
	Color green(0, 255, 120, 255);
	Vec2  pos(0, 0);
	Vec2  offset(300, 300);

	Shapes::Rectangle box(offset, offset + offset,green);
	Shapes::Circle circle(offset,50,blue);
	circle.SetVisible(false);

	sudsy::Button button("Hello!", box);

	int switcher = 0;
	bool show = true;
	button.SetClickFunction([&](sudsy::clicks c) {
			if (c == sudsy::lb) {
				if (switcher) {
					button.SetShape(circle);
					box.SetVisible(false);
					circle.SetVisible(true);
					switcher = 0;
				}
				else {
					button.SetShape(box);
					circle.SetVisible(false);
					box.SetVisible(true);
					switcher = 1;
				}
			}
			if (c == sudsy::rb) {
				if (show) {
					button.SetVisible(true);
					show = false;
				}
				else {
					button.SetVisible(false);
					show = true;
				}
			}
		});

	sudsy::Init();

	while (true) {
		box.SetColor(green);
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
