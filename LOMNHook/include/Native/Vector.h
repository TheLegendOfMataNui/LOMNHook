#pragma once

#include <vector>

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
	Data = (T*)operator new(initialCount * sizeof(T));
}

template <typename T>
void LOMNHook::Native::Vector<T>::PushBack(T value)
{
	this->Data[Count] = value;
	Count++;
}