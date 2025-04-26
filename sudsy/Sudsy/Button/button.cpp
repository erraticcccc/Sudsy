#include "button.h"

namespace sudsy {
	Button::Button() {
		parent = child = nullptr;
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
	void Button::SetColor(Color col) {
		this->color = col;
	}
	void Button::SetClickColor(Color color) {
		clickcolor = color;
	}
	void Button::SetHoverColor(Color color) {
		hovercolor = color;
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