#include "window.h"

namespace sudsy
{
	void Window::Draw() {

	}
	Window::Window()
	{
		Window::Create();
	}

	Window::Window(std::string t)
	{
		Window::Create();
		title = t;
	}

	Window::Window(std::string t, int width, int height)
	{
		Window::Create();
		title = t;
		this->w = w;
		this->h = h;
	}

	Window::Window(std::string t, int width, int height, int posx, int posy)
	{
		Window::Create();
		title = t;
		this->w = width;
		this->h = height;
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
		Window::SetAlpha(visible ? 255 : 0);
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

	void Window::SetAlpha(int alpha)
	{
		color.a = alpha;
	}

	void Window::SetColor(int x, int y, int z)
	{
		color = Color(x,y,z);
	}

	void Window::SetColor(Color col)
	{
		color = col;
	}
}