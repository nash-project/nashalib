#pragma once
#include <bencoder.hpp>
#include <arch/x86/32/encoder.hpp>
#include <instruction.hpp>
#include <settings.hpp>
#include <label.hpp>
#include <Data.hpp>

namespace assembler{

	class Assembler{
		public:
			BEncoder * encoder;
			Assembler(architecture, int, format);
			void encode(struct inst*);
			void freeInstruction(struct inst*);
			struct inst * mInstruction(mnemonic, struct inst_operand* op0 = NULL, 
										struct inst_operand *op1 = NULL, struct inst_operand* op2 = NULL);
		
			int label_as_relative(std::string);
			int get_label(std::string);
			void add_label(std::string, int);
			void write(std::string);
			void new_data(Data*);
		private:
			FILE* ofile;
	};


};