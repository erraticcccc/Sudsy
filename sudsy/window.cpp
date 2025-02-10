#include "window.h"

namespace sudsy
{
	Window::Window()
	{
		Window::Create();
	}

	Window::Window(std::string t)
	{
		Window::Create();
		title = t;
	}

	Window::Window(std::string t, int w, int h)
	{
		Window::Create();
		title = t;
		width = w;
		height = h;
	}

	Window::Window(std::string t, int w, int h, int posx, int posy)
	{
		Window::Create();
		title = t;
		width = w;
		height = h;
		x = posx;
		y = posy;
	}

	Window::~Window()
	{
		Destroy();
	}

	void Window::Create()
	{
		// Create window

	}

	void Window::Destroy()
	{
		// Destroy window
	}

	void Window::Render()
	{
		// Render window
	}

	void Window::SetTitle(std::string title)
	{
		// Set window title
	}

	void Window::SetSize(int width, int height)
	{
		// Set window size
	}

	void Window::SetPosition(int x, int y)
	{
		// Set window position
	}

	void Window::SetVisible(bool visible)
	{
		// Set window visibility
		Window::SetAlpha(visible ? 255.f : 0.f);
	}

	void Window::SetMinimized(bool minimized)
	{
		// Unlikely to be implemented
	}

	void Window::SetMaximized(bool maximized)
	{
		// Unlikely to be implemented
	}

	void Window::SetBorderless(bool borderless)
	{
		// Unlikely to be implemented
	}

	void Window::SetMovable(bool movable)
	{
	}

	void Window::SetSizable(bool sizable)
	{
	}

	void Window::SetMinSize(int width, int height)
	{
	}

	void Window::SetMaxSize(int width, int height)
	{
	}

	void Window::SetAlpha(float alpha)
	{
		color.a = alpha;
	}

	void Window::SetColor(float r, float g, float b)
	{
		color = Color(color.r, color.g, color.b);
	}

	void Window::SetColor(Color col)
	{
		color = col;
	}

	void Window::SetFont(std::string font)
	{
		text.SetFont(font);
	}

	void Window::SetFontSize(int size)
	{
		text.SetFontSize(size);
	}

	void Window::SetFontColor(float r, float g, float b)
	{
		text.SetFontColor(Color(r, g, b));
	}

	void Window::SetFontColor(Color col)
	{
		text.SetFontColor(col);
	}

	void Window::SetFontShadow(bool shadow)
	{
		text.SetFontShadow(shadow);
	}

	void Window::SetFontOutline(bool outline)
	{
		text.SetFontOutline(outline);
	}

	void Window::SetFontCentered(bool centered)
	{
		text.SetFontCentered(centered);
	}

	void Window::SetFontRightAligned(bool rightaligned)
	{
	}

	void Window::SetFontFlags(int flags)
	{
	}

	void Window::SetFontOffset(int x, int y)
	{
	}

	void Window::SetFontShadowOffset(int x, int y)
	{
	}

	void Window::SetFontOutlineOffset(int x, int y)
	{
	}

	void Window::SetFontCenteredOffset(int x, int y)
	{
	}

	void Window::SetFontRightAlignedOffset(int x, int y)
	{
	}

	void Window::SetFontShadowColor(float r, float g, float b)
	{
		text.SetFontShadowColor(Color(r, g, b));
	}

	void Window::SetFontShadowColor(Color col)
	{
		text.SetFontShadowColor(col);
	}

	void Window::SetFontOutlineColor(float r, float g, float b)
	{
		text.SetFontOutlineColor(Color(r, g, b));
	}

	void Window::SetFontOutlineColor(Color col)
	{
		text.SetFontOutlineColor(col);
	}

	void Window::SetFontShadowBlur(float blur)
	{
	}
	void Window::SetFontOutlineSpreadThickness(float thickness)
	{
	}
}