#include <assembler.hpp>
#include <stdio.h>




namespace assembler{
	Assembler::Assembler(architecture arch, int bsz){

		ofile = fopen("temp.out", "wb");

		if (arch == architecture::x86 && bsz == 32){
			encoder = new x86_32_Encoder(ofile);
		}
	}
	void Assembler::encode(struct inst* instruction){
		encoder->encode(instruction);
	}
	struct inst * Assembler::mInstruction(mnemonic mnemonic_, struct inst_operand* op0, 
										struct inst_operand *op1 , struct inst_operand* op2){

		struct inst * instruction = (struct inst*)calloc(1, sizeof(struct inst));
		instruction->mnemonic = mnemonic_;

		if (op0 != NULL){
			new_operand(instruction, op0);
		}

		if (op1 != NULL){
			new_operand(instruction, op1);
		}

		if (op2 != NULL){
			new_operand(instruction, op2);
		}

		return instruction;
	}
	void Assembler::freeInstruction(struct inst* instruction){
		if (instruction == NULL){
			return;
		}
		free_instruction(instruction);
	}
};