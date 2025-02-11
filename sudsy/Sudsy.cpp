#include "Sudsy.h"


// Draws everything in context
void DoDraw() {

}

namespace Sudsy {
	void Initialize(sudsy::DX dxversion) {
		sudsy::Hook pEndScene(GetProcAddress(GetModuleHandleA("d3d9.dll"), "Direct3DCreate9"), &DoDraw);

		pEndScene.Init();

	}
}