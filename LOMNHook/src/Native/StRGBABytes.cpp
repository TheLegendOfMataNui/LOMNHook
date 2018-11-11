#include "stdafx.h"

#include <Native/StRGBABytes.h>

using namespace LOMNHook::Native;

StRGBABytes::StRGBABytes() {
	this->R = 0;
	this->G = 0;
	this->B = 0;
	this->A = 0;
}

StRGBABytes::StRGBABytes(unsigned char r, unsigned char g, unsigned char b, unsigned char a) {
	this->R = r;
	this->G = g;
	this->B = b;
	this->A = a;
}