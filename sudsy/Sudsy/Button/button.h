#pragma once

#include "Text/text.h"
#include <functional>

namespace sudsy {
	class Button : public Sudject {
		sudsy::Text text;
	public:
		std::function<void(sudsy::clicks)> Click = nullptr;
		std::function<void(sudsy::clicks)> Paint = [](sudsy::clicks = none) -> void {};
		Button() : text("") {}
		Button(std::string content) : text(content) {}
		Button(std::string content, Shape& shape) : text(content) {
			AddChild(shape);
		}
		Button(std::string content, Shape& shape, std::function<void(sudsy::clicks)> function) : text(content), Click(function) { AddChild(shape)->AddChild(text); }
		void SetShape(Shape& shape);
		Shape* GetShape() {
			if (!children.empty()) { return (Shape*)children[0]; }
		}
		Type GetType() { return S_BUTTON; }
		void Draw() {};
		bool Valid() { return (Click && Paint && GetChild(0)); }
		void SetClickFunction(std::function<void(sudsy::clicks)> f) { Click = f; }
		ScreenPos GetPos() { return GetChild(0)->GetPos(); }
		void SetVisible(bool vis) { visible = vis; }
	public:
		void operator=(std::string t) {
			text = t;
		}
		void operator=(int t) {
			text = t;
		}
		void operator=(std::function<void(sudsy::clicks)> rep) {
			Click = rep;
		}
	};
}