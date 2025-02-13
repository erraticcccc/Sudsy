#pragma once
#include "common.h"

#define HYPOTENUSE(a,b) \
		(sqrtf((a*a)+(b*b)))

static int _clmp(int to, int max, int min) {
	if (to > max) {
		to -= max;
	}
	if (to < min) {
		to = max - to;
	}
	return to;
}

static float _fclmp(float to, float max, float min) {
	if (to > max) {
		to -= max;
	}
	if (to < min) {
		to = max - to;
	}
	return to;
}

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
		r = _clmp(r, 255, 0);
		g = _clmp(g, 255, 0);
		b = _clmp(b, 255, 0);
		a = _clmp(a, 255, 0);
	}

	Color operator=(Color other) {
		Set(other);
		return *this;
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
	D3DCOLOR DirectX() {
		return D3DCOLOR_ARGB(a, r, g, b);
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


struct Vec2
{
	float x, y;

	Vec2() {
		x = y = 0.f;
	}

	Vec2(float _x, float _y) {
		x = _x; y = _y;
	}

	void Set(float _x, float _y) {
		x = _x, y = _y;
	}

	Vec2 operator+ (Vec2 other) {
		return Vec2(x + other.x, y + other.y);
	}
	Vec2 operator- (Vec2 other) {
		return Vec2(x - other.x, y - other.y);
	}

	float distance(Vec2 other) {
		return HYPOTENUSE(fabs(other.x - this->x), fabs(other.y - this->y));
	}

	void clamp(float maxx, float minx, float maxy, float miny) {
		x = _fclmp(x, maxx, minx);
		y = _fclmp(y, maxy, miny);
	}

	void bounds(float boundsmin, float boundsmax, float pos, bool& b) {
		if (boundsmax < pos) {
			b = false;
		}
		else if (boundsmin > pos) {
			b = true;
		}
	}

	D3DXVECTOR2 ToDirectX()
	{
		return D3DXVECTOR2(x, y);
	}
};

struct ScreenPos {
	ScreenPos(Vec2 s, Vec2 e) {
		start = s, end = e;
	}
	Vec2 start, end;
};

struct _VTX {
	float x, y, z, rwh;
	D3DCOLOR col;
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
	void AddChild(Sudject& child) {
		children.push_back(&child);
		child.parent = this;
	}
	bool IsVisible() { return visible; }
	virtual void Draw() = 0;
	virtual bool Valid() = 0;
	virtual ScreenPos GetPos() = 0;
	virtual void SetVisible(bool vis) = 0;
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
		ScreenPos GetPos() {
			return ScreenPos(start, end);
		}
		void Draw() {
			if (!Valid()) { return; }
			if (!Sudevice) { return; }

			static ID3DXLine* pLine = nullptr;

			if (!pLine)
				D3DXCreateLine(Sudevice, &pLine);

			if (pLine)
			{
				pLine->SetWidth(this->thickness);

				D3DXVECTOR2 points[2];

				if (!parent) {
					points[0] = start.ToDirectX(), points[1] = end.ToDirectX();
				}
				else {
					points[0] = (parent->GetPos().start + start).ToDirectX(), points[1] = (parent->GetPos().end - end).ToDirectX();
				}

				this->color.Clamp();

				D3DCOLOR color = D3DCOLOR_ARGB(this->color.a, this->color.r, this->color.g, this->color.b);

				pLine->Draw(points, 2, color);
			}

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
			if (!parent) {
				return start.distance(end) > 0;
			}
			else {
				return (parent->GetPos().start + start).distance(parent->GetPos().end - end) > 0;
			}
		}
		void SetVisible(bool vis) {
			visible = vis;
		}
	};
	struct Rectangle : public Shape {
		Vec2 tl, tr, bl, br; // Top left, top right, bottom left, bottom right
		float linethickness = 0.f; // only useful if unfilled/outline
		Color color = COLOR_WHITE, outlinecol = COLOR_WHITE;
		int outlineoffset = 0;
		bool filled = true, outline = false;
		Rectangle() {
		}
		Rectangle(Vec2 topleft, Vec2 bottomright) : tl(topleft), br(bottomright), bl(tl.x, br.y), tr(br.x, tl.y)
		{
		}
		Type GetType() { return RECTANGLE; }
		void SetColor(Color col) {
			color = col;
		}
		void SetThickness(float thickness) {}
		void SetFilled(bool filled) {}
		bool Valid() {
			return tl.distance(br) > 0;
		}
		void SetVisible(bool v) {
			visible = v;
		}
		void Draw() {
			if (!Valid()) { return; }
			if (!Sudevice) { return; }

			static ID3DXLine* pLine = nullptr;

			if (!pLine)
				D3DXCreateLine(Sudevice, &pLine);

			if (pLine)
			{
				float Thickness = br.y - tl.y;
				float Y = tl.y + (Thickness / 2.f);

				D3DXVECTOR2 left(tl.x, Y);
				D3DXVECTOR2 right(tl.x + br.x, Y);

				pLine->SetWidth(Thickness);

				D3DXVECTOR2 points[2] = { left, right };

				this->color.Clamp();
				pLine->Draw(points, 2, this->color.DirectX());
			}
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
	void Init();
	void Render();
	void Destroy();
	inline bool Active = false;
}