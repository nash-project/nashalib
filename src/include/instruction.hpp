#pragma once
#include <mnemonic.hpp>
#include <registers.hpp>

/**
 * the number of different type of operand types.
 */
#define OPERAND_TYPE_COUNT 5

/**
 *  All the operand types 
 */
enum inst_operand_type{
	INST_OPERAND_TYPE_REG = 0,
	INST_OPERAND_TYPE_SREG,
	INST_OPERAND_TYPE_IMM,
	INST_OPERAND_TYPE_MEM,
    INST_OPERAND_TYPE_SCALE,
};
/**
 * an instruction operand
 * 
 */
struct inst_operand{
	int value;
	enum inst_operand_type type;
	unsigned int size;
    bool reg; // used to check if operand is memory ref to address or register
    unsigned char sib_byte;
}__attribute__((packed));
/**
 * an instruction
 * 
 */
struct inst{
    mnemonic mnemonic;
	int Noperands;
	struct inst_operand operands[3];
	int Nprefixs;
	unsigned char prefixes[2];
}__attribute__((packed));



/**
 * adds created operand to instruction
 * @param instruction a pointer to the instruction you want to add the operand to
 * @param operand the operand you want to add to the instruction
 */
extern "C" void new_operand(struct inst*, struct inst_operand*);

/**
 * creates a memory reference operand
 * @param address this is the address of the memory
 */
extern "C" struct inst_operand* create_mem(int);

/**
 * creates memory reference of register operand
 * @param register a register
 */
extern "C" struct inst_operand* create_mem_reg(registers);

/**
 * creates register operand
 * @param register a register
 */
extern "C" struct inst_operand* create_reg(registers);

/** 
 * creates new operand with a type of immediate
 * @param immediate the integer value of the immediate
 * @param size the size of the immediate in bytes.
 * */
extern "C" struct inst_operand* create_imm(int, int);
/**
 * frees up all the memory that the instruct used
 * @param instruction a pointer to the instruction
 */
extern "C" void free_instruction(struct inst*);

/**
* creates new operand object that 
*/
extern "C" struct inst_operand* create_scale_reg(struct inst_operand*, registers, unsigned char);