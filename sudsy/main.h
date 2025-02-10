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
 
	bool Valid() {
		return (!(r > 255) && !(r < 0)) && (!(g > 255) && !(g < 0)) && (!(b>255) && !(b<0)) && (!(a > 255) && !(a<0));
		} // unlikely to work - programmed on phone :(
	
	bool Valid(float z) {
		return (z < 255) && (z > 0);
		}
	
	void Clamp() {
			if (Valid()) { return; }
			if (!Valid(r)) {
				r > 255 ? r -= 255 : r = 255 - r;
			}
			if (!Valid(g)) {
				g > 255 ? g -= 255 : g = 255 - g;
			}
			if (!Valid(b)) {
				b > 255 ? b -= 255 : b = 255 - b;
			}
			if (!Valid(a)) {
				a > 255 ? a -= 255 : a = 255 - a;
			}
		}
	
	// TODO: Add operator overloads and clamp
		Color operator=(Color other) {
			Set(other);
		}
		Color operator+(Color other) {
			Color n(r + other.r, g + other.g, b + other.b, a + other.a);
			n.Clamp();
			return n;
		}
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
	virtual bool Valid() = 0;
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