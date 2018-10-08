
Rough Timeline
--------------

`InitFunc`s: Lots of initialization functions are queued up and then ran.
- `LOMNHook::PreInit()` is the first `InitFunc` (queued in `DllMain`)
- Mod `OnPreInit()`
- Game `InitFunc`s
- Any `InitFunc`s queued in `LOMNHook::PreInit()` or `OnPreInit()`
- Mod `OnPostInit()`
- `LOMNHook::PostInit()` (queued in `LOMNHook::PreInit()`)

`GcGame::DoSetUp()` is where the `ScProcess` list is created and populated.
- `LOMNHook::PreSetUp()`
  - Mod `OnPreSetUp()`
- Native `GcGame::DoSetUp()` (`gProcessManager` is created here and accessible after)
- `LOMNHook::PostSetUp()`
  - Mod `OnPostSetUp()`

How to Start a New Mod
----------------------
First, create a new C++ DLL project.

Next, add the LOMNAPI include folder to the project include directories.
Using Visual Studio: right click on the project, pick Properties, navigate to the `VC++ Directories`, and edit the `Include Directories` property to include the path of the LOMNAPI `include/` folder. For mods in the LOMNHook repository, we can use macros as such: `$(SolutionDir)LOMNHook\include` 

Also, you will need to link to the LOMNHook exe for the implementation of LOMNAPI functions.
Using Visual Studio, open the project properties, navigate to the `Linker > Input` and add `ijl15.lib` (this file is created when compiling LOMNHook). For mods in the LOMNHook repository, use `$(OutDir)..\ijl15.lib`.

If you are making a mod in the LOMNHook repository, please set the output directories (under `General`) to the following:

`Debug` `x86`: `<your game folder>\mods\`
`Release` `x86`: `$(SolutionDir)bin\$(Configuration)\mods\`

Then, add this starter code in the main C++ file:
```
#include "HookMod.h"

extern "C" {
	__declspec(dllexport) LOMNHook::HookMod* HookmodInit() {
		return nullptr;
	}
}
```

Now, it is up to you to create a subclass of `LOMNHook::HookMod` and return a pointer to an instance from your `HookmodInit()` function.

Mod Extension Points
--------------------

Start off by overriding one of the virtual methods in your HookMod subclass.

To hook methods with MinHook (TODO: Give example here), start out doing that as early as possible (`OnPreInit()`) 

To add an `ScProcess` to the global list, do that in your `OnPostSetUp()`, as this is as soon as the global process list is available.