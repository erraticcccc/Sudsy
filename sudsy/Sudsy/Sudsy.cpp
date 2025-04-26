#include "Sudsy.h"

typedef HRESULT(__stdcall* EndScene)(IDirect3DDevice9* pDevice);
EndScene oEndScene;

HRESULT __stdcall RenderScene(IDirect3DDevice9* pDevice);

WNDPROC oWndProc;
LRESULT wndProc(HWND h, UINT msg, WPARAM wparam, LPARAM lparam) {
	if (msg == WM_LBUTTONDBLCLK)
		sudsy::test = msg;
	
	return CallWindowProc(oWndProc,h,msg,wparam,lparam);
}

void HookWndProc() {
	oWndProc = (WNDPROC)SetWindowLongPtr(sudsy::WHandle, GWLP_WNDPROC, (LONG_PTR)wndProc);
	if (!oWndProc) {
		sudsy::test = GetWindowThreadProcessId(sudsy::WHandle, NULL) == GetCurrentThreadId();
	}
}

void HookD3D9() {
	IDirect3D9* pD3D = Direct3DCreate9(D3D_SDK_VERSION);

	if (!pD3D) { return; }

	D3DPRESENT_PARAMETERS d3dpp = { 0 };
	d3dpp.hDeviceWindow = sudsy::WHandle = GetForegroundWindow();
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.Windowed = TRUE;

	pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, d3dpp.hDeviceWindow, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &Sudevice);

	if (!Sudevice) {
		d3dpp.Windowed = FALSE;
		pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, d3dpp.hDeviceWindow, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &Sudevice);
	}

	if (!Sudevice) {
		pD3D->Release();
		return;
	}

	auto pVTable = *reinterpret_cast<void***>(Sudevice);

#if defined(_WIN64)
	oEndScene = (EndScene)sudsy::hook.THook((BYTE*)pVTable[42], (BYTE*)&RenderScene, 15);
#elif defined(_WIN32)
	oEndScene = (EndScene)sudsy::hook.THook((BYTE*)pVTable[42], (BYTE*)&RenderScene, 7);
#endif

	Sudevice->Release();
	pD3D->Release();
}

void HookD3D10() {
	
}

void HookD3D11() {

}

void HookD3D12() {

}

void sudsy::Init() {
	if (GetModuleHandleA("d3d9.dll")) {
		HookD3D9();
	}
	if (GetModuleHandleA("d3d11.dll")) {
		HookD3D11();
	}
	if (GetModuleHandleA("d3d12.dll")) {
		HookD3D12();
	}
	HookWndProc();
}

void DrawChildren(const std::vector<Sudject*>& childvec) {
	for (auto& children : childvec) {
		if (!children->Valid()) { continue; }
		children->Draw();
		if (!children->GetChildren().empty()) {
			DrawChildren(children->GetChildren());
		}
	}
}

void sudsy::Render() {
	if (sudjects.empty()) { return; }
	std::sort(sudjects.begin(), sudjects.end(), [](Sudject* a, Sudject* b) {
		int depthA = 0, depthB = 0;
		for (Sudject* p = a; p->GetParent(); p = p->GetParent()) depthA++;
		for (Sudject* p = b; p->GetParent(); p = p->GetParent()) depthB++;
		return depthA < depthB; // Parents come before children
	});

	for (auto& suds : sudjects) {
		if (!suds->IsVisible()) { continue; }
		if (!suds->Valid()) { continue; }
		if (suds->GetParent()) { continue; }
		suds->Draw();
		if (!suds->GetChildren().empty()) {
			DrawChildren(suds->GetChildren());
		}
	}
}

void sudsy::Destroy() {
	sudsy::hook.ToggleHook();
}

void sudsy::UpdateMousePos() {
	// Obtain mousepos relative to window
	if (!sudsy::WHandle) { return; }
	GetCursorPos(&sudsy::MousePos);
	ScreenToClient(sudsy::WHandle, &sudsy::MousePos);
}

void sudsy::UpdateWindowPos() {
	if (!sudsy::WHandle) { return; }
	GetWindowRect(sudsy::WHandle, &sudsy::WPos);
}

HRESULT __stdcall RenderScene(IDirect3DDevice9* pDevice) {
	Sudevice = pDevice;

	sudsy::UpdateMousePos();
	sudsy::UpdateWindowPos();

	sudsy::Render();

	return oEndScene(pDevice);
}