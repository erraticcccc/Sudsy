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

	void Window::SetTitle(sudsy::Text title)
	{
		// Set window title
		this->title = title;
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
}