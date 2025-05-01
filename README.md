```
#include "Sudsy.h"
#pragma comment(lib,"sudsy.lib")
```

Add this to any exe or dll, and you have access to an array of different rendering capabilities within any DirectX application.

Current Functionality:
 - Basic automation
	- DX9 Hooking
	- Object and rendering management
 - All basic shapes implemented
 - Text rendering

Heres an example:
```c++
#include "../sudsy/Sudsy/Sudsy.h"

#if defined(_WIN64)

#pragma comment(lib,"sudsy_x64.lib")

#elif defined(_WIN32)

#pragma comment(lib,"sudsy_x86.lib")

#endif

void MainThread() {

	Vec2  offset(300, 300);

	sudsy::Button button("flip");
	Shapes::Rectangle box(offset, offset + offset/4, Color(0, 255, 120, 170));
	
	button.SetShape(box);
	
	sudsy::AddHotkey(VK_INSERT, [&]() {
			button.SetVisible(!button.IsVisible());
		});

	int switcher = 0;
	button = ([&](sudsy::clicks c) {
			if (c == sudsy::lb) {
				Color col = button.GetColor();
				col.Set(col.r + switcher, col.g - switcher, col.b + (switcher * 2));
				button.SetTextColor(255 - (col.r % 255), 255 - (col.g % 255), 255 - (col.b % 255));
				button.SetColor(col);
			}
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

```

This example will create a small button, that changes color randomly upon clicking. The button can be hidden or shown using the 'Insert' key. 

What I need to do next:
- Finish class definitions
- Get more ideas for things
- Implement dragging for movable windows and sliders