#include <nashalib/assembler.hpp>
#include <nashalib/registers.hpp>
#include <stdlib.h>
#include <iostream>
#include <nashalib/settings.hpp>
#include <nashalib/Data.hpp>

int main(){

    struct nashalib::inst* instruction = NULL;
    nashalib::Data * msg_data = new nashalib::Data((unsigned char*)"hello\n", 6, local_label, "msg");
    nashalib::operand_list operands;
    nashalib::operand_list call_operands;
    nashalib::operand_list mov_operands;
    nashalib::operand_list int_operands;
    nashalib::operand_list ret_operands;

    nashalib::Assembler *assembler = new nashalib::Assembler(nashalib::architecture::x86, 32, nashalib::format::elf32);

    assembler->new_data(msg_data);

    assembler->add_label("_start", global_label);

    call_operands.push_back(nashalib::create_label("print"));
    instruction = assembler->mInstruction(nashalib::mnemonic::CALL, call_operands);
    assembler->encode(instruction);
    assembler->freeInstruction(instruction);



    mov_operands.push_back(nashalib::create_reg(nashalib::registers::eax));
    mov_operands.push_back(nashalib::create_imm(1,32));
    instruction = assembler->mInstruction(nashalib::mnemonic::MOV, mov_operands);
    assembler->encode(instruction);
    assembler->freeInstruction(instruction);

    int_operands.push_back(nashalib::create_imm(0x80, 8));
    instruction = assembler->mInstruction(nashalib::mnemonic::INT, int_operands);
    assembler->encode(instruction);
    assembler->freeInstruction(instruction);


    assembler->add_label("print", local_label);


    nashalib::operand_list mov_operands1;
    nashalib::operand_list mov_operands2;
    nashalib::operand_list mov_operands3;
    nashalib::operand_list mov_operands4;
    nashalib::operand_list int_operands1;

    mov_operands1.push_back(nashalib::create_reg(nashalib::registers::eax));
    mov_operands1.push_back(nashalib::create_imm(4, 32));
    instruction = assembler->mInstruction(nashalib::mnemonic::MOV, mov_operands1);
    assembler->encode(instruction);
    assembler->freeInstruction(instruction);


    mov_operands2.push_back(nashalib::create_reg(nashalib::registers::ebx));
    mov_operands2.push_back(nashalib::create_imm(1, 32));
    instruction = assembler->mInstruction(nashalib::mnemonic::MOV, mov_operands2);
    assembler->encode(instruction);
    assembler->freeInstruction(instruction);


    mov_operands3.push_back(nashalib::create_reg(nashalib::registers::ecx));
    mov_operands3.push_back(nashalib::create_label("msg"));
    instruction = assembler->mInstruction(nashalib::mnemonic::MOV, mov_operands3);
    assembler->encode(instruction);
    assembler->freeInstruction(instruction);

    mov_operands4.push_back(nashalib::create_reg(nashalib::registers::edx));
    mov_operands4.push_back(nashalib::create_imm(6, 32));
    instruction = assembler->mInstruction(nashalib::mnemonic::MOV, mov_operands4);
    assembler->encode(instruction);
    assembler->freeInstruction(instruction);


    int_operands1.push_back(nashalib::create_imm(0x80, 8));
    instruction = assembler->mInstruction(nashalib::mnemonic::INT, int_operands1);
    assembler->encode(instruction);
    assembler->freeInstruction(instruction);


    instruction = assembler->mInstruction(nashalib::mnemonic::RETN, ret_operands);
    assembler->encode(instruction);
    assembler->freeInstruction(instruction);


    assembler->write("output.o");

    return 0;
}



