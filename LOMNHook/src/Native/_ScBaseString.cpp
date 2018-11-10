#include "stdafx.h"

#include "Native/_ScBaseString.h"

using namespace LOMNHook::Native;

_ScBaseString::_ScBaseString() {
	this->Data = nullptr;
	this->Length = 0;
}

_ScBaseString::_ScBaseString(const char* data) {
	this->Data = data;
	this->Length = strlen(data);
}