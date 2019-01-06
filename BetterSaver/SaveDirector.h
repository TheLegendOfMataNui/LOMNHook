#pragma once

namespace SaveDirector {
	void Save();
	char Load();
	void ResetData();

	bool GetBooleanValue(const unsigned short& ID);
	void SetBooleanValue(const unsigned short& ID, const bool& value);
	bool RemoveBooleanValue(const unsigned short& ID);
	bool ToggleBooleanValue(const unsigned short& ID);

	int GetIntegerValue(const unsigned short& ID);
	void SetIntegerValue(const unsigned short& ID, const int& value);
	int IncrementIntegerValue(const unsigned short& ID);
	int DecrementIntegerValue(const unsigned short& ID);
	bool RemoveIntegerValue(const unsigned short& ID);

	float GetFloatValue(const unsigned short& ID);
	void SetFloatValue(const unsigned short& ID, const float& value);
	bool RemoveFloatValue(const unsigned short& ID);

	void ExecuteMicrocodeInstruction(const unsigned long& instruction);
}