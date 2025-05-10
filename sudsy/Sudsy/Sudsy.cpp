#include "Sudsy.h"

typedef HRESULT(__stdcall* EndScene)(IDirect3DDevice9* pDevice);
EndScene oEndScene;

HRESULT __stdcall RenderScene(IDirect3DDevice9* pDevice);

inline sudsy::clicks click = sudsy::none;

ScreenPos original;
WNDPROC oWndProc = NULL;
LRESULT CALLBACK wndProc(HWND h, UINT code, WPARAM wparam, LPARAM lparam) {
	switch (code) {
		case WM_LBUTTONDOWN: {
			sudsy::MousePos = { (float)GET_X_LPARAM(lparam), (float)GET_Y_LPARAM(lparam) };
			if (sudsy::MouseDown) { break; }
			sudsy::MouseDown = true;
			click = sudsy::lb;
			sudsy::Button* b = sudsy::ProcessButtons();
			if (b) { b->Click(click); }
			break;
		}
		case WM_LBUTTONUP: {
			sudsy::MouseDown = false;
			break;
		}
		case WM_MOVE: {
			break;
		}
		case WM_MOUSEMOVE: {
			if (sudsy::MouseDown) {
				click = sudsy::lb;
				sudsy::Button* b = sudsy::ProcessButtons();
				if (!b) { break; }
				if (!b->IsMoveable()) { break; }
				Vec2 going = { (float)GET_X_LPARAM(lparam), (float)GET_Y_LPARAM(lparam) };
				Vec2 change = { going.x - sudsy::MousePos.x, going.y - sudsy::MousePos.y };
				b->Move(change);
				sudsy::MousePos = going;
			}
			break;
		}
		case WM_RBUTTONDOWN: {
			click = sudsy::rb;
			sudsy::Button* b = sudsy::ProcessButtons();
			if (b) { b->Click(click); }
			break;
		}
		case WM_MBUTTONDOWN: {
			click = sudsy::mb;
			sudsy::Button* b = sudsy::ProcessButtons();
			if (b) { b->Click(click); }
			break;
		}
		case WM_SIZE: {
			/*ScreenPos n = sudsy::UpdateWindowPos();
			n.start = n.left / original.left;
			n.end = { n.bottom / original.bottom,  };
			for (auto& shape : sudjects) {
				if (!shape->Valid()) { continue; }
				if (shape->GetType() != S_SHAPE) { continue; }
				Shape* sh = (Shape*)shape;
				sh->Rescale(n);
			}*/
			break;
		}
		default: {
			if (original.end.x == -500000) { original = sudsy::UpdateWindowPos(); }
			click = sudsy::none;
			break;
		}
	}

	if (code == WM_KEYDOWN) {
		sudsy::ProcessHotkey(wparam);
	}

	return CallWindowProc(oWndProc,h,code,wparam,lparam);
}

HWND hMainWindow;

BOOL CALLBACK EnumWindowsProc(HWND hWindow, LPARAM lpReserved)
{
	DWORD dwProcessID;
	GetWindowThreadProcessId(hWindow, &dwProcessID);

	if (dwProcessID != GetCurrentProcessId()) return true;
	if (GetWindow(hWindow, GW_OWNER) != NULL) return true;
	if (!IsWindowVisible(hWindow)) return true;

	hMainWindow = hWindow;
	return false;
}

bool GetMainWindow()
{
	if (IsWindow(hMainWindow)) return true;

	EnumWindows(EnumWindowsProc, 0);

	return IsWindow(hMainWindow);
}

void HookWndProc() {
	oWndProc = (WNDPROC)SetWindowLongPtr(sudsy::WHandle, GWLP_WNDPROC, (LONG_PTR)wndProc);
	if (!oWndProc) {
	}
}

void HookD3D9() {
	IDirect3D9* pD3D = Direct3DCreate9(D3D_SDK_VERSION);

	if (!pD3D) { return; }

	GetMainWindow();

	D3DPRESENT_PARAMETERS d3dpp = { 0 };
	d3dpp.hDeviceWindow = sudsy::WHandle = hMainWindow;
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
		if (!children->GetParent()->IsVisible()) { continue; }
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

	for (auto& sud : sudjects) {
		if (!sud->IsVisible()) { continue; }
		if (!sud->Valid()) { continue; }
		if (sud->GetParent()) { continue; }
		sud->Draw();
		if (!sud->GetChildren().empty()) {
			DrawChildren(sud->GetChildren());
		}
	}
}

void sudsy::Destroy() {
	sudsy::hook.ToggleHook();
}

ScreenPos sudsy::UpdateWindowPos() {
	RECT r;
	if (!sudsy::WHandle) { return { pd::VEC2ZERO, pd::VEC2ZERO }; }
	GetWindowRect(sudsy::WHandle, &r);
	ScreenPos p;
	p.start = { (float)r.left, (float)r.right };
	p.end = { (float)r.top, (float)r.bottom };
	return p;
}

sudsy::Button* sudsy::ProcessButtons() {
	if (sudjects.empty()) { return nullptr; } // Somethings wrong || there is no buttons anyway
	for (Sudject *& sud : sudjects) {
		if (!sud->Valid()) { continue; }
		if (!sud->IsVisible()) { continue; }
		if (sud->GetType() != S_BUTTON) { continue; }
		ScreenPos p = sud->GetPos();
		if (!sudsy::MousePos.Bounds(p.start, p.end)) { continue; }
		return (Button*)sud;
	}
	return nullptr;
}

inline std::map <int, std::function<void()>> CatchKeys;

void sudsy::AddHotkey(int key, std::function <void()> func) {
	CatchKeys[key] = std::move(func);
}

void sudsy::ProcessHotkey(int key) {
	auto f = CatchKeys.find(key);
	if (f != CatchKeys.end()) {
		f->second();
	}
}


HRESULT __stdcall RenderScene(IDirect3DDevice9* pDevice) {

	Sudevice = pDevice;

	if (!sudsy::WPos.left) { sudsy::UpdateWindowPos(); }

	sudsy::Render();

	return oEndScene(pDevice);
}