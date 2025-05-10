#include "text.h"

namespace sudsy 
{
	void Text::Draw() {
		if (!Sudevice) { return; }
		if (!Valid()) { return; }
		if (!font.Valid()) { font.Create(); }

		RECT r;
		if (!parent) {
			SetRect(&r, pos.x, pos.y, content.length() * 4, 5);
			font.self->DrawText(NULL, content.c_str(), -1, &r, DT_LEFT | DT_NOCLIP, fontcolor.DirectX());			
		}
		else {
			auto p = parent->GetPos();
			switch (alignment) {
			case ALIGN_CENTER: {
				float midx = (p.end.x - p.start.x)/2 + p.start.x;
				float midy = (p.end.y - p.start.y)/2 + p.start.y;
				SetRect(&r, midx - content.length() * 4 + 5, midy - 10, content.length() * 4 + midx, 5 + midy);
				font.self->DrawText(NULL, content.c_str(), -1, &r, DT_LEFT | DT_NOCLIP, fontcolor.DirectX());
				break;
			}
			case ALIGN_LEFT: {
				SetRect(&r, p.start.x + pos.x, p.start.y + pos.y, content.length() * 4, 5);
				font.self->DrawText(NULL, content.c_str(), -1, &r, DT_LEFT | DT_NOCLIP, fontcolor.DirectX());
			}
			default:
				break;
		}
		}
	}
	bool Text::Valid() {
		return this->content.length() > 0 && (font.Valid());
	}
	Text::Text()
	{
		this->content = "";
	}
	Text::Text(std::string content)
	{
		this->content = content;

	}
	Text::Text(std::string content, Vec2 w)
	{
		this->content = content;
		pos = w;
	}
	Text::Text(std::string con, Vec2 p, Color col) {
		content = con;
		pos = p;
		fontcolor = col;
	}
	Text::Text(std::string content, int size)
	{
		this->content = content;
		this->fontSize = size;
	}
	Text::Text(std::string content, int size, Color color)
	{
		this->content = content;
		this->fontSize = size;
		this->fontcolor = color;
	}
	void Text::SetFont(Font font)
	{
	}
	ScreenPos Text::GetPos() {
		return ScreenPos(pos,pos);
	}
	Text::~Text() {
	}
}