#pragma once
#include <nashalib/bencoder.hpp>
#include <nashalib/arch/x86/32/encoder.hpp>
#include <nashalib/instruction.hpp>
#include <nashalib/settings.hpp>
#include <nashalib/label.hpp>
#include <nashalib/Data.hpp>
#include <vector>
namespace nashalib{

	typedef std::vector<inst_operand*> operand_list;

	class Assembler{
		public:
			BEncoder * encoder;
			Assembler(architecture, int, format);
			void encode(struct inst*);
			void freeInstruction(struct inst*);
			struct inst * mInstruction(mnemonic mnemonic_, operand_list&);
		
			int label_as_relative(std::string);
			int get_label(std::string);
			Label* get_label_obj(std::string);
			void add_label(std::string, int);
			void write(std::string);
			void new_data(Data*);
		

		private:
			FILE* ofile;
	};


};