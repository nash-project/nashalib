#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <arch/x86/32/encoder.hpp>
#include <registers.hpp>
#include <arch/x86/32/opcodes.hpp>
#include <endianess.hpp>

struct modrm{
    unsigned char rm: 3;
    unsigned char reg: 3;
    unsigned char mod: 2;
}__attribute__((packed));

static int find_opcode(struct inst* inst_){
    bool all_operands_valid = false;
    for (int i = 0; i < OPCODE_TABLE_SIZE; i++){
        if (opcode_table[i].mnemonic != inst_->mnemonic){
            continue;
        }
        if (opcode_table[i].Noperands != inst_->Noperands){
            continue;
        }
        for (int ii = 0; ii <= inst_->Noperands; ii++){
            if ( (inst_->operands[ii].size == opcode_table[i].operands[ii].size) &&
                    (inst_->operands[ii].type == opcode_table[i].operands[ii].type)){

                if ( (opcode_table[i].operands[ii].use_literal_value)) { 
                    if (opcode_table[i].operands[ii].value == inst_->operands[ii].value){
                        all_operands_valid = true;
                    }
                    else{
                        all_operands_valid = false;
                        //printf("Incorrect operand value %d\n", ii);
                        break;
                    }
                }else{
                    all_operands_valid = true;
                }
            }
            else{
                all_operands_valid = false;
                //printf("Incorrent operand size %d\n", ii);
                break;
            }
        }
        if (all_operands_valid)
            return i;
    }

    return -1;
}


static inline void add_reg_2_modrm(int opcode_index, struct inst_operand* operand, struct modrm* _modrm, int *imm_offset_, int i){
    switch (operand->type){
        case INST_OPERAND_TYPE_REG:
            _modrm->reg = registers_table[operand->value].reg;        
            break;
        case INST_OPERAND_TYPE_IMM:
            (*imm_offset_) = i;
            if (opcode_table[opcode_index].rm_extends_opcode){
                _modrm->rm = opcode_table[opcode_index].rm;
            }
            break;
        default:
            break;
    }
    
}

static inline void set_rm_in_modrm(struct modrm *modrm_, unsigned char rm){
    modrm_->rm = rm;
}

static inline bool add_rm_2_modrm(int opcode_index, struct modrm * _modrm, struct inst_operand* operand, int i, int *imm_offset_){
    switch (operand->type){
        case INST_OPERAND_TYPE_SREG:
            return false;
            break;
        case INST_OPERAND_TYPE_IMM:
            _modrm->mod = 0b11;
            (*imm_offset_) = i;
            if (opcode_table[opcode_index].rm_extends_opcode){
                _modrm->rm = opcode_table[opcode_index].rm;
            }
            return true;
            break;
        case INST_OPERAND_TYPE_REG:
            _modrm->mod = 0b11;
            _modrm->rm = registers_table[operand->value].reg;
            return true;
            break;
        case INST_OPERAND_TYPE_MEM:
            _modrm->mod = 0b00;
            _modrm->rm = registers_table[operand->value].reg;
            return true;
            break;
        default:
            return false;
            break;
    }
}


void x86_32_Encoder::encode(struct inst* inst_){
    unsigned char opcode;

    struct modrm modrm_  = {0};
    unsigned char modrm_byte = 0;
    int modrm_index = 0;
    bool skip_rm = false; 

    bool needs_sib = false;
    unsigned char sib_byte;


    int operand_offset_of_imm = -1;


    bool already_done_66_prefix = false;

	int opcode_index = find_opcode(inst_);

    if (opcode_index == -1){
        printf("Failed to find correct opcode for instruction\n");
        return;  
    }
    opcode = opcode_table[opcode_index].opcode;


    for (int i = 0; i < inst_->Noperands; i++){
        if (!already_done_66_prefix && opcode_table[opcode_index].operands[i].needs_66_prefix){
            add_byte(0x66);
            already_done_66_prefix = true;
        }

        if (opcode_table[opcode_index].operands[i].use_literal_value);
        else if(inst_->operands[i].type == INST_OPERAND_TYPE_SCALE){
            needs_sib = true;
            sib_byte = inst_->operands[i].sib_byte;
            set_rm_in_modrm(&modrm_,0b100);
            modrm_index++;
            skip_rm = true;
        }
        else{
            if (opcode_table[opcode_index].which_does_rm_field_point_to == 0){
                if (modrm_index == 0) {
                    if (skip_rm){
                        if (add_rm_2_modrm(opcode_index, &modrm_, &inst_->operands[i], i, &operand_offset_of_imm))
                            modrm_index++;
                    }
                }
                else if (modrm_index == 1){
                    add_reg_2_modrm(opcode_index, &inst_->operands[i], &modrm_, &operand_offset_of_imm, i);
                    modrm_index++;
                }   
            }
            else{

                if (modrm_index == 1){
                    if (skip_rm){
                        if (add_rm_2_modrm(opcode_index, &modrm_, &inst_->operands[i], i, &operand_offset_of_imm))
                            modrm_index++;
                    }
                }
                else if (modrm_index == 0){
                    add_reg_2_modrm(opcode_index, &inst_->operands[i], &modrm_, &operand_offset_of_imm, i);
                        modrm_index++;
                }
            }
        }
        
    }

    add_byte(opcode);

    modrm_byte = *(unsigned char*)&modrm_;

    if (modrm_index != 0){
        add_byte(modrm_byte);
    }

    if (needs_sib){
        add_byte(sib_byte);
    }

    if (operand_offset_of_imm != -1){
        add_imm( &inst_->operands[operand_offset_of_imm], ENDIANESS__BIG_ENDIAN__);
    }
}

