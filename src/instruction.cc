#include <instruction.hpp>
#include <stdlib.h>
#include <string.h>
#include <iostream>


struct sib_byte{
	unsigned char base: 3;
	unsigned char index: 3;
	unsigned char scale: 2;
}__attribute__((packed)); // changed here

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

extern "C" struct inst_operand* create_scale_reg(struct inst_operand* base, registers index, unsigned char scale){
	struct inst_operand *op = (struct inst_operand*)malloc(sizeof(struct inst_operand));
	struct sib_byte sb;
	op->type = INST_OPERAND_TYPE_SCALE;
	op->size = base->size;
	switch (scale){
		case 1:
			sb.scale = 0b00;
			break;
		case 2:
			sb.scale = 0b01;
			break;
		case 4:
			sb.scale = 0b10;
			break;
		case 8:
			sb.scale = 0b11;
			break;
		default:
			return NULL;
			break;
	}
	sb.index = registers_table[(int)index].reg;
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
	op->sib_byte = *(unsigned char*)&sb;
	return op;
}