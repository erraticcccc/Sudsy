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
		Undo();
		stolenBytes.clear();
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
		stolenBytes.resize(7); // TBD, going to depend on size of first bytes within pEndScene

		memcpy(&stolenBytes[0], originalFunction, 7);

		DWORD oldProtect;
		VirtualProtect(originalFunction, 7, PAGE_EXECUTE_READWRITE, &oldProtect);

		*(byte*)originalFunction = 0xE9;

		uintptr_t relativeAddress = (uintptr_t)newFunction - (uintptr_t)originalFunction - 5;

		*(uintptr_t*)((uintptr_t)originalFunction + 1) = relativeAddress;

		VirtualProtect(originalFunction, 7, oldProtect, &oldProtect);
	}

	void Hook::Undo()
	{
		DWORD oldProtect;
		VirtualProtect(originalFunction, 5, PAGE_EXECUTE_READWRITE, &oldProtect);

		memcpy(originalFunction, &stolenBytes[0], 5);

		VirtualProtect(originalFunction, 5, oldProtect, &oldProtect);		
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