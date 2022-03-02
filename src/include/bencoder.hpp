#pragma once
#include <vector>
#include <map>
#include <instruction.hpp>
#include <string>
#include <endianess.hpp>
#include <stdio.h>

class BEncoder { // Base assembler extraction
public:

/**
 * encodes an instruction into machine code
 * @param instruction a pointer to an instruction
 */

	BEncoder(FILE *file): ofile(file) {}

	virtual void encode(struct inst* ) = 0;
	void add_byte(unsigned char);
	void add_int(int, int);
	void add_short(int, int);
	void add_imm(struct inst_operand*, int);
	
protected:
	int cpos;
	FILE* ofile;
	std::map<std::string, int> labels;
};