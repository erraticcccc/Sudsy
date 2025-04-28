#include "button.h"

namespace sudsy {
	void Button::SetShape(Shape& shape) {
		if (!GetChildren().empty()) { RemoveChild(0); }

		AddChild(shape)->AddChild(text);
	}
}