#include "Hook.h"

namespace sudsy
{
	// Two args: Target function, which will be replaced, and the replacement function, which will replace the target function
	Hook::Hook(void* target, void* replacement)
	{
		SetTarget(target);
		SetReplacement(replacement);
		Init();
	}

	Hook::~Hook()
	{
	}

#ifdef _WIN64

	void Hook::Init()
	{
		stolenBytes.resize(14); // TBD, going to depend on size of first bytes within pEndScene

		memcpy(&stolenBytes[0], originalFunction, 14);

		DWORD oldProtect;
		VirtualProtect(originalFunction, 14, PAGE_EXECUTE_READWRITE, &oldProtect);

		*(byte*)originalFunction = 0x48;
		*(byte*)((uintptr_t)originalFunction + 1) = 0xB8;
		*(uintptr_t*)((uintptr_t)originalFunction + 2) = (uintptr_t)newFunction;
		*(byte*)((uintptr_t)originalFunction + 10) = 0xFF;
		*(byte*)((uintptr_t)originalFunction + 11) = 0xE0;

		VirtualProtect(originalFunction, 14, oldProtect, &oldProtect);
	}

	void Hook::Undo()
	{
		DWORD oldProtect;
		VirtualProtect(originalFunction, 14, PAGE_EXECUTE_READWRITE, &oldProtect);

		memcpy(originalFunction, &stolenBytes[0], 14);

		VirtualProtect(originalFunction, 14, oldProtect, &oldProtect);
	}

#elif _WIN32

	void Hook::Init()
	{
		DWORD p;
		VirtualProtect(originalFunction, 7, PAGE_EXECUTE_READWRITE, &p);
		stolenBytes = (BYTE*)VirtualAlloc(0, 7 + 5, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
		if (!stolenBytes) return;
		memcpy(stolenBytes, originalFunction, 7);
		uintptr_t relAddress = newFunction - originalFunction - 5;
		uintptr_t jumpbackAddress = newFunction - stolenBytes - 5;
		memset(originalFunction, 0x90, 7);

		BYTE relJump[] = {
			0xE9, 0x0, 0x0, 0x0, 0x0
		};
		memcpy(&relJump[1], &relAddress, 4);
		memcpy(originalFunction, relJump, 5);

		memcpy(&relJump[1], &jumpbackAddress, 4);
		memcpy(stolenBytes + 7, relJump, 5);

		VirtualProtect(originalFunction, 7, p, &p);
	}

	byte* Hook::GetBytes() {
		return stolenBytes;
	}

	void Hook::Undo()
	{
		DWORD oldProtect;
		VirtualProtect(originalFunction, 7, PAGE_EXECUTE_READWRITE, &oldProtect);

		memcpy(originalFunction, &stolenBytes[0], 7);

		VirtualProtect(originalFunction, 7, oldProtect, &oldProtect);		
	}

#endif

	void Hook::ToggleHook() 
	{
		if (Toggle)
		{
			Undo();
			Toggle = false;
		}
		else
		{
			Init();
			Toggle = true;
		}
	}

	void Hook::SetTarget(void* func)
	{
		originalFunction = (byte*)func;
	}

	void Hook::Hook::SetReplacement(void* func)
	{
		newFunction = (byte*)func;
	}

}