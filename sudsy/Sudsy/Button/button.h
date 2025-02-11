#pragma once

#include "Text/text.h"

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
	public:
		sudsy::Text text;
		Button();
		Button(std::string content);
		Button(std::string content, float size);
		Button(std::string content, Vec2 size);
		Button(std::string content, float size, Color color);
		Button(std::string content, float size, Color color, Color hovercolor);
		Button(std::string content, float size, Color color, Color hovercolor, Color clickcolor);
		void SetColor(Color col);
		void SetClickColor(Color color);
		void SetHoverColor(Color color);
		void OnClick();
		void OnRelease();
		void Paint();
	};
}