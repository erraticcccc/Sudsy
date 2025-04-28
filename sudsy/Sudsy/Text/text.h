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
		//				device   h		 w		weight       mip italic  charset         precision           quality				 pitch and		 family    fontName   fontobj
		D3DXCreateFont(Sudevice, height, width, weight * 200, 1, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, ANTIALIASED_QUALITY, DEFAULT_PITCH | FF_DONTCARE, name.c_str(), &self);
	}
	~Font() {
		if (!self) { return; }
		self->Release();
		self = nullptr;
	}
	bool Valid() {
		if (self == nullptr) { Create(); }
		return self != nullptr;
	}
};

enum alignment {
	ALIGN_NONE = 0,
	ALIGN_RIGHT,
	ALIGN_LEFT,
	ALIGN_TOP,
	ALIGN_BOTTOM
};

namespace sudsy
{
	class Text : public Sudject
	{
		std::string content = "";
		Vec2 pos = pd::VEC2ZERO;
		int fontSize = 0;
		Color fontcolor = pd::COLOR_WHITE;
		bool shadow = false, rightaligned = false, outline = false, centered = false;
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
		void SetFont(Font font);
		Type GetType() { return type; }
		~Text();
		void SetPos(Vec2 p) { pos = p; }
		ScreenPos GetPos();
		void Draw();
		bool Valid();
		void SetVisible(bool v) {
			visible = v;
		}
	public:
		void operator=(std::string str)		{ content = str; }
		void operator=(Vec2 vtostr)			{ content = (std::to_string(vtostr.x) + ", " + std::to_string(vtostr.y)); }
		void operator=(int itostr)			{ content = std::to_string(itostr); }
		void operator=(float ftostr)		{ content = std::to_string(ftostr); }
		void operator=(double dtostr)		{ content = std::to_string(dtostr); }
		Text& operator+=(std::string str)	{ content += str; }
		Text& operator+=(Text &other)		{ content += other.content; }
		Text operator+(std::string &str)	{ return content + str; }
		Text operator+(Text &other)			{ return content + other.content; }
	};
}