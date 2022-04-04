#include <assembler.hpp>
#include <registers.hpp>
#include <stdlib.h>
#include <iostream>
#include <settings.hpp>
#include <Data.hpp>


int main(){

    int data = 1;

    assembler::Assembler *assembler = new assembler::Assembler(architecture::x86, 32, format::elf32);

    Data *_data = new Data((unsigned char*)&data, sizeof(int), global_label, "_msg");


    assembler->add_label("_start", global_label);


    assembler->new_data(_data);



    struct inst_operand * op1 = create_scale_reg(create_reg(registers::ecx), registers::ebx, 2);

    if (op1 == NULL){
        return 1;
    }


    // add eax, [ecx + (ebx * 2)]; WORKS. 03 04 58 
    // =======================================================

    struct inst * instruction = assembler->mInstruction(mnemonic::ADD, create_reg(registers::eax), op1); 

    assembler->encode(instruction);

    assembler->freeInstruction(instruction);

    // =======================================================



    // add eax, [ 100 + (ebx * 2)]; WORKS. 03 04 5D 64  00 00 00 
    // =======================================================

    op1 = create_scale_reg(create_imm(100, 32), registers::ebx, 2);

    if (op1 == NULL){
        return 1;
    }
    
    instruction = assembler->mInstruction(mnemonic::ADD, create_reg(registers::eax), op1); 

    assembler->encode(instruction);

    assembler->freeInstruction(instruction);

    // ======================================================

    //add eax, [ebx+ecx*2]; WORKED. 0x03, 0x04, 0x4B
    // ======================================================

    op1 = create_scale_reg(create_reg(registers::ebx), registers::ecx, 2);

    if (op1 == NULL){
        return 1;
    }
    
    instruction = assembler->mInstruction(mnemonic::ADD, create_reg(registers::eax), op1); 

    assembler->encode(instruction);

    assembler->freeInstruction(instruction);

    assembler->write("output.o");

    delete assembler;

    // ======================================================
    std::cout << "Raw flat binary output: temp.out\n";
    std::cout << "Run `make disa` to show objdump of temp.out\n";
    return 0;
}



