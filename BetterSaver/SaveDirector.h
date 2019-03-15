#pragma once
#include "Native/ScIdentifier.h"
#include "Native/Vector.h"
#include "Native/ScFixedString.h"


namespace LOMNHook {
	namespace Native {
		enum SAVE_CONDITION : unsigned int
		{
			SAVE_CONDITION_HAKA1 = 0x1,
			SAVE_CONDITION_HAKA2 = 0x2,
			SAVE_CONDITION_HAKA3 = 0x4,
			SAVE_CONDITION_HAKADONE = 0x8,
			SAVE_CONDITION_MSK1 = 0x10,
			SAVE_CONDITION_MSK2 = 0x20,
			SAVE_CONDITION_MSK3 = 0x40,
			SAVE_CONDITION_GLY1 = 0x80,
			SAVE_CONDITION_GLY2 = 0x100,
			SAVE_CONDITION_GLY3 = 0x200,
			SAVE_CONDITION_ITEM1_ITEM3 = 0x400,
			SAVE_CONDITION_ITEM2 = 0x800,
			SAVE_CONDITION_UNUSED = 0x1000,
			SAVE_CONDITION_QUEST1 = 0x2000,
			SAVE_CONDITION_QUEST2 = 0x4000,
			SAVE_CONDITION_QUEST3 = 0x8000,
			SAVE_CONDITION_QUEST4 = 0x10000,
			SAVE_CONDITION_QUEST5 = 0x20000,
			SAVE_CONDITION_QUEST6 = 0x40000,
			SAVE_CONDITION_QUEST7 = 0x80000,
			SAVE_CONDITION_QUEST8 = 0x100000,
			SAVE_CONDITION_QUEST9 = 0x200000,
			SAVE_CONDITION_MISC1 = 0x400000,
			SAVE_CONDITION_MISC2 = 0x800000,
			SAVE_CONDITION_MISC3 = 0x1000000,
			SAVE_CONDITION_MISC4 = 0x2000000,
			SAVE_CONDITION_MISC5 = 0x4000000,
			SAVE_CONDITION_MISC6 = 0x8000000,
			SAVE_CONDITION_MISC7 = 0x10000000,
			SAVE_CONDITION_MISC8 = 0x20000000,
			SAVE_CONDITION_MISC9 = 0x40000000,
			SAVE_CONDITION_RANDOM = 0x80000000,
		};

		struct GtSaverData {
			ScIdentifier ID;
			ScIdentifier AreaID;
		};

		struct GtSaverTime {
			ScIdentifier AreaID;
			float Time;
		};

		struct GtConvMemory {
			ScIdentifier AreaID;
			ScIdentifier ID;
			unsigned char Number;
			char _pad[3];
		};

		struct GtConvFrame
		{
			DWORD a;
			DWORD b;
			DWORD c;
			DWORD d;
			ScFixedString<255> str_1;
			ScFixedString<255> str_2;
			ScFixedString<255> str_3;
			ScFixedString<255> str_4;
			ScFixedString<255> str_5;
			DWORD e;
		};

		struct GtConvInfo
		{
			DWORD line_side;
			SAVE_CONDITION condition_start;
			SAVE_CONDITION set_flags;
			ScIdentifier id;
			DWORD e;
			Vector<GtConvFrame> frames;
		};

		struct GtConvChar
		{
			ScIdentifier toa_name;
			ScIdentifier char_name;
			ScIdentifier char_count;
			Vector<GtConvInfo> conversations;
		};

	}
}

namespace SaveDirector {
	typedef unsigned short ValueID;

	void Save();
	char Load();
	void ResetData();

	// Gets the value with the given key, or false if there is none.
	bool GetBooleanValue(const ValueID& id);
	// Sets the value with the given key to the given value.
	// Adds the value if it is not present.
	void SetBooleanValue(const ValueID& id, const bool& value);
	// Removes the value with the given key, if present.
	// Returns whether there was a value to remove.
	bool RemoveBooleanValue(const ValueID& id);
	bool ToggleBooleanValue(const ValueID& id);

	int GetIntegerValue(const ValueID& id);
	void SetIntegerValue(const ValueID& id, const int& value);
	int IncrementIntegerValue(const ValueID& id);
	int DecrementIntegerValue(const ValueID& id);
	bool RemoveIntegerValue(const ValueID& id);

	float GetFloatValue(const ValueID& id);
	void SetFloatValue(const ValueID& id, const float& value);
	bool RemoveFloatValue(const ValueID& id);

	void ExecuteMicrocodeInstruction(const unsigned long& instruction);
	bool TestLegacyBoolean(const unsigned long& id);
}