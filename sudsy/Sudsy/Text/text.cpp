#include "text.h"

namespace sudsy 
{
	void Text::Draw() {

	}
	bool Text::Valid() {
		return this->content.length() > 0;
	}
	Text::Text()
	{
		this->content = "";
	}
	Text::Text(std::string content)
	{
		this->content = content;
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