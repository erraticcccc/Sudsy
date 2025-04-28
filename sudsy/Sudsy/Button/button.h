#pragma once

#include "Text/text.h"
#include <functional>

namespace sudsy {
	class Button : public Sudject {
		Shape*   bShape = nullptr;
		sudsy::Text text;
		Color hovercolor = pd::COLOR_WHITE;
		Color clickcolor = pd::COLOR_WHITE;
	public:
		std::function<void(sudsy::clicks)> Click = nullptr;
		std::function<void(sudsy::clicks)> Paint = [](sudsy::clicks = none) -> void {};
		Button() : text("") {}
		Button(std::string content) : text(content) {}
		Button(std::string content, Shape& shape) : text(content), bShape(&shape) { AddChild(*bShape); bShape->AddChild(text); }
		Button(std::string content, Shape& shape, std::function<void(sudsy::clicks)> function) : text(content), bShape(&shape), Click(function) { AddChild(*bShape); bShape->AddChild(text); }
		void SetClickColor(Color color);
		void SetHoverColor(Color color);
		void SetShape(Shape &shape) { bShape = &shape; }
		Type GetType();
		void Draw() {};
		bool Valid();
		void SetClickFunction(std::function<void(sudsy::clicks)> f) { Click = f; }
		ScreenPos GetPos() { return bShape->GetPos(); }
		void SetVisible(bool vis) ;
	};
}