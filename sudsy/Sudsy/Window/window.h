#pragma once
#include "ButtonList/ButtonList.h"

struct WindowProperties {
	bool HideButtons;
	bool Movable;
	bool Sizable;

};

namespace sudsy
{
	class Window : public Sudject
	{
	public:
		Window();
		Window(sudsy::Text t);
		Window(sudsy::Text t, Shape* shape);
		~Window();
	public:
		void Create();
		void Destroy();
		void SetTitle(sudsy::Text title);
		void SetSize(int width, int height);
		void SetPosition(int x, int y);
		void SetVisible(bool visible);
		void SetColor(Color col);
		void SetText(Text txt);
		void Draw();
		ScreenPos GetPos() {
			if (children.empty()) { return pd::SPZERO; }
			return GetChild(0)->GetPos();
		}
	private:
		sudsy::Text title;
		bool visible;
	};
}