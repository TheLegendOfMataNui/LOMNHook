#pragma once

#include <string>

namespace LOMNHook 
{
	class HookMod
	{
		virtual std::wstring GetName() const = 0;
		virtual int GetVersion() const = 0;

		// InitFunc phase of startup
		virtual void OnPreInit() { }
		virtual void OnPostInit() { }

		// DoSetUp phase of startup
		virtual void OnPreSetUp() { }
		virtual void OnPostSetUp() { }
	};
}