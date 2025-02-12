#pragma once
#include "main.h"

typedef unsigned char byte;

namespace sudsy {
	class Hook {
		unsigned int Size = 0;
		DWORD patternSize = 0;
		HMODULE	mBase = 0;
		bool Toggle;
		BYTE* stolenBytes;
	public:
		~Hook();
		BYTE* THook(BYTE* to, BYTE* from, int amount);
		// to is the function you want to hook, from is the function
		// that overrides "to".
		BYTE* THook64(BYTE* to, BYTE* from, int amount);
		void ToggleHook();
	};
}