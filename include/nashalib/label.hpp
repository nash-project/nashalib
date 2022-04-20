#pragma once
#include <nashalib/settings.hpp>
#include <string>
namespace nashalib{

class Label{
public:

	Label(int _offset, int _vis, section s): offset(_offset), visibility(_vis), _section(s) {}

	int offset;
	int visibility;
	section _section;
};

struct label_map_entry{
	int pos;
	char* label;
	bool relative;
};

}