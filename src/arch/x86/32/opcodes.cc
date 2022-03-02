#include <arch/x86/32/opcodes.hpp>


struct opcode_info opcode_table[] = {

    {0x80, 0, true, mnemonic::ADD, 2, 0 ,{
        {false, 8, 0, false, INST_OPERAND_TYPE_REG},
        {false, 8, 0, false, INST_OPERAND_TYPE_IMM}
    }},

    {0x81, 0, true, mnemonic::ADD, 2, 0, {
        {true, 16, 0, false, INST_OPERAND_TYPE_REG},
        {true, 16, 0, false, INST_OPERAND_TYPE_IMM}
    }},

    {0x01, 0, false, mnemonic::ADD, 2, 0, {
        {true, 16, 0, false, INST_OPERAND_TYPE_REG},
        {true, 16, 0, false, INST_OPERAND_TYPE_REG}
    }},

    {0x0E, 0, false, mnemonic::PUSH, 1, 0, {
        {false, 16, (int)registers::cs, true, INST_OPERAND_TYPE_SREG}
    }}

};