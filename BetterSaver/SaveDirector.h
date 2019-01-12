#pragma once

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
}