#pragma once
#include "common.h"

struct Color {
	float r, g, b, a;
	Color() {
		r = g = b = a = 255.f;
	}
	Color(float _r, float _g, float _b, float _a = 255.f) {
		r = _r; g = _g; b = _b; a = _a;
	}
	Color(float z) {
		r = g = b = a = z;
	}
	void Set(float _r, float _g, float _b, float _a = 255.f) { r = _r; g = _g; b = _b; a = _a; }
	void Set(Color color) { r = color.r; g = color.g; b = color.b; a = color.a; }
 // TODO: Add operator overloads and clamp
};

struct Vec3 {
	float x, y, z;
	Vec3() {
		x = y = z = 0.f;
	}
	Vec3(float _x, float _y, float _z) {
		x = _x; y = _y; z = _z;
	}
};

struct Vec2 {
	float x, y;
	Vec2() {
		x = y = 0.f;
	}
	Vec2(float _x, float _y) {
		x = _x; y = _y;
	}
};

// Used as a base class for all objects, will be used for parent/child relationships
class Sudject {
	int sid; // used for render order and identification
};

Color COLOR_WHITE = Color(255.f, 255.f, 255.f, 255.f);
Color COLOR_BLACK = Color(0.f, 0.f, 0.f, 255.f);

namespace sudsy
{
	// Sudsy is a DirectX wrapper that allows you to create all of the below objects within any directx application
	class Shader;
	class Text; // Used in basically every class
	class Button;
	class Image;
	class Checkbox; // Builds off of button
	class Slider;
	class Entry; // Used for listbox
	class Listbox; // Used for dropdown as well as its own listbox
	class Dropdown;
	class Colorpicker;
	class Groupbox;
	class Tab;
	class Panel;
	class Window;
}