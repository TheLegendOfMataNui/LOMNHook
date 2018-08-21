
Rough Timeline
--------------

`InitFunc`s: Lots of initialization functions are queued up and then ran.
- `LOMNHook::PreInit()` is the first `InitFunc` (queued in `DllMain`)
- Game `InitFunc`s
- Mod `OnPreInit()`
- Any `InitFunc`s queued in `LOMNHook::PreInit()`
- Mod `OnPostInit()`
- `LOMNHook::PostInit()` (queued in `LOMNHook::PreInit()`)

`GcGame::DoSetUp()` is where the `ScProcess` list is created and populated.
- `LOMNHook::PreSetUp()`
  - Mod `OnPreSetUp()`
- Native `GcGame::DoSetUp()`
- `LOMNHook::PostSetUp()`
  - Mod `OnPostSetUp()`

Mod Extension Points
--------------------

Start off by overriding one of the virtual methods in your HookMod subclass.