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

	Color blue(0, 0, 255, 40);
	Color green(0, 255, 120, 170);
	Vec2  pos(5, 5);
	Vec2  offset(300, 300);

	sudsy::Button button("flip");
	Shapes::Rectangle box(offset, offset + offset/4, green);
	
	sudsy::AddHotkey(VK_INSERT, [&]() {
		if (button.IsVisible()) {
			button.SetVisible(false);
		}
		else {
			button.SetVisible(true);
		}
		});

	button.SetShape(box);

	int switcher = 0;
	bool show = true;
	button = ([&](sudsy::clicks c) {
			if (c == sudsy::lb) {
				// nothing :)
			}
		});

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
