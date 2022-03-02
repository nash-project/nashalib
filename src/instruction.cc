#include <instruction.hpp>
#include <stdlib.h>
#include <string.h>
#include <iostream>


extern "C" void new_operand(struct inst *i, struct inst_operand *operand){
	memcpy((void*)&i->operands[i->Noperands], (void*)operand, sizeof(struct inst_operand));
    free(operand);
	i->Noperands++;
}

extern "C" struct inst_operand* create_reg(enum registers reg){

	struct inst_operand * op = (struct inst_operand*)malloc(sizeof(struct inst_operand));
	op->value = (int)reg;
    op->size = registers_table[(int)reg].size;

	if (registers_table[(int)reg].is_segment){
		//std::cout << "is segment register\n";
		op->type = INST_OPERAND_TYPE_SREG;
	}
	else{
		op->type = INST_OPERAND_TYPE_REG;
	}
	
	return op;
}

extern "C" struct inst_operand* create_mem(int mem){
	struct inst_operand * op = (struct inst_operand*)malloc(sizeof(struct inst_operand));
	op->value = mem;
	op->type = INST_OPERAND_TYPE_MEM;
    op->reg = false;
	return op;
}

extern "C" struct inst_operand* create_mem_reg(enum registers reg){
    struct inst_operand* op = (struct inst_operand*)malloc(sizeof(struct inst_operand));
    op->value = (int)reg;
    op->type = INST_OPERAND_TYPE_MEM;
    op->reg = true;
    op->size = registers_table[(int)reg].size;
    return op;
}

extern "C" struct inst_operand* create_imm(int imm, int size){
	struct inst_operand * op = (struct inst_operand*)malloc(sizeof(struct inst_operand));
	op->value = imm;
	op->type = INST_OPERAND_TYPE_IMM;
    op->size = size;
	return op;
}
extern "C" void free_instruction(struct inst* inst_){
    free(inst_);
}