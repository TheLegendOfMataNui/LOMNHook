#pragma once

#include <vector>

#include "Memory.h"

namespace LOMNHook
{
	namespace Native
	{
		template <typename T>
		struct Vector
		{
			unsigned int AllocatedCount;
			unsigned int Count;
			T* Data;

			Vector(int initialCount);
			void PushBack(T value);
		};
	}
}

template <typename T>
LOMNHook::Native::Vector<T>::Vector(int initialCount)
{
	Count = 0;
	AllocatedCount = initialCount;
	//Data = (T*)operator new(initialCount * sizeof(T));
    Data = (T*)SrMalloc(sizeof(T) * initialCount);
}

template <typename T>
void LOMNHook::Native::Vector<T>::PushBack(T value)
{
	if (this->Count >= this->AllocatedCount) {
		T* oldData = this->Data;
		int newCapacity = this->AllocatedCount * 2;
		if (newCapacity == 0)
			newCapacity = 1;

		this->Data = (T*)SrMalloc(sizeof(T) * newCapacity);
		for (int i = 0; i < this->Count; i++)
			this->Data[i] = oldData[i];

		this->AllocatedCount = newCapacity;

		SrFree(oldData);
	}
	this->Data[Count] = value;
	Count++;
}