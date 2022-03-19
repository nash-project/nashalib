#include <assembler.hpp>
#include <registers.hpp>
#include <stdlib.h>
#include <iostream>


int main(){

    assembler::Assembler *assembler = new assembler::Assembler(assembler::architecture::x86, 32);

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


    // ======================================================
    std::cout << "Raw flat binary output: temp.out\n";
    std::cout << "Run `make disa` to show objdump of temp.out\n";
    return 0;
}



