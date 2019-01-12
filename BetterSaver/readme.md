BetterSaver
===========

BetterSaver is a rewrite of the `GcSaver` LOMN subsystem. The goals are:
- A human-readable save file format
- More robustness and flexibility in interacting with save games from gameplay code and scripted cutscenes.

Design
------

The orginal GcSaver stored a bitfield of conditions, as follows:

bit 00: `khaka1`  
bit 01: `khaka2`  
bit 02: `khaka3`  
bit 03: `khakadone`  
bit 04: `kmsk1`  
bit 05: `kmsk2`  
bit 06: `kmsk3`  
bit 07: `kgly1`  
bit 08: `kgly2`  
bit 09: `kgly3`  
bit 10: `kitem1` and `kitem3`  
bit 11: `kitem2`  
bit 12: unused  
bit 13: `kquest1`  
bit 14: `kquest2`  
bit 15: `kquest3`  
bit 16: `kquest4`  
bit 17: `kquest5`  
bit 18: `kquest6`  
bit 19: `kquest7`  
bit 20: `kquest8`  
bit 21: `kquest9`  
bit 22: `kmisc1`  
bit 23: `kmisc2`  
bit 24: `kmisc3`  
bit 25: `kmisc4`  
bit 26: `kmisc5`  
bit 27: `kmisc6`  
bit 28: `kmisc7`  
bit 29: `kmisc8`  
bit 30: `kmisc9`  
bit 31: `krandom`

BetterSaver stores 3 dictionaries of saved values, each mapping a 16bit ID to a float, boolean, or integer value.
Each dictionary is isolated, meaning the same ID can be used independently for a float value, an integer value, and a boolean value.

There will be 3 APIs for BetterSaver. The main two are Native and OSI, with the same functionality, which is as follows:  

`bool GetBooleanValue(ushort ID)`  
`void SetBooleanValue(ushort ID, bool value)`  
`bool RemoveBooleanValue(ushort ID)`  
`bool ToggleBooleanValue(ushort ID)`  

`int GetIntegerValue(ushort ID)`  
`void SetIntegerValue(ushort ID, int value)`  
`int DecrementIntegerValue(ushort ID)`  
`int IncrementIntegerValue(ushort ID)`  
`bool RemoveIntegerValue(ushort ID)`  

`float GetFloatValue(ushort ID)`  
`void SetFloatValue(ushort ID, float value)`  
`bool RemoveFloatValue(ushort ID)`  

The Microcode API works by repurposing unused conversation flag bits into instructions that will be executed when the conversation is run.  
Care has been taken to make all-zeroes in the Microcode bits (the values that a legacy flag will have) equal the 'Boolean Set True' instruction, which mimics the legacy behavior.

bit 0: Type of value. 0 = Boolean, 1 = Integer.  
bit 1: Operation I. Boolean: 0 = Set, 1 = Toggle. Integer: 0 = Set, 1 = Increment or Decrement.  
bit 2: Operation II. Boolean: Set: 0 = True, 1 = False. Toggle: 0, Unused. Integer: Set: The value to be set to. Increment or Decrement: 0 = Increment, 1 = Decrement.  
bit 3: ID Mode. 0: Operate all non-Microcode bits that are set to 1 as their own ID, 1: Use all non-Microcode bits as a single 32-bit integer.

The Microcode for a conversation flag will be stored in bits 24-27. In other words, the above bits go here:  
`XXXX3210 XXXXXXXX XXXXXXXX XXXXXXXX` (big-endian)

This involves changing the behavior of `SetCondition` and `IsConditionSet`, as well as `Save`, `Load`, and `ResetData`.

Of these, `Save` and `Load` can be rewritten at will, and `ResetData` is trivial, but `SetCondition` and `IsConditionSet` are trickier to maintain compatibility with.

Legacy save conditions are accessed in two places: By native code in the conversation engine, and by OSI script, and we will take a different approach to grandfathering each.

Conversation Engine
-------------------

We will allocate booleans with IDs 0-31 as the storage for the conditions that the legacy system stored.

The conversation engine sets the condition flags in `GcSaver::UpdateConvMemory`. Thankfully, any time the flags are set, it is done by calling `GcSaver::SetCondition`, which we will hook.
However, the conversation flag requirements are directly checked against `GcSaver::sConvConditions`, which will need to be kept in sync with the rest of the system by special-casing IDs 0-31 in `SetBooleanValue` to update `GcSaver::sConvConditions`.
This means that while conversation setting flags are augmented with Microcode instructions, the conversation requirement flags remain unchanged.

The hooked `GcSaver::SetCondition` will interpret the given bitfield according to the Microcode API specified above, and make calls to the Native API to carry out the instruction.

OSI Calls
---------

With BetterSaver, OSI calls to `gcsaver::setcondition` and `gcsaver::isconditionset` are deprecated, and any call to them will be forwarded to `gcsaver::setbooleanvalue` and `gcsaver::getbooleanvalue`.