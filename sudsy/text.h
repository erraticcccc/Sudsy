#pragma once
#include "main.h"

namespace sudsy
{
	class Text
	{
		std::string content;
		std::string font;
		Sudject parent;
		int fontSize;
		Color fontcolor; // not even sure if this is going to be possible
		bool shadow;
		bool outline;
		bool centered;
		bool rightaligned;
		int flags;
		int offsetx;
		int offsety;
		int shadowoffsetx;
		int shadowoffsety;
		int outlineoffsetx;
		int outlineoffsety;
		int centeredoffsetx;
		int centeredoffsety;
		int rightalignedoffsetx;
		int rightalignedoffsety;
		Color shadowcolor;
		float shadowblur;
		float shadowopacity;
		float shadowdistance;
		float shadowangle;
		float shadowspread;
		float shadowspreadoffset;
		float shadowspreadopacity;
		float shadowspreadblur;
		float shadowspreadthickness;
		Color outlinecolor;
		float outlinethickness;
		float outlineopacity;
		float outlinedistance;
		float outlineangle;
		float outlinespread;
		float outlinespreadoffset;
		float outlinespreadopacity;
		float outlinespreadblur;
		float outlinespreadthickness;
	public:
		Text();
		Text(std::string content);
		Text(std::string content, int size);
		Text(std::string content, int size, Color color);
		void SetFont(std::string font);
		void SetFontSize(int size);
		void SetFontColor(Color color);
		void SetFontShadow(bool shadow);
		void SetFontOutline(bool outline);
		void SetFontCentered(bool centered);
		void SetFontRightAligned(bool rightaligned);
		void SetFontOutlineColor(Color color);
		void SetFontShadowColor(Color color);
		~Text();
	public:
		Text& operator=(std::string content);
		Text& operator=(int itostr); // converts integerts to strings
		Text& operator=(float ftostr); // converts floats to strings
		Text& operator=(double dtostr); // converts doubles to strings
		Text& operator+(std::string content);
		Text& operator+(Text content);
	};
}