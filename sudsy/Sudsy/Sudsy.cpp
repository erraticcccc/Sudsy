#include "Sudsy.h"

typedef HRESULT(__stdcall* EndScene)(IDirect3DDevice9* pDevice);
EndScene oEndScene;

void RenderScene();

void sudsy::Init() {
	IDirect3D9* pD3D = Direct3DCreate9(D3D_SDK_VERSION);

	if (!pD3D) {
		return;
	}

	D3DPRESENT_PARAMETERS d3dpp = { 0 };
	d3dpp.hDeviceWindow = GetForegroundWindow();
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.Windowed = TRUE;

	IDirect3DDevice9* pDevice = nullptr;

	pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, d3dpp.hDeviceWindow, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &pDevice);
		
	if (!pDevice) {
		d3dpp.Windowed = FALSE;
		pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, d3dpp.hDeviceWindow, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &pDevice);
	}

	if (!pDevice) {
		pD3D->Release();
		throw std::exception("Failed to create device");
		return;
	}

	auto pVTable = *reinterpret_cast<void***>(pDevice);

	// 3 fucking EndScenes: pEndScene (function location based off of vTable), oEndScene (original function), and HkEndScene (hook object)

	sudsy::Hook HkEndScene(pVTable[42], &RenderScene);

	HkEndScene.Init();

	while (Active) {
		Render();
	}
}

void sudsy::Render() {
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

void RenderScene() {

	sudsy::Render();

}