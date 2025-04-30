#pragma once
#include "misc/Shape.h"

namespace sudsy
{
	// Sudsy is a DirectX wrapper that allows you to create all of the below objects within any directx application
	// Not really going to be useful for the time, only going to be making DX9 based
	enum DX {
		DX9,
		DX11,
		DX12
	};
	enum clicks {
		none = 0,
		lb,
		rb,
		mb
	};
	class Hook;
	class Shader;
	class Text;
	class Button;
	class Image;
	class Checkbox;
	class Slider;
	class ButtonList;
	class Dropdown;
	class Colorpicker;
	class Tab;
	class Window;
	inline Vec2 MousePos = { 0,0 };
	inline RECT WPos = { 0,0,0,0 };
	inline HWND WHandle = NULL;
	inline clicks MClick = none;
	inline int test = 0;
	void UpdateMousePos();
	void UpdateWindowPos();
	void ProcessButtons();
	void ProcessHotkey(int key);
	void AddHotkey(int key, std::function <void()> func);
	void Init();
	void Render();
	void Destroy();
	inline bool Active = false;
}