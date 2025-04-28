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
			SetRect(&r, pos.x + p.start.x, pos.y + p.start.y, content.length() * 4 + p.end.x, 5 + p.end.y);
			font.self->DrawText(NULL, content.c_str(), -1, &r, DT_LEFT | DT_NOCLIP, fontcolor.DirectX());
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