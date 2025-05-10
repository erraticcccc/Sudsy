#pragma once

#include "Text/text.h"

namespace sudsy {
	class Button : public Sudject {
		sudsy::Text text;
	public:
		std::function<void(sudsy::clicks)> Click = nullptr;
		std::function<void(sudsy::clicks)> Paint = [](sudsy::clicks = none) -> void {};
		Button() : text("") {}
		Button(std::string content) : text(content) {}
		Button(std::string content, Shape& shape) : text(content) {
			SetShape(shape);
		}
		Button(std::string content, Shape& shape, Color& color) : text(content) {
			SetShape(shape);
			SetColor(color);
		}
		Button(std::string content, Shape& shape, std::function<void(sudsy::clicks)> function) : text(content), Click(function) { AddChild(shape)->AddChild(text); }
		void SetShape(Shape& shape);
		Shape* GetShape() { if (!children.empty()) { return (Shape*)children[0]; } else { return nullptr; } }
		Type GetType() { return S_BUTTON; }
		void Draw() {};
		bool Valid() { return (Click && Paint && GetChild(0)); }
		void SetPos(ScreenPos& dir) { GetShape()->SetPos(dir); }
		void Move(Vec2 dir) { GetShape()->Move(dir); }
		void SetClickFunction(std::function<void(sudsy::clicks)> f) { Click = f; }
		ScreenPos GetPos() { return GetShape()->GetPos(); }
		void SetVisible(bool vis) { visible = vis; }
		Color GetColor() { return GetShape()->GetColor(); }
		void SetColor(const Color& color) { GetShape()->SetColor(color); }
		void SetTextColor(const Color& color) { text.SetColor(color); }
		void SetTextColor(int r, int g, int b, int a = 255) { text.SetColor(r,g,b,a); }
		void SetTextAlignment(Alignment a) { text.SetAlignment(a); }
		void Rescale(ScreenPos& ratios) {
			GetShape()->Rescale(ratios);
		}
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