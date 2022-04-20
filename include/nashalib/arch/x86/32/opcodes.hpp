#pragma once
#include <nashalib/instruction.hpp>

#define OPCODE_TABLE_SIZE 15


namespace nashalib{

#define RELATIVE 1
#define LITERAL 2
#define NONE 0

struct opcode_info_operand_entry{
    bool needs_66_prefix;
    unsigned int size;
    int value;
    bool use_literal_value;
    enum inst_operand_type type;
    int label_type;
}__attribute__((packed));


struct opcode_info{
    bool needs_modrm;
    unsigned char opcode;
    unsigned char which_does_rm_field_point_to: 1;
    bool rm_extends_opcode;
    enum mnemonic mnemonic;
    unsigned char Noperands; // doesn't have to be large 
    unsigned char rm: 3;
    struct opcode_info_operand_entry operands[3];
}__attribute__((packed));

extern "C" struct opcode_info opcode_table[];

}