#include <nashalib/arch/x86/32/opcodes.hpp>

namespace nashalib{

struct opcode_info opcode_table[] = {
    {true,0x80, 0, true, mnemonic::ADD, 2, 0 ,{
        {false, 8, 0, false, INST_OPERAND_TYPE_REG, NONE},
        {false, 8, 0, false, INST_OPERAND_TYPE_IMM, LITERAL}
    }},
    {true,0x89, 0, true, mnemonic::MOV, 2, 0 ,{
        {false, 32, 0, false, INST_OPERAND_TYPE_REG, NONE},
        {false, 32, 0, false, INST_OPERAND_TYPE_REG, NONE}
    }},
    {true, 0x81, 0, true, mnemonic::ADD, 2, 0, {
        {true, 16, 0, false, INST_OPERAND_TYPE_REG, NONE},
        {true, 16, 0, false, INST_OPERAND_TYPE_IMM, LITERAL}
    }},
    {true, 0x81, 0, true, mnemonic::ADD, 2, 0, {
        {false, 32, 0, false, INST_OPERAND_TYPE_REG, NONE},
        {false, 32, 0, false, INST_OPERAND_TYPE_IMM, LITERAL}
    }},
    {true, 0x01, 0, false, mnemonic::ADD, 2, 0, {
        {true, 16, 0, false, INST_OPERAND_TYPE_REG, NONE},
        {true, 16, 0, false, INST_OPERAND_TYPE_REG, NONE}
    }},
    {true , 0x0E, 0, false, mnemonic::PUSH, 1, 0, {
        {false, 16, (int)registers::cs, true, INST_OPERAND_TYPE_SREG, NONE}
    }},
    {true, 0x03, 0, false, mnemonic::ADD, 2, 0, {
        {false, 32, 0, false, INST_OPERAND_TYPE_REG, NONE},
        {false, 32, 0, false, INST_OPERAND_TYPE_SCALE, NONE}
    }},
    {true, 0xb8, 1, false, mnemonic::MOV, 2, 0, {
        {false, 32 , (int)registers::eax, true, INST_OPERAND_TYPE_REG, NONE},
        {false, 32 ,0, false, INST_OPERAND_TYPE_IMM, LITERAL},
    }},
    {true, 0xb9, 1, false, mnemonic::MOV, 2, 0, {
        {false, 32 , (int)registers::ecx, true, INST_OPERAND_TYPE_REG, NONE},
        {false, 32 ,0, false, INST_OPERAND_TYPE_IMM, LITERAL},
    }},
    {true, 0xba, 1, false, mnemonic::MOV, 2, 0, {
        {false, 32 , (int)registers::edx, true, INST_OPERAND_TYPE_REG, NONE},
        {false, 32 ,0, false, INST_OPERAND_TYPE_IMM, LITERAL},
    }},
    {true, 0xbb, 1, false, mnemonic::MOV, 2, 0, {
        {false, 32 , (int)registers::ebx, true, INST_OPERAND_TYPE_REG, NONE},
        {false, 32 ,0, false, INST_OPERAND_TYPE_IMM, LITERAL},
    }},
    {false, 0xcd, 0, false, mnemonic::INT, 1, 0, {
        {false, 8 , 0, false, INST_OPERAND_TYPE_IMM, LITERAL},
    }},
    {false, 0x68, 0, false, mnemonic::PUSH, 1, 0, {
        {false, 32 , 0, false, INST_OPERAND_TYPE_IMM, LITERAL},
    }},
    {false, 0xc3, 0, false, mnemonic::RETN, 0, 0, {
    }},
    {false, 0xe8, 0, false, mnemonic::CALL, 1, 0, {
        {false, 32 , 0, false, INST_OPERAND_TYPE_IMM, RELATIVE},
    }},
};

}