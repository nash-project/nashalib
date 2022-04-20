#pragma once
#include <nashalib/settings.hpp>
#include <nashalib/label.hpp>

namespace nashalib{

class relocation_entry{
public:
	relocation_entry(section _section, int _offset): section(_section), offset(_offset) {}
	section section;
	int offset;
};
}