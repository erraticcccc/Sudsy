#include "../sudsy/Sudsy/Sudsy.h"

#if defined(_WIN64)

#pragma comment(lib,"sudsy_x64.lib")

#elif defined(_WIN32)

#pragma comment(lib,"sudsy_x86.lib")

#endif

void MainThread() {

	Vec2  offset(300, 300);

	Shapes::Rectangle box(offset, offset + offset/4, Color(0, 255, 120, 170));
	
	sudsy::Button button("flip",box);
	button.SetMoveable(true);

	int switcher = 0;
	button.SetClickFunction([&](sudsy::clicks c) {
			if (c == sudsy::lb) {
				Color col = button.GetColor();
				col.Set(col.r + switcher, col.g - switcher, col.b + (switcher * 2));
				button.SetTextColor(255 - (col.r % 255), 255 - (col.g % 255), 255 - (col.b % 255));
				button.SetColor(col);
			}
			if (c == sudsy::rb) {
				button.SetMoveable(!button.IsMoveable());
			}
		});

	sudsy::AddHotkey(VK_INSERT, [&]() {
			button.SetVisible(!button.IsVisible());
		});

	sudsy::Init();

	while (true) {
		switcher++;
		switcher %= 500;
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
