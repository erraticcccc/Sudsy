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
	void operator=(Color other) {
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

class Drawable {
public:
	void Draw() { return; } // Meant to be overridden
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
class Sudject : public Drawable {
	int sid; // used for render order and identification
	bool visible;
public:
	Sudject() {
		// Somehow get last created Sudject/Object or create managing vector of some sort
	}
	Sudject* parent;
	std::vector <Sudject*> children;
	Sudject* GetParent() {
		return parent;
	}
	std::vector <Sudject*> GetChildren() {
		return children;
	}
	Sudject* GetChild(int index) {
		return children[index];
	}
	void AddChild(Sudject* child) {
		children.push_back(child);
	}
	bool Valid() { return true; }
	void SetVisible(bool vis) { visible = vis; }
	bool IsVisible() { return visible; }
};

inline std::vector <Sudject*> sudjects;

namespace PreDef {
	inline Color COLOR_WHITE = Color(255.f, 255.f, 255.f, 255.f);
	inline Color COLOR_BLACK = Color(0.f, 0.f, 0.f, 255.f);
}

namespace Shapes {
	struct Line {
		Vec2 start, end;
		float thickness;
		Color color;
	};
	struct Rectangle {
		Vec2 start, end;
		float linethickness;
		Color color;
		bool filled;
	};
	struct Circle {
		Vec2 center;
		float linethickness;
		float radius;
		Color color;
		bool filled;
	};
	struct Triangle {
		Vec2 a, b, c;
		float linethickness;
		Color color;
		bool filled;
	};
}


namespace sudsy
{
	// Sudsy is a DirectX wrapper that allows you to create all of the below objects within any directx application
	// Not really going to be useful for the time, only going to be making DX9 based
	enum DX {
		DX9,
		DX10,
		DX11,
		DX12
	};
	class Hook;
	void Initialize(DX dxversion);
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