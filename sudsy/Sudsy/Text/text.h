#pragma once
#include "main.h"

struct Font {
	std::string name;
	ID3DXFont* self = nullptr;
	int height = 0, width = 0, weight = 0;
	Font() : name("Arial")
	{}
	Font(std::string fontName) : name(fontName)
	{}
	void Create() {
		if (!Sudevice) { return; }
		std::wstring w(name.begin(), name.end());
		//				device   h		 w		weight       mip italic  charset         precision           quality				 pitch and		 family       fontName   fontobj
		D3DXCreateFont(Sudevice, height, width, weight * 200, 1, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, ANTIALIASED_QUALITY, DEFAULT_PITCH | FF_DONTCARE, w.c_str(), &self);
	}
	~Font() {
		if (!self) { return; }
		self->Release();
		self = nullptr;
	}
	bool Valid() {
		return (self != nullptr);
	}
};

namespace sudsy
{
	class Text : public Sudject
	{
		std::string content = "";
		Vec2 pos = pd::VEC2ZERO;
		Sudject* parent = nullptr;
		int fontSize = 0;
		Color fontcolor = pd::COLOR_WHITE; // not even sure if this is going to be possible
		bool shadow = false, rightaligned = false, outline = false, centered = false;
		int offsetx = 0, offsety = 0;
		int shadowoffsetx = 0, shadowoffsety = 0;
		int outlineoffsetx = 0, outlineoffsety = 0;
		int centeredoffsetx = 0, centeredoffsety = 0;
		int rightalignedoffsetx = 0, rightalignedoffsety = 0;
		Color shadowcolor = pd::COLOR_BLACK, outlinecolor = pd::COLOR_BLACK;
		Type type = S_TEXT;
	public:
		Font font;
		Text();
		Text(std::string content);
		Text(std::string content, Vec2 pos);
		Text(std::string content, Vec2 pos, Color col);
		Text(std::string content, int size);
		Text(std::string content, int size, Color col);
		void SetFont(std::string font);
		void SetFontSize(int size);
		void SetFontColor(Color color);
		void SetFontShadow(bool shadow);
		void SetFontOutline(bool outline);
		void SetFontCentered(bool centered);
		void SetFontRightAligned(bool rightaligned);
		void SetFontOutlineColor(Color color);
		void SetFontShadowColor(Color color);
		Type GetType() { return type; }
		~Text();
		ScreenPos GetPos();
		void SetParent(Sudject* par) { parent = par; }
		void Draw();
		bool Valid();
		void SetVisible(bool v) {
			visible = v;
		}
	public:
		void operator=(std::string &str) { content = str; }
		void operator=(int itostr) { content = std::to_string(itostr); }
		void operator=(float ftostr) { content = std::to_string(ftostr); }
		void operator=(double dtostr) { content = std::to_string(dtostr); }
		void operator+(std::string &str) { content += str; }
		void operator+(Text &other) { content += other.content; }
	};
}