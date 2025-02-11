#include "Sudsy.h"
#pragma comment(lib,"sudsy.lib")

Add this to any exe or dll, and you have access to an array of different rendering capabilities within any DirectX application.

Current Functionality:
- Doesn't do anything yet.
- Class definitions for Window, Button, Text, and Hook have been outlined.
- General ideas for other classes have been put into the main namespace (sudsy::)
- General structure for how a project using Sudsy would look
  //
  int main()/MainThread() {
    Sudsy::Init();
    Sudsy::Window w("Title");
    Sudsy::Text* t = w.AddText("Text");
    Vec2 pos = t-> t->GetParent()->GetPos();
    t->SetPos(pos.x + 20, pos.y + 10);
    // Rendering automatic :)
    while (!GetAsyncKeyState(VK_INSERT) && 1) {
      if (GetAsyncKeyState(VK_F1) && 1) {
        Sudsy::Toggle();
      }
      continue;
    }
    Sudsy::Destroy();
    // Easy cleanup
  }
What I need to do next:
- Add rendering context/tree (Choose how it iterates through objects to render them)
- Finish class definitions
- Implement actual object management
