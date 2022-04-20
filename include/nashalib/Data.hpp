#pragma once

namespace nashalib{

class Data{
public:
	Data(unsigned char * _data, int _size, int _vis,std::string _label): data(_data), size(_size),  label(_label), vis(_vis) {}

	unsigned char * data;
	int size;
	std::string label;
	int vis;
};

}