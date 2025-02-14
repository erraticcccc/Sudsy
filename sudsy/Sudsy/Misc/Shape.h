#pragma once
#include "misc/Sudject.h"

#define D3DFVF_CUSTOMVERTEX (D3DFVF_XYZRHW | D3DFVF_DIFFUSE)
#define CUSTOMFVF (D3DFVF_XYZ | D3DFVF_DIFFUSE)

namespace pd {
	inline Color COLOR_WHITE = Color(255, 255, 255, 255);
	inline Color COLOR_BLACK = Color(0, 0, 0, 255);
	inline Vec2 VEC2ZERO = Vec2(0, 0);
	inline Vec3 VEC3ZERO = Vec3(0, 0, 0);
}

enum Type {
	LINE,
	RECTANGLE,
	CIRCLE,
	TRIANGLE
};

struct Shape : public Sudject {
	virtual Type GetType() = 0;
	virtual void Draw() = 0;
	virtual void SetColor(Color color) = 0;
	virtual void SetThickness(float thickness) = 0;
	virtual void SetFilled(bool filled) = 0;
	virtual float Area() = 0;
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
			color = pd::COLOR_WHITE;
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
		float Area() {
			float sidea = (end.y - start.y) + thickness;
			float sideb = end.x - start.x;
			return sidea * sideb;
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
		Color color = pd::COLOR_WHITE, outlinecol = pd::COLOR_WHITE;
		int outlineoffset = 0;
		bool filled = true, outline = false;
		Rectangle() {
		}
		Rectangle(Vec2 topleft, Vec2 bottomright) : tl(topleft), br(bottomright), bl(tl.x, br.y), tr(br.x, tl.y)
		{
		}
		Rectangle(Vec2 topleft, Vec2 bottomright, Color col) : color(col), tl(topleft), br(bottomright), bl(tl.x, br.y), tr(br.x, tl.y)
		{
		}
		Type GetType() { return RECTANGLE; }
		void SetColor(Color col) {
			color = col;
		}
		ScreenPos GetPos() {
			return ScreenPos(tl, br);
		}
		float Area() {
			return 0.f;
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

			LPDIRECT3DVERTEXBUFFER9 vBuffer;

			_VTX OurVertices[] =
			{
				{ 0, 0, 0, 1.0f, D3DCOLOR_XRGB(127, 0, 0) },
				{ 500, 0, 0, 1.0f, D3DCOLOR_XRGB(127, 0, 0) },
				{ 0, 300, 0, 1.0f, D3DCOLOR_XRGB(127, 0, 0) },
				{ 500, 300, 0, 1.0f, D3DCOLOR_XRGB(127, 0, 0) }
			};

			Sudevice->CreateVertexBuffer(4 * sizeof(_VTX),
				0,
				CUSTOMFVF,
				D3DPOOL_MANAGED,
				&vBuffer,
				NULL);

			VOID* pVoid;    // the void* we were talking about

			vBuffer->Lock(0, 0, (void**)&pVoid, 0);    // locks v_buffer, the buffer we made earlier
			memcpy(pVoid, OurVertices, sizeof(OurVertices));    // copy vertices to the vertex buffer
			vBuffer->Unlock();    // unlock v_buffer

			Sudevice->SetFVF(CUSTOMFVF);
			Sudevice->SetStreamSource(0, vBuffer, 0, sizeof(_VTX));
			Sudevice->DrawPrimitive(D3DPT_TRIANGLELIST, 0, 1);
		}
	};
	struct Circle : public Shape {
		Vec2 center = pd::VEC2ZERO;
		float linethickness = 1.f;
		float radius = 0.f;
		Color color = pd::COLOR_WHITE;
		bool filled = true;
		Circle() {}
		Circle(Vec2& c, float r, Color& col) : center(c), radius(r), color(col) {}
		bool Valid() {
			return radius > 0;
		}
		Type GetType() { return CIRCLE; }
		void Draw() {
			if (!Valid()) { return; }
			if (!Sudevice) { return; }

			_VTX line[] = {
				{ 100.0f, 100.0f, 0.0f, 1.0f, D3DCOLOR_XRGB(255, 0, 0) },
				{ 200.0f, 200.0f, 0.0f, 1.0f, D3DCOLOR_XRGB(255, 0, 0) }
			};

			Sudevice->SetFVF(D3DFVF_CUSTOMVERTEX);
			HRESULT hr = Sudevice->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 1, line, sizeof(_VTX));

			std::cout << hr;
		}
		ScreenPos GetPos() {
			return ScreenPos(center, center);
		}
		void SetVisible(bool vis) {
			visible = vis;
		}
		void SetColor(Color col) { color = col; }
		void SetThickness(float thickness) { linethickness = thickness; }
		void SetFilled(bool filled) { this->filled = filled; }

	};
	struct Triangle : public Shape {
		Vec2 a, b, c;
		float linethickness;
		Color color;
		bool filled;
	};
}