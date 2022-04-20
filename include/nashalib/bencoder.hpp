#pragma once
#include <vector>
#include <map>
#include <nashalib/instruction.hpp>
#include <string>
#include <nashalib/endianess.hpp>
#include <stdio.h>
#include <nashalib/settings.hpp>
#include <nashalib/label.hpp>
#include <nashalib/Data.hpp>
#include <nashalib/relocation_entry.hpp>

namespace nashalib{

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
	void add_label(std::string, bool relative = false);


	Label* _add_label(std::string, int, section);
	void _add_data(Data*);
	int _get_cpos();
	int _get_label(std::string);
	Label* _get_label_obj(std::string);
	int _get_data_cpos();
	void _resolve_labels();
	

protected:
	int cpos;
	FILE* ofile;
	std::map<std::string, Label*> labels;
	std::vector<Data*> data;
	std::vector<relocation_entry*> reloctable_table;
	int data_cpos = 0;
	format _format;
	std::vector<struct label_map_entry*> referenced_labels_map;
};

}