#pragma once
#include <vector>

typedef void(__cdecl *ScInitHandler)(bool);

template<typename T>
struct ScVector {
	unsigned int AllocatedCount;
	unsigned int Count;
	T* Data;

public:
	ScVector(int initialCount) {
		Count = 0;
		AllocatedCount = initialCount;
		Data = (T*)operator new(initialCount * sizeof(T));
	}

	void PushBack(T value) {
		// Ignore any out of bounds issues... I'm lazy
		this->Data[Count] = value;
		Count++;
	}
};

HWND GetWindowHandle();