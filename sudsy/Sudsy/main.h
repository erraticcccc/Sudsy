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
	class Hook;
	class Shader;
	class Text;
	class Button;
	class Image;
	class Checkbox;
	class Slider;
	class Entry;
	class Listbox;
	class Dropdown;
	class Colorpicker;
	class Groupbox;
	class Tab;
	class Panel;
	class Window;
	void Init();
	void Render();
	void Destroy();
	inline bool Active = false;
}