#pragma once

class Data{
public:
	Data(unsigned char * _data, int _size, int _vis,std::string _label): data(_data), size(_size), vis(_vis), label(_label) {}

	unsigned char * data;
	int size;
	std::string label;
	int vis;
};