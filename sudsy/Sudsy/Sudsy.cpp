#include "Sudsy.h"

typedef HRESULT(__stdcall* EndScene)(IDirect3DDevice9* pDevice);
EndScene oEndScene;

HRESULT __stdcall RenderScene(IDirect3DDevice9* pDevice);

void sudsy::Init(sudsy::Hook hk) {
	IDirect3D9* pD3D = Direct3DCreate9(D3D_SDK_VERSION);

	if (!pD3D) { return; }

	D3DPRESENT_PARAMETERS d3dpp = { 0 };
	d3dpp.hDeviceWindow = GetForegroundWindow();
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

	oEndScene = (EndScene)hk.THook((BYTE*)pVTable[42], (BYTE*)&RenderScene, 7);
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
		suds->Draw();
	}
}

void sudsy::Destroy() {

}

HRESULT __stdcall RenderScene(IDirect3DDevice9* pDevice) {
	Sudevice = pDevice;
	sudsy::Render();

	return oEndScene(pDevice);
}