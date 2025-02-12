#pragma once
#include "main.h"

typedef unsigned char byte;

namespace sudsy {
	class Hook {
		byte* stolenBytes;
		bool Toggle;
		byte* originalFunction;
		byte* newFunction;
	public:
		Hook(void* target, void* replacement);
		~Hook();
		void Init();
		void Undo();
		void ToggleHook();
		void SetTarget(void* func);
		void SetReplacement(void* func);
		byte* GetBytes();
	};
}