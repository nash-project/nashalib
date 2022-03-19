#include <instruction.hpp>
#include <stdlib.h>
#include <string.h>
#include <iostream>



extern "C" void new_operand(struct inst *i, struct inst_operand *operand){
	i->operands.push_back(operand);
}

extern "C" struct inst_operand* create_reg(enum registers reg){

	struct inst_operand * op = (struct inst_operand*)malloc(sizeof(struct inst_operand));
	op->value = (int)reg;
    op->size = registers_table[(int)reg].size;

	if (registers_table[(int)reg].is_segment){
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
	for (int x = 0; x < inst_->operands.size(); x++){

		if (inst_->operands[x]->type == INST_OPERAND_TYPE_SCALE){

			if (inst_->operands[x]->sib_info.base->type == INST_OPERAND_TYPE_IMM){
				free(inst_->operands[x]->sib_info.base);
			}
			free(inst_->operands[x]);
		}
	}
    free(inst_);
}

extern "C" struct inst_operand* create_scale_reg(struct inst_operand* base, registers index, unsigned char scale){

	struct inst_operand *op = (struct inst_operand*)malloc(sizeof(struct inst_operand));
	op->type = INST_OPERAND_TYPE_SCALE;
	op->size = registers_table[(int)index].size;
	op->sib_info.base = base;
	op->sib_info.sib_byte.index = registers_table[(int)index].reg;

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




	/*
	switch (base->type){
		case INST_OPERAND_TYPE_REG:
			sb.base = registers_table[(int)base->value].reg;
			break;
		case INST_OPERAND_TYPE_IMM:
			//sb.base
			// TODO: IMPLEMENT
			return NULL;
			break;
		default:
			return NULL;
			break;
	}
	op->sib_byte = *(unsigned char*)&sb;*/
	return op;
}