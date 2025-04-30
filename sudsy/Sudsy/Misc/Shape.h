#pragma once
#include "misc/Sudject.h"

#define D3DFVF_CUSTOMVERTEX (D3DFVF_XYZRHW | D3DFVF_DIFFUSE)
#define CUSTOMFVF (D3DFVF_XYZRHW | D3DFVF_DIFFUSE)

struct Shape : public Sudject {
	virtual Type GetType() = 0;
	virtual inline void Draw() = 0;
	virtual void SetColor(const Color &color) = 0;
	virtual void SetThickness(float thickness) = 0;
	virtual void SetFilled(bool filled) = 0;
	virtual float Area() = 0;
};

namespace Shapes {
	struct Line : public Shape {
		Vec2 start, end;
		float thickness;
		Color color;
		Line() : start(pd::VEC2ZERO), end(pd::VEC2ZERO), thickness(1.f), color (pd::COLOR_WHITE) {}
		Line(Vec2 s, Vec2 e, float t, Color c) {
			start = s;
			end = e;
			thickness = t;
			color = c;
		}
		Type GetType() { return S_SHAPE; }
		ScreenPos GetPos() {
			return ScreenPos(start, end);
		}
		float Area() {
			float sidea = (end.y - start.y) + thickness;
			float sideb = end.x - start.x;
			return sidea * sideb;
		}
		inline void Draw() {
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
		void SetColor(const Color &color) {
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
		Rectangle() : tl(pd::VEC2ZERO), tr(pd::VEC2ZERO), bl(pd::VEC2ZERO), br(pd::VEC2ZERO) {}
		Rectangle(Vec2 topleft, Vec2 bottomright) : tl(topleft), br(bottomright), bl(topleft.x, bottomright.y), tr(bottomright.x, topleft.y) {}
		Rectangle(Vec2 topleft, Vec2 bottomright, Color col) : color(col), tl(topleft), br(bottomright), bl(topleft.x, bottomright.y), tr(bottomright.x, topleft.y) {}
		Type GetType() { return S_SHAPE; }
		void SetColor(const Color& col) {
			color = col;
		}
		ScreenPos GetPos() {
			return ScreenPos(tl, br);
		}
		float Area() {
			return ((tr.x - tl.x) * (bl.y - tl.y));
		}
		void SetThickness(float thickness) {}
		void SetFilled(bool filled) {}
		void SetPos(Vec2 topleft, Vec2 bottomright) {
			tl = topleft;
			br = bottomright;
			tr = { br.x, tl.y };
			bl = { tl.x, br.y };
		}
		void SetPos(Vec2 topleft) {
			Vec2 dif = br - tl;
			tl = topleft;
			br = tl + dif;
			tr = { br.x, topleft.y };
			bl = { topleft.x, br.y };
		}
		bool Valid() {
			if (parent) {
				return ((tl != pd::VEC2ZERO) && (br != pd::VEC2ZERO));
			}
			else {
				return tl.distance(br) > 0;
			}
		}
		void SetVisible(bool v) {
			visible = v;
		}
		inline void Draw() {
			if (!Valid()) { return; }
			if (!Sudevice) { return; }

			static ID3DXLine* pLine = nullptr;

			if (!pLine)
				D3DXCreateLine(Sudevice, &pLine);

			if (parent && parent->GetType() == S_SHAPE) {
				ScreenPos pp = parent->GetPos();
				for (float i = tl.y + pp.start.y; i < pp.end.y - br.y; ++i) {
					D3DXVECTOR2 line[] = {
						D3DXVECTOR2(tl.x + pp.start.x, i),
						D3DXVECTOR2(pp.end.x - tr.x, i)
					};
					pLine->Draw(line, 2, color.DirectX());
				}
			}
			else {
				for (float i = tr.y; i < br.y; ++i) {
					D3DXVECTOR2 line[] = {
						D3DXVECTOR2(tl.x, i),
						D3DXVECTOR2(tr.x, i)
					};
					pLine->Draw(line, 2, color.DirectX());
				}
			}
		}
	};
	struct Circle : public Shape {
		Vec2 center = pd::VEC2ZERO;
		float linethickness = 1.f;
		float radius = 0.f;
		Color color;
		bool filled = true;
		Circle() {}
		Circle(Vec2& c, float r, Color& col) : center(c), radius(r), color(col) {}
		bool Valid() {
			return radius > 0;
		}
		Type GetType() { return S_SHAPE; }
		inline void Draw() {
			if (!Valid()) { return; }
			if (!Sudevice) { return; }

			const int numSegments = 36;
			_VTX vertices[numSegments + 2];

			if (parent && parent->GetType() == S_SHAPE) {
				ScreenPos p = parent->GetPos();
				vertices[0].x = center.x + ((p.end.x - p.start.x)/2 + p.start.x);
				vertices[0].y = center.y + ((p.end.y - p.start.y)/2 + p.start.y);
			}
			else {
				vertices[0].x = center.x;
				vertices[0].y = center.y;
			}
			vertices[0].z = 0.0f;
			vertices[0].rhw = 1.0f;
			vertices[0].color = color.DirectX();

			for (int i = 1; i <= numSegments + 1; ++i)
			{
				float theta = (2 * D3DX_PI * (i - 1)) / numSegments;
				vertices[i].x = center.x + radius * cosf(theta);
				vertices[i].y = center.y - radius * sinf(theta);
				vertices[i].z = 0.0f;
				vertices[i].rhw = 1.0f;
				vertices[i].color = color.DirectX();
			}

			Sudevice->SetFVF(D3DFVF_CUSTOMVERTEX);

			Sudevice->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, numSegments, vertices, sizeof(_VTX));
		}
		float Area() {
			return ::sqrtf(D3DX_PI * (radius * radius));
		}
		ScreenPos GetPos() {
			Vec2 rvec = Vec2(radius);
			return ScreenPos(center - rvec, center + rvec);
		}
		void SetPos() {

		}
		void SetVisible(bool vis) {
			visible = vis;
		}
		void SetColor(const Color &col) { color = col; }
		void SetThickness(float thickness) { linethickness = thickness; }
		void SetFilled(bool filled) { this->filled = filled; }

	};
	struct Triangle : public Shape {
		Vec2 a, b, c;
		float linethickness = 1.f;
		Color color = pd::COLOR_WHITE;
		bool filled = true;
		Triangle() : a(pd::VEC2ZERO), b(pd::VEC2ZERO), c(pd::VEC2ZERO) {}
		Triangle(Vec2 x, Vec2 y, Vec2 z) : a(x), b(y), c(z) {}
		Triangle(Vec2 p, float r) : a(p.x - r,p.y - r), b(p.x + r, p.y + r), c(p.x, p.y - r) {}

	};
}