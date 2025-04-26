#pragma once

#include "Text/text.h"

typedef bool (*bfunc)();

namespace sudsy {
	class Button : public Sudject {
		Sudject* parent;
		Sudject* child;
		Vec2 pos;
		Vec2 size;
		Color color;
		Color hovercolor;
		Color clickcolor;
		bool toggle;
		bfunc ClickFunction = nullptr;
	public:
		sudsy::Text text;
		Button();
		Button(std::string content) : parent(nullptr), child(nullptr), text(Text(content)) {}
		Button(std::string content, float size);
		Button(std::string content, Vec2 size);
		Button(std::string content, float size, Color color);
		void SetColor(Color col);
		void SetClickColor(Color color);
		void SetHoverColor(Color color);
		void Click() { if (ClickFunction != nullptr) { ClickFunction(); } };
		void Paint();
	};
}