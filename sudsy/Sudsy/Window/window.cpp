#include "window.h"

namespace sudsy
{
	void Window::Draw() {

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
	}


	void Window::SetColor(Color col)
	{
	}
}