#pragma once
#include "text.h"
#include "button.h"

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
		void Render();
		void SetTitle(std::string title);
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
		void SetAlpha(float alpha);
		void SetColor(float r, float g, float b);
		void SetColor(Color col);
		void SetText(Text txt);
		bool IsMouseInWindow();
	private:
		std::string title;
		int width;
		int height;
		int x;
		int y;
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
		std::vector <sudsy::Text> text;
		std::vector <sudsy::Button> buttons;
	};
}