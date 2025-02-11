#include "button.h"

namespace sudsy {
	Button::Button() {
		parent = child = nullptr;
	}
	Button::Button(std::string content) {
		parent = child = nullptr;
		text = Text(content);
	}
	Button::Button(std::string content, float size) {
		parent = child = nullptr;
		text = Text(content);
		this->size = Vec2(size, size);
	}
	Button::Button(std::string content, Vec2 size) {
		parent = child = nullptr;
		text = Text(content);
		this->size = size;
	}
	Button::Button(std::string content, float size, Color color) {
		parent = child = nullptr;
		text = Text(content);
		this->size = Vec2(size, size);
		this->color = color;
	}
	Button::Button(std::string content, float size, Color color, Color hovercolor){
		parent = child = nullptr;
		text = Text(content);
		this->size = Vec2(size, size);
		this->color = color;
		this->hovercolor = hovercolor;
	}
	Button::Button(std::string content, float size, Color color, Color hovercolor, Color clickcolor){
		parent = child = nullptr;
		text = Text(content);
		this->size = Vec2(size, size);
		this->color = color;
		this->hovercolor = hovercolor;
		this->clickcolor = clickcolor;
	}
	void Button::SetColor(Color col) {
		this->color = col;
	}
	void Button::SetClickColor(Color color) {
		clickcolor = color;
	}
	void Button::SetHoverColor(Color color) {
		hovercolor = color;
	}
	void Button::OnClick() {
		toggle = !toggle;
		SetColor(clickcolor);
	}
	void Button::OnRelease() {
		SetColor(hovercolor);
	}
	void Button::Paint() {
		// Do GetMouseCursorPos and find if within bounds of button

		// if (parent == nullptr) { return; } // how??

		// if (parent.Visible() == false) { return; }

		// Paint



		// Requires more info relating to DX9 so its gonna wait :)))
		// if (!IsMouseInButton()) { return; }
		// Prevents logic of button from being executed if not in bounds, still paints

		// 

	}
}