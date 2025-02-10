#pragma once

#include "text.h"

namespace Sudsy {
	class Button : public Sudject {
		sudsy::Text text;
		Sudject parent;
		Vec2 pos;
		Vec2 size;
		Color color;
		Color hovercolor;
		Color clickcolor;
		bool IsHovered;
	public:
		Button();
		Button(std::string content);
		Button(std::string content, int size);
		Button(std::string content, int size, Color color);
		Button(std::string content, int size, Color color, Color hovercolor);
		Button(std::string content, int size, Color color, Color hovercolor, Color clickcolor);
		void SetFont(std::string font);
		void SetFontSize(int size);
		void SetFontColor(Color color);
		void SetFontShadow(bool shadow);
		void SetFontOutline(bool outline);
		void SetFontCentered(bool centered);
		void SetFontRightAligned(bool rightaligned);
		void SetFontOutlineColor(Color color);
		void SetFontShadowColor(Color color);
		void SetColor(Color color);
		void SetHoverColor(Color color);
		void SetClickColor(Color color);
		void SetHovered(bool hovered);
		void OnHover();
		void OnClick();
		void OnRelease();
		void OnClickOutside();
		void OnHoverOutside();
		void OnReleaseOutside();
		void OnClickInside();
		void OnHoverInside();
		void OnReleaseInside();
	};
}