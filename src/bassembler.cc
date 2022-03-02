#include <bencoder.hpp>
#include <stdio.h>


void BEncoder::add_byte(unsigned char byte){
	fwrite(&byte, sizeof(unsigned char), 1, ofile);
    cpos++;
    //printf("%02x",byte);
}

void BEncoder::add_int(int number, int endianess){
    (void)endianess;
	fwrite(&number, sizeof(int), 1, ofile);
    cpos += 4;
    //printf("%08x", cnumber);
}

void BEncoder::add_short(int number, int endianess){
    (void)endianess;
	fwrite(&number, sizeof(short), 1, ofile);
    cpos += 2;
    //printf("[%04x]", cnumber);
}

void BEncoder::add_imm(struct inst_operand *operand, int endianess){
    (void)endianess;
    if (operand->type != INST_OPERAND_TYPE_IMM){
        return;
    }
    switch (operand->size){
        case 32:
            add_int(operand->value, endianess);
            break;
        case 16:
            add_short(operand->value, endianess);
            break;
        case 8:
            add_byte(operand->value);
            break;
    }
}
