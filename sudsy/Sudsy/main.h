#pragma once
#include "common.h"

#define HYPOTENUSE(a,b) \
		(sqrtf((a*a)+(b*b)))

struct Color {
	int r, g, b, a;

	Color() : r(255), g(255), b(255), a(255) {}

	Color(int _r, int _g, int _b, int _a = 255) {
		Set(_r, _g, _b, _a);
	}

	Color(int z) {
		Set(z, z, z, z);
	}

	void Set(int _r, int _g, int _b, int _a = 255) {
		r = _r; g = _g; b = _b; a = _a;
		Clamp();
	}

	void Set(const Color& color) {
		r = color.r;
		g = color.g;
		b = color.b;
		a = color.a;
		Clamp();
	}

	bool Valid() const {
		return (r >= 0 && r <= 255) &&
			(g >= 0 && g <= 255) &&
			(b >= 0 && b <= 255) &&
			(a >= 0 && a <= 255);
	}

	bool Valid(int z) const {
		return (z >= 0 && z <= 255);
	}

	void Clamp() {
		r = std::clamp(r,0, 255);
		g = std::clamp(g,0, 255);
		b = std::clamp(b,0, 255);
		a = std::clamp(a,0, 255);
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
	float distance(Vec2 other) {
		return HYPOTENUSE(fabs(other.x - this->x), fabs(other.y - this->y));
	}
};

class Sudject;

inline std::vector <Sudject*> sudjects;
inline IDirect3DDevice9* Sudevice = nullptr;

// Used as a base class for all objects, will be used for parent/child relationships
class Sudject {
protected:
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

inline Color COLOR_WHITE = Color(255, 255, 255, 255);
inline Color COLOR_BLACK = Color(0, 0, 0, 255);

struct Shape : public Sudject {
	enum Type {
		LINE,
		RECTANGLE,
		CIRCLE,
		TRIANGLE
	};
	virtual Type GetType() = 0;
	virtual void Draw() = 0;
	virtual void SetColor(Color color) = 0;
	virtual void SetThickness(float thickness) = 0;
	virtual void SetFilled(bool filled) = 0;
};

namespace Shapes {
	struct Line : public Shape {
		Vec2 start, end;
		float thickness;
		Color color;
		D3DRECT line;
		Line() {
			start = Vec2(0.f, 0.f);
			end = Vec2(0.f, 0.f);
			thickness = 1.f;
			color = COLOR_WHITE;
		}
		Line(Vec2 s, Vec2 e, float t, Color c) {
			start = s;
			end = e;
			thickness = t;
			color = c;
		}
		Type GetType() { return LINE; }
		void Draw() {
			if (!Valid()) { return; }
			if (!Sudevice) { return; }
			line.x1 = start.x + (thickness/2);
			line.x2 = start.y - (thickness / 2);
			line.y1 = end.x + (thickness / 2);
			line.y2 = end.y - (thickness / 2);
			auto c = D3DCOLOR_ARGB(color.a,color.r,color.g,color.b);
			Sudevice->Clear(1,&line,D3DCLEAR_TARGET,c,0,0);
		}
		void SetColor(Color color) {
			this->color = color;
		}
		void SetThickness(float thickness) {
			this->thickness = thickness;
		}
		void SetFilled(bool filled) {
			// Not used
		}
		bool Valid() {
			return start.distance(end) > 0;
		}
		void SetVisible(bool vis) {
			visible = vis;
		}
	};
	struct Rectangle : public Shape {
		Vec2 start, end;
		float linethickness;
		Color color;
		bool filled;
		
		Rectangle() {
			start = Vec2(0.f, 0.f);
			end = Vec2(0.f, 0.f);
			linethickness = 1.f;
			color = COLOR_WHITE;
			filled = false;
		}
	};
	struct Circle : public Shape {
		Vec2 center;
		float linethickness;
		float radius;
		Color color;
		bool filled;
		Circle() {
			center = Vec2(0.f, 0.f);
			linethickness = 1.f;
			radius = 0.f;
			color = COLOR_WHITE;
			filled = false;
		}
	};
	struct Triangle : public Shape {
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
	void Init(sudsy::Hook hk);
	void Render();
	void Destroy();
	inline bool Active = false;
}