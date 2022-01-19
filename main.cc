#include <iostream>
#include <registers.hpp>
#include <instruction.hpp>
#include <instructions.hpp>
#include <utils/bin.hpp>
#include <timer.hpp>
#include <stdlib.h>
#include <stdint.h>


/* 
    's' bit is the last bit of the opcode. the d bit is the second to last bit in the opcode
*/

#define REGISTER_BIT32_SIZE     32
#define REGISTER_BIT16_SIZE     16
#define REGISTER_BIT8_SIZE      8

#define MOD11   0b11000000
#define MOD00   0b00000000 
#define MOD01   0b01000000  
#define MOD10   0b10000000 


enum class options{
    number,
    reg
};


void print_instruction(struct instruction *instruction){  
    unsigned char c = instruction->instruction[0];
    for (unsigned int i = 0 ;i <= instruction->len - 1; i++){
        c = instruction->instruction[i];
        printf("%x ", c);
    }
    printf("\n");
}

unsigned char *chunk_uint64_ct_little_endian(uint64_t value){
    unsigned char* chunks = (unsigned char*)malloc(9);
    unsigned char e;
    for (int g = 0; g <= 8; g++){
        if (g == 0){
            e = (value & 0xFF);
        }
        else{
            e = ((value >> (8 * g)) & 0xFF);            
        }
        chunks[g] = e;
    }
    return chunks;
}

unsigned char *chunk_uint16_ct_little_endian(uint16_t value){
    unsigned char* chunks = (unsigned char*)malloc(3);
    unsigned char e;
    for (int g = 0; g <= 2; g++){
        if (g == 0){
            e = (value & 0xFF);
        }
        else{
            e = ((value >> (8 * g)) & 0xFF);            
        }
        chunks[g] = e;
    }
    return chunks;
}

unsigned char *chunk_uint32_ct_little_endian(uint32_t value){
    unsigned char* chunks = (unsigned char*)malloc(5);
    unsigned char e;
    for (int g = 0; g <= 4; g++){
        if (g == 0){
            e = (value & 0xFF);
        }
        else{
            e = ((value >> (8 * g)) & 0xFF);            
        }
        chunks[g] = e;
    }
    return chunks;
}

inline int register_bit_size(registers reg){
    switch (reg){

        // 32 bits

        case registers::EAX:
        case registers::ECX:
        case registers::EDX:
        case registers::EBX:
        case registers::ESP:
        case registers::EBP:
        case registers::ESI:
        case registers::EDI:
            return REGISTER_BIT32_SIZE;


        // 16 bits

        case registers::AX:
        case registers::CX:
        case registers::DX:
        case registers::BX:
        case registers::SP:
        case registers::BP:
        case registers::SI:
        case registers::DI:
            return REGISTER_BIT16_SIZE;

        // 8 bits

        // low bytes
        case registers::AL:
        case registers::CL:
        case registers::DL:
        case registers::BL:

        // high bytes
        case registers::AH:
        case registers::CH:
        case registers::DH:
        case registers::BH:
            return REGISTER_BIT8_SIZE;
        default:
            return 0;
    }
    return 0;
}

inline unsigned char get_register_code(registers reg){

    switch (reg){
        case registers::AL:
        case registers::AX:
        case registers::EAX:
            return AX_REGISTERS_WL;
        case registers::CL:
        case registers::CX:
        case registers::ECX:
            return CX_REGISTERS_WL;
        case registers::DL:
        case registers::DX:
        case registers::EDX:
            return DX_REGISTERS_WL;
        case registers::BL:
        case registers::BX:
        case registers::EBX:
            return BX_REGISTERS_WL;
        case registers::AH:
        case registers::SP:
        case registers::ESP:
            return SP_REGISTERS_W_AH;
        case registers::CH:
        case registers::BP:
        case registers::EBP:
            return BP_REGISTERS_W_CH;
        case registers::BH:
        case registers::DI:
        case registers::EDI:
            return DI_REGISTERS_W_BH;
        case registers::DH:
        case registers::SI:
        case registers::ESI:
            return SI_REGISTERS_W_DH;
    }
    return 0b000;
}

inline unsigned char mov_number_in2_reg_opcode(registers reg){
    switch (reg){
        case registers::AL:
            return 0xb0;
        case registers::CL:
            return 0xb1;
        case registers::DL:
            return 0xb2;
        case registers::BL:
            return 0xb3;


        case registers::AH:
            return 0xb4;
        case registers::CH:
            return 0xb5;
        case registers::DH:
            return 0xb6;
        case registers::BH:
            return 0xb7;

        case registers::AX:
        case registers::EAX:
            return 0xb8;
        case registers::CX:
        case registers::ECX:
            return 0xb9;
        case registers::DX:
        case registers::EDX:
            return 0xba;
        case registers::BX:
        case registers::EBX:
            return 0xbb;
        case registers::SP:
        case registers::ESP:
            return 0xbc;
        case registers::BP:
        case registers::EBP:
            return 0xbd;
        case registers::SI:
        case registers::ESI:
            return 0xbc;
        case registers::DI:
        case registers::EDI:
            return 0xbf;        
    }
    return 0;
}

struct instruction *mov(registers f, registers s){

    struct instruction *instruction = (struct instruction*)malloc(sizeof(struct instruction));

    unsigned char opcode; 
    int reg_size; 


    opcode = MOV_INSTRUCTION_OPCODE;

    reg_size = register_bit_size(f);

    if(reg_size == REGISTER_BIT32_SIZE){
        opcode =  set_bit(opcode, 0); // set s bit
    }
    else if(reg_size == REGISTER_BIT16_SIZE){
        opcode =  set_bit(opcode, 0); // set s bit

        instruction->instruction[instruction->len++] = 0x66;
    }

    instruction->instruction[instruction->len++] = opcode;

    unsigned char f_reg =      get_register_code(f);
    unsigned char s_reg =      get_register_code((registers)s);

    unsigned char modrm = cat_binary(MOD11, s_reg, 3, 2);

    modrm = cat_binary(modrm, f_reg, 3, 5);

    instruction->instruction[instruction->len++] = modrm;
    

    return instruction;
}



int main(){


    /*Timer t;

    for (int e = 0;e <= 5;e++){

        t.reset();

        mov(registers::AX, registers::DX);

        std::cout << "Time elapsed: " << t.elapsed_nanoseconds() << " nanoseconds\n";
    }*/
    struct instruction* i = mov( registers::ECX, registers::EAX);

    print_instruction(i);

    //uint16_t value = 0x1122;
    //unsigned char e = (value & 0xFF); // 0x22
    //unsigned char j = ((value >> 8) & 0xFF); // 0x11

    //printf("%x %x\n",j);

    /*unsigned char* c = chunk_uint16_ct_little_endian(0x2233);

    for(int t = 0; t <= 2; t++){
        printf("%x ", c[t]);
    }

    printf("\n");*/

    //binary(j);

}