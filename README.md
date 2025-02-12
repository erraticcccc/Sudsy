```
#include "Sudsy.h"
#pragma comment(lib,"sudsy.lib")
```

Add this to any exe or dll, and you have access to an array of different rendering capabilities within any DirectX application.

Current Functionality:
 - Automatic DX9 hooking (EndScene)
 - Capable of drawing lines

Heres an example:
```c++
#include "Sudsy.h"
#pragma comment(lib,"sudsy_x86.lib")

int MainThread() {

	Color Rainbow(255);

	Shapes::Rectangle rect(Vec2(95, 295), Vec2(505, 305));
	Shapes::Line line(Vec2(100, 300), Vec2(500, 300), 25.f, COLOR_WHITE);
	rect.AddChild(line);
	Shapes::Line child(Vec2(100, 300), Vec2(500, 300), 15.f, COLOR_BLACK);
	line.AddChild(child);

	sudsy::Init();
	while (true) {
		Sleep(50);	
	}

    Sudsy::Destroy();
    // Easy cleanup

}
```

This example will compile, and upon injecting into any DirectX9 application, will draw a line, a black line with a white outline, from the around the top left quarter to near the middle.

What I need to do next:
- Add rendering context/tree (Choose how it iterates through objects to render them)
- Finish class definitions
- Implement actual object management
