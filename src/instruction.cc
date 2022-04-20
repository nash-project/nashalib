#include <nashalib/instruction.hpp>
#include <stdlib.h>
#include <string.h>
#include <iostream>

namespace nashalib{


void new_operand(struct inst *i, struct inst_operand *operand){
	i->operands.push_back(operand);
}

struct inst_operand* create_reg(enum registers reg){

	struct inst_operand * op = (struct inst_operand*)malloc(sizeof(struct inst_operand));
	op->val.value = (int)reg;
    op->size = registers_table[(int)reg].size;

	if (registers_table[(int)reg].is_segment){
		op->type = INST_OPERAND_TYPE_SREG;
	}
	else{
		op->type = INST_OPERAND_TYPE_REG;
	}
	
	return op;
}

struct inst_operand* create_mem(int mem){
	struct inst_operand * op = (struct inst_operand*)malloc(sizeof(struct inst_operand));
	op->val.value = mem;
	op->type = INST_OPERAND_TYPE_MEM;
    op->reg = false;
	return op;
}

struct inst_operand* create_mem_reg(enum registers reg){
    struct inst_operand* op = (struct inst_operand*)malloc(sizeof(struct inst_operand));
    op->val.value = (int)reg;
    op->type = INST_OPERAND_TYPE_MEM;
    op->reg = true;
    op->size = registers_table[(int)reg].size;
    return op;
}

struct inst_operand* create_imm(int imm, int size){
	struct inst_operand * op = (struct inst_operand*)malloc(sizeof(struct inst_operand));
	op->val.value = imm;
	op->type = INST_OPERAND_TYPE_IMM;
    op->size = size;
	return op;
}
void free_instruction(struct inst* inst_){
	for (int x = 0; x < (int)inst_->operands.size(); x++){

		if (inst_->operands[x]->type == INST_OPERAND_TYPE_SCALE){

			if (inst_->operands[x]->sib_info.base->type == INST_OPERAND_TYPE_IMM){
				free(inst_->operands[x]->sib_info.base);
			}
			free(inst_->operands[x]);
		}
	}
    free(inst_);
}

struct inst_operand* create_scale_reg(struct inst_operand* base, registers index, unsigned char scale){

	struct inst_operand *op = (struct inst_operand*)malloc(sizeof(struct inst_operand));
	op->type = INST_OPERAND_TYPE_SCALE;
	op->size = registers_table[(int)index].size;
	op->sib_info.base = base;
	op->sib_info.sib_byte.index = registers_table[(int)index].reg;
	op->val.value = -1;

	switch (scale){
		case 1:
			op->sib_info.sib_byte.scale = 0b00;
			break;
		case 2:
			op->sib_info.sib_byte.scale = 0b01;
			break;
		case 4:
			op->sib_info.sib_byte.scale = 0b10;
			break;
		case 8:
			op->sib_info.sib_byte.scale = 0b11;
			break;
		default:
			return NULL;
			break;
	}
	return op;
}

struct inst_operand * create_label(std::string label){
	struct inst_operand * op = (struct inst_operand*)malloc(sizeof(struct inst_operand));
	op->val.label = label;
	op->type = INST_OPERAND_TYPE_LABEL;
    op->size = 32; // we just assume its 32 bit because we only support x86_32 atm
	return op;
}

}