#include "button.h"

namespace sudsy {
	void Button::SetClickColor(Color color) {
		clickcolor = color;
	}
	void Button::SetHoverColor(Color color) {
		hovercolor = color;
	}
	Type Button::GetType() { return S_BUTTON; }
	//void Button::Draw() { if (Paint) { Paint(none); } }
	bool Button::Valid() {
		return (Click && Paint && bShape);
	}
	void Button::SetVisible(bool vis) { visible = vis; }
}