#pragma once
#include <bencoder.hpp>
#include <arch/x86/32/encoder.hpp>
#include <instruction.hpp>
namespace assembler{

	enum class architecture{
		x86
	};


	class Assembler{
		public:
			BEncoder * encoder;
			Assembler(architecture, int);
			void encode(struct inst*);
			void freeInstruction(struct inst*);
			struct inst * mInstruction(mnemonic, struct inst_operand* op0 = NULL, 
										struct inst_operand *op1 = NULL, struct inst_operand* op2 = NULL);
		
		int label_as_relative(std::string);
		int get_label(std::string);
		void add_label(std::string);
		private:
			FILE* ofile;
	};


};