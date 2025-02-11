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
		return (r >= 0.0f && r <= 255.0f) &&
			(g >= 0.0f && g <= 255.0f) &&
			(b >= 0.0f && b <= 255.0f) &&
			(a >= 0.0f && a <= 255.0f);
	}
	
	bool Valid(float z) {
		return (z < 255.f) && (z > 0.f);
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

	void operator=(Color other) {
		Set(other);
	}
	Color operator+(Color other) {
		Color n(r + other.r, g + other.g, b + other.b, a + other.a);
		n.Clamp();
		return n;
	}
	Color operator-(Color other) {
		Color n(r - other.r, g - other.g, b - other.b, a - other.a);
		n.Clamp();
		return n;
	}
	void Lerp(Color other) {

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

class Sudject;

inline std::vector <Sudject*> sudjects;

// Used as a base class for all objects, will be used for parent/child relationships
class Sudject {
	bool visible;
	Sudject* parent;
	std::vector <Sudject*> children;
public:
	Sudject() {
		parent = nullptr;
		visible = true;
		sudjects.push_back(this);
	}
	Sudject(Sudject* p) {
		parent = p;
		visible = true;
		sudjects.push_back(this);
	}
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
	bool IsVisible() { return visible; }
	virtual bool Valid() = 0;
	virtual void SetVisible(bool vis) = 0;
	virtual void Draw() = 0;
};


inline Color COLOR_WHITE = Color(255.f, 255.f, 255.f, 255.f);
inline Color COLOR_BLACK = Color(0.f, 0.f, 0.f, 255.f);


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
	inline void Init(DX dxversion);
	inline void Render();
	inline void Destroy();
	inline bool Active = false;
}