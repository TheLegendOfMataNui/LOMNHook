#pragma once

#include <string>

#include "LOMNAPI.h"

namespace LOMNHook {
	class LOMNAPI HookMod {
	public:
		virtual std::wstring GetName() const = 0;
		virtual int GetVersion() const = 0;
		virtual int GetAPIRevision() const = 0;

		// InitFunc phase of startup
		virtual void OnPreInit() { }
		virtual void OnPostInit() { }

		// DoSetUp phase of startup
		virtual void OnPreSetUp() { }
		virtual void OnPostSetUp() { }

		// When the InitFuncs are called again to shutdown
		virtual void OnPreDeInit() { }
		virtual void OnPostDeInit() { }
	};
}