#pragma once
#include <vector>
#include <map>
#include <instruction.hpp>
#include <string>
#include <endianess.hpp>
#include <stdio.h>
#include <settings.hpp>
#include <label.hpp>
#include <Data.hpp>


class BEncoder { // Base assembler extraction
public:

/**
 * encodes an instruction into machine code
 * @param instruction a pointer to an instruction
 */

	BEncoder(FILE *file, format __format): ofile(file), _format(__format) {}

	virtual void encode(struct inst* ) = 0;
	virtual void gen_bin(std::string) = 0;

	void add_byte(unsigned char);
	void add_int(int, int);
	void add_short(int, int);
	void add_imm(int,int, int);
	
	void add_label(std::string, int, section);
	void add_data(Data*);
	
	int get_cpos();
	int get_label(std::string);
	int get_data_cpos();

protected:
	int cpos;
	FILE* ofile;
	std::map<std::string, Label*> labels;
	std::vector<Data*> data;
	int data_cpos = 0;
	format _format;
};