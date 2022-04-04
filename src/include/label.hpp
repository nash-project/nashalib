#pragma once
#include <settings.hpp>


class Label{
public:

	Label(int _offset, int _vis, section s): offset(_offset), visibility(_vis), _section(s) {}

	int offset;
	int visibility;
	section _section;
};