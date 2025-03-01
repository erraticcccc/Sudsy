#pragma once
#include "common.h"

#define HYPOTENUSE(a,b) \
		(sqrtf((a*a)+(b*b)))

inline int _clmp(int to, int max, int min) {
	if (to > max) {
		to -= max;
		return _clmp(to,max,min);
	}
	if (to < min) {
		to = max - to;
		return _clmp(to,max,min);
	}
	return to;
}

inline float _fclmp(float to, float max, float min) {
	if (to > max) {
		to -= max;
		return _fclmp(to, max, min);
	}
	if (to < min) {
		to = max - to;
		return _fclmp(to, max, min);
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
		Color n(r + ((r + other.r) / 2), 
				g + ((g + other.g) / 2), 
				b + ((b + other.b) / 2), 
				a + ((a + other.a) / 2));
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
	void HSLToColor(float h, float s, float l) {
		float r, g, b;
		h = _fclmp(h, 360, 0);
		h /= 360;
		auto hueToRgb = [](float p, float q, float t) {
			if (t < 0.0f) t += 1.0f;
			if (t > 1.0f) t -= 1.0f;
			if (t < 1.0f / 6.0f) return p + (q - p) * 6.0f * t;
			if (t < 1.0f / 2.0f) return q;
			if (t < 2.0f / 3.0f) return p + (q - p) * (2.0f / 3.0f - t) * 6.0f;
			return p;
			};

		if (s == 0.0f) {
			r = g = b = l; // achromatic
		}
		else {
			float q = l < 0.5f ? l * (1.0f + s) : l + s - l * s;
			float p = 2.0f * l - q;
			r = hueToRgb(p, q, h + 1.0f / 3.0f);
			g = hueToRgb(p, q, h);
			b = hueToRgb(p, q, h - 1.0f / 3.0f);
		}

		Set(static_cast<int>(r * 255.0f), static_cast<int>(g * 255.0f), static_cast<int>(b * 255.0f), a);
		Clamp();
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
	void Set(Vec2 &other) {
		x = other.x, y = other.y;
	}

	Vec2 operator+ (Vec2 other) {
		return Vec2(x + other.x, y + other.y);
	}
	Vec2 operator- (Vec2 other) {
		return Vec2(x - other.x, y - other.y);
	}
	void operator+=(Vec2 other) {
		this->Set(other.x + this->x, other.y + this->y);
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
	Vec2 start, end;
	ScreenPos(Vec2& s, Vec2& e) : start(s), end(e) {}
};

struct _VTX {
	float x, y, z, rhw;
	D3DCOLOR color;
};