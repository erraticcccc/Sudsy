#pragma once
#include "main.h"

typedef BYTE byte;

namespace sudsy {
	class Hook {
		unsigned int Size = 0;
		DWORD patternSize = 0;
		HMODULE	mBase = 0;
		bool Toggle = false;
		BYTE* stolenBytes = nullptr;
	public:
		BYTE* THook(BYTE* to, BYTE* from, int amount);
		void ToggleHook();
	};
}