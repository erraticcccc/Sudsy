#include "text.h"

namespace sudsy 
{
	void Text::Draw() {
		if (!Sudevice) { return; }
		if (!Valid()) { return; }
		if (!font.Valid()) { font.Create(); }

		RECT r;
		SetRect(&r, pos.x, pos.y, content.length() * 4, 5);
		std::wstring s(content.begin(), content.end());
		font.self->DrawText(NULL, s.c_str(), -1, &r, DT_LEFT | DT_NOCLIP, fontcolor.DirectX());
	}
	bool Text::Valid() {
		return this->content.length() > 0 || (!font.Valid());
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
	void Text::SetFont(std::string font)
	{
	}
	void Text::SetFontSize(int size){
		}
	void Text::SetFontColor(Color color){
		fontcolor = color;
	}
	void Text::SetFontShadow(bool shadow){
		}
	void Text::SetFontOutline(bool outline){
		}
	void Text::SetFontCentered(bool centered){
		}
	void Text::SetFontRightAligned(bool rightaligned){
		}
	void Text::SetFontOutlineColor(Color color){
		}
	void Text::SetFontShadowColor(Color color){
		}
	ScreenPos Text::GetPos() {
		return ScreenPos(pos,pos);
	}
	Text::~Text() {
	}
}