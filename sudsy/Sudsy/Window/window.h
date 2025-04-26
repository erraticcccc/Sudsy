#pragma once
#include "Checkbox/checkbox.h"

namespace sudsy
{
	class Window
	{
	public:
		Window();
		Window(std::string t);
		Window(std::string t, int w, int h);
		Window(std::string t, int w, int h, int posx, int posy);
		~Window();
	public:
		void Create();
		void Destroy();
		void SetTitle(sudsy::Text title);
		void SetSize(int width, int height);
		void SetPosition(int x, int y);
		void SetVisible(bool visible);
		void SetMinimized(bool minimized);
		void SetMaximized(bool maximized);
		void SetBorderless(bool borderless);
		void SetMovable(bool movable);
		void SetSizable(bool sizable);
		void SetMinSize(int width, int height);
		void SetMaxSize(int width, int height);
		void SetAlpha(int alpha);
		void SetColor(int x, int y, int z);
		void SetColor(Color col);
		void SetText(Text txt);
		bool IsMouseInWindow();
		void Draw();
	private:
		sudsy::Text title;
		int w, h, x, y;
		bool visible;
		bool minimized;
		bool maximized;
		bool borderless;
		bool movable;
		bool sizable;
		int minwidth;
		int minheight;
		int maxwidth;
		int maxheight;
		Color color;
	};
}