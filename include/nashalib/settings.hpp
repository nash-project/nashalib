#pragma once

#define global_label 1
#define local_label 2

namespace nashalib{

enum class architecture{
	x86,
};
enum class format{
	elf32,
};

enum class section{
	_data,
	_text,
};

}