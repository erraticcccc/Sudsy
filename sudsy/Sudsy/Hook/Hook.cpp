#include "Hook.h"

namespace sudsy
{
	// Two args: Target function, which will be replaced, and the replacement function, which will replace the target function

#if defined(_WIN32) && !defined(_WIN64)

	BYTE* Hook::THook(BYTE* toHook, BYTE* from, int amount) {
		// to is the function you want to hook, from is the function
		// that overrides "to".
		if (amount < 5) return 0;
		DWORD p;
		VirtualProtect(toHook, amount, PAGE_EXECUTE_READWRITE, &p);
		stolenBytes = (BYTE*)VirtualAlloc(0, amount + 5, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
		if (!stolenBytes) return 0;
		memcpy(stolenBytes, toHook, amount);
		uintptr_t relAddress = from - toHook - 5;
		uintptr_t jumpbackAddress = toHook - stolenBytes - 5;
		memset(toHook, 0x90, amount);

		BYTE relJump[] = {
			0xE9, 0x0, 0x0, 0x0, 0x0
		};
		memcpy(&relJump[1], &relAddress, 4);
		memcpy(toHook, relJump, 5);

		memcpy(&relJump[1], &jumpbackAddress, 4);
		memcpy(stolenBytes + amount, relJump, 5);

		VirtualProtect(toHook, amount, p, &p);

		return stolenBytes;
	}

#elif defined(_WIN64)

	BYTE* Hook::THook(BYTE* toHook, BYTE* from, int amount) {
		// to is the function you want to hook, from is the function
		// that overrides "to".
		if (amount < 13) return 0;
		DWORD p;
		VirtualProtect(toHook, amount, PAGE_EXECUTE_READWRITE, &p);
		stolenBytes = (BYTE*)VirtualAlloc(0, amount + 13, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
		if (!stolenBytes) return 0; // virtualAlloc failed!
		memcpy(stolenBytes, toHook, amount);

		BYTE absJump64[] = {
			0x49, 0xBA, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
			0x41, 0xFF, 0xE2
		};
		uint64_t testingVar = (uint64_t)from;
		memcpy(&absJump64[2], &testingVar, 8);
		memset(toHook, 0x90, amount);
		memcpy(toHook, absJump64, sizeof(absJump64));

		uint64_t jumpbackAddress = (uint64_t)(toHook + 13);
		memcpy(&absJump64[2], &jumpbackAddress, 8);
		memcpy((stolenBytes + amount), absJump64, 13);

		VirtualProtect(toHook, amount, p, &p);

		return stolenBytes;
}

#endif

	void Hook::ToggleHook() 
	{
	}

}