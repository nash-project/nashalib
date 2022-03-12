#include <assembler.hpp>
#include <registers.hpp>
#include <stdlib.h>
#include <iostream>
#include <chrono>


void test(assembler::Assembler* assembler){

    struct inst * instruction = assembler->mInstruction(mnemonic::PUSH, create_reg(registers::cs));

    assembler->encode(instruction);

    assembler->freeInstruction(instruction);


    struct inst * instruction0 = assembler->mInstruction(mnemonic::ADD, create_reg(registers::cx), create_reg(registers::ax));

    assembler->encode(instruction0);

    assembler->freeInstruction(instruction0);


    struct inst * instruction1 = assembler->mInstruction(mnemonic::ADD, create_reg(registers::ax), create_imm(255, 16));



    assembler->encode(instruction1); // 66 81 c1 ff 00

    assembler->freeInstruction(instruction1);
}

int main(){

    assembler::Assembler *assembler = new assembler::Assembler(assembler::architecture::x86, 32);

    struct inst_operand * op1 = create_scale_reg(create_reg(registers::ecx), registers::ebx, 2);

    if (op1 == NULL){
        return 1;
    }

    struct inst * instruction = assembler->mInstruction(mnemonic::ADD,create_reg(registers::eax), op1);

    assembler->encode(instruction);

    assembler->freeInstruction(instruction);

    // mov eax, ecx + (ebx * 2)

    return 0;
}



