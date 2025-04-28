#include "../sudsy/Sudsy/Sudsy.h"

#if defined(_WIN64)

#pragma comment(lib,"sudsy_x64.lib")

#elif defined(_WIN32)

#pragma comment(lib,"sudsy_x86.lib")

#endif

int thing = 0;

void testClick(sudsy::clicks c) {
	if (c == sudsy::lb) {
		thing++;
	}
	if (c == sudsy::rb) {
		thing--;
	}
}

void MainThread() {

	Color blue(0, 0, 255, 255);
	Color green(0, 255, 120, 255);
	Color offgreen(0, 240, 170, 255);
	Vec2  pos(10, 10);
	Vec2  offset(300, 300);

	sudsy::Button button("Hello!");
	Shapes::Rectangle box(offset, offset + (offset/5), green);
	Shapes::Rectangle box2(pos, pos, blue);
	box.AddChild(box2);

	Shapes::Circle circle(offset,50,blue);

	circle.SetVisible(false);
	button.SetShape(box);

	int switcher = 0;
	bool show = true;
	button = ([&](sudsy::clicks c) {
			if (c == sudsy::lb) {
				if (switcher) {
					circle.SetVisible(true);
					box.SetVisible(false);
					button.SetShape(circle);
					switcher = 0;
				}
				else {
					box.SetVisible(true);
					circle.SetVisible(false);
					button.SetShape(box);
					switcher = 1;
				}
			}
			if (c == sudsy::rb) {
				if (show) {
					button.SetVisible(show);
					show = false;
				}
				else {
					button.SetVisible(show);
					show = true;
				}
			}
		});

	button = testClick;

	sudsy::Init();

	while (true) {
		box.SetColor(offgreen);
		button = thing;
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
