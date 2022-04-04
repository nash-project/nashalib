#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <arch/x86/32/encoder.hpp>
#include <registers.hpp>
#include <arch/x86/32/opcodes.hpp>
#include <endianess.hpp>
#include <seegul/seegul.h>
#include <fstream>
#include <iostream>
#include <settings.hpp>



struct modrm{
    unsigned char rm: 3;
    unsigned char reg: 3;
    unsigned char mod: 2;
}__attribute__((packed));

struct imm{
    int imm;
    bool needs_imm;
    int size;
}__attribute__((packed));


static int find_opcode(struct inst* inst_){
    bool all_operands_valid = false;
    for (int i = 0; i < OPCODE_TABLE_SIZE; i++){
        if (opcode_table[i].mnemonic != inst_->mnemonic){
            continue;
        }
        if (opcode_table[i].Noperands != inst_->operands.size()){
            continue;
        }
        for (int ii = 0; ii < inst_->operands.size(); ii++){
            if ( (inst_->operands[ii]->size == opcode_table[i].operands[ii].size) &&
                    (inst_->operands[ii]->type == opcode_table[i].operands[ii].type)){

                if ( (opcode_table[i].operands[ii].use_literal_value)) { 
                    if (opcode_table[i].operands[ii].value == inst_->operands[ii]->value){
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


static inline void set_mod_in_modrm(struct modrm *modrm_, unsigned char mod){
    modrm_->mod = mod;
}

static inline void add_reg_2_modrm(int opcode_index, struct inst_operand* operand, struct modrm* _modrm, struct imm *imm){
    switch (operand->type){
        case INST_OPERAND_TYPE_REG:
            _modrm->reg = registers_table[operand->value].reg;        
            break;
        case INST_OPERAND_TYPE_IMM:
            
            imm->imm = operand->value;
            imm->needs_imm = true;
            imm->size = operand->size;

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

static inline bool add_rm_2_modrm(int opcode_index, struct modrm * _modrm, struct inst_operand* operand, struct imm *imm){
    switch (operand->type){
        case INST_OPERAND_TYPE_SREG:
            return false;
            break;
        case INST_OPERAND_TYPE_IMM:

            imm->imm = operand->value;
            imm->needs_imm = true;
            imm->size = operand->size;
            _modrm->mod = 0b11;
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


    struct imm imm = {0};

    bool already_done_66_prefix = false;

	int opcode_index = find_opcode(inst_);

    if (opcode_index == -1){
        printf("Failed to find correct opcode for instruction\n");
        return;  
    }
    opcode = opcode_table[opcode_index].opcode;


    for (int i = 0; i < inst_->operands.size(); i++){
        if (!already_done_66_prefix && opcode_table[opcode_index].operands[i].needs_66_prefix){
            add_byte(0x66);
            already_done_66_prefix = true;
        }

        if (opcode_table[opcode_index].operands[i].use_literal_value);
        else if(inst_->operands[i]->type == INST_OPERAND_TYPE_SCALE){

            if (inst_->operands[i]->sib_info.base->type == INST_OPERAND_TYPE_REG){
                needs_sib = true;

                set_rm_in_modrm(&modrm_,0b100);

                if (registers_table[(int)inst_->operands[i]->sib_info.base->reg].reg == 0b101){
                    imm.imm = 0x0;
                    imm.size = 8;
                    imm.needs_imm = true;
                    set_mod_in_modrm(&modrm_, 0b01);
                }
                else{
                    set_mod_in_modrm(&modrm_, 0b00);
                }

                //printf("%d: reg: %d\n", i, (int)inst_->operands[i].value);
                inst_->operands[i]->sib_info.sib_byte.base = registers_table[(int)inst_->operands[i]->sib_info.base->value].reg; 

                sib_byte = *(unsigned char*)&inst_->operands[i]->sib_info.sib_byte;
                
                modrm_index++;
                skip_rm = true;
            }
            else if(inst_->operands[i]->sib_info.base->type == INST_OPERAND_TYPE_IMM){
                needs_sib = true;
                

                set_rm_in_modrm(&modrm_,0b100);

                inst_->operands[i]->sib_info.sib_byte.base = 0b101;

                switch (inst_->operands[i]->sib_info.base->size){
                    case 32:{
                        imm.imm = inst_->operands[i]->sib_info.base->value;
                        imm.size = 32;
                        imm.needs_imm = true;
                        set_mod_in_modrm(&modrm_, 0b00);
                        break;
                    }

                    case 8:{
                        imm.imm = inst_->operands[i]->sib_info.base->value;
                        imm.size = 8;
                        imm.needs_imm = true;
                        set_mod_in_modrm(&modrm_, 0b01);
                        break;
                    }

                    default:
                        printf("Incorrect size for displacement\n");
                        return;
                }
                

                sib_byte = *(unsigned char*)&inst_->operands[i]->sib_info.sib_byte;
                modrm_index++;
                skip_rm = true;
            }

        }
        else{
            if (opcode_table[opcode_index].which_does_rm_field_point_to == 0){
                if (modrm_index == 0) {
                    if (skip_rm){
                        if (add_rm_2_modrm(opcode_index, &modrm_, inst_->operands[i], &imm))
                            modrm_index++;
                    }
                }
                else if (modrm_index == 1){
                    add_reg_2_modrm(opcode_index, inst_->operands[i], &modrm_, &imm);
                    modrm_index++;
                }   
            }
            else{

                if (modrm_index == 1){
                    if (skip_rm){
                        if (add_rm_2_modrm(opcode_index, &modrm_, inst_->operands[i], &imm))
                            modrm_index++;
                    }
                }
                else if (modrm_index == 0){
                    add_reg_2_modrm(opcode_index, inst_->operands[i], &modrm_, &imm);
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

    if (imm.needs_imm){
        add_imm(imm.imm, imm.size, ENDIANESS__BIG_ENDIAN__);
    }
}

void x86_32_Encoder::gen_elf32(std::string name){

    Elf32_Sym *csym;
    Elf32 * elf = new Elf32();
    std::fstream tfile("temp.out", std::ios::in | std::ios::binary);
    if (!tfile.is_open()) return;
    std::vector<char> instructions(std::istreambuf_iterator<char>{tfile}, std::istreambuf_iterator<char>{});
    struct Elf32_section * shstrtab_section;
    struct Elf32_section * text_section;
    struct Elf32_section * strtab_section;
    struct Elf32_section * symtab_section;
    struct Elf32_section * data_section;
    struct Elf32_section * rel_text_section;
    SymTab32 * symbol_table = new SymTab32();
    StrTab32 * strtab = new StrTab32();
    StrTab32 * shstrtab = new StrTab32();
    RelTab32 * rel_tab = new RelTab32();

    elf->new_section(); // NULL
    text_section = elf->new_section(); // .text
    shstrtab_section = elf->new_section(); // .shstrtab
    symtab_section = elf->new_section(); // .symtab
    strtab_section = elf->new_section(); // .strtab
    data_section = elf->new_section(); // .data
    rel_text_section = elf->new_section(); // .rel.text

    elf->eheader->e_shstrndx = shstrtab_section->index;
// .shstrtab
// ===============================================
    shstrtab->new_string(".shstrtab");
    shstrtab->new_string(".text");
    shstrtab->new_string(".strtab");
    shstrtab->new_string(".symtab");
    shstrtab->new_string(".data");
    shstrtab->new_string(".rel.text");
    
// ===============================================
// .text
    text_section->data = (void*)instructions.data();
    text_section->data_sz = instructions.size();
    text_section->section->sh_name = shstrtab->get_string(".text");
    text_section->section->sh_type = SHT_PROGBITS;
    text_section->section->sh_flags = SHF_ALLOC | SHF_EXECINSTR;
    text_section->section->sh_addralign = 4;



    int size_of__data_data = 0;
    int _data_data_index = 0;

    for ( Data* data_ : data){
        size_of__data_data += data_->size;
    }

    unsigned char * _data_data = (unsigned char*)malloc(size_of__data_data);

    for (Data* data_ : data){
        for (int y = 0; y < data_->size; y++){
            _data_data[_data_data_index] = data_->data[y];
            _data_data_index++;
        }
    }

    data_section->data = (void*)_data_data;
    data_section->data_sz = size_of__data_data;
    data_section->section->sh_name = shstrtab->get_string(".data");
    data_section->section->sh_type = SHT_PROGBITS;
    data_section->section->sh_flags = SHF_ALLOC | SHF_WRITE;
    data_section->section->sh_addralign = 4;

// .strtab
    strtab->new_string("temp.nash");

    
// .symtab

    bool set_symtab_loc_idx = false;
    int symtab_idx = 0;

    symtab_section->section->sh_name = shstrtab->get_string(".symtab");
    symtab_section->section->sh_link = strtab_section->index;

    symbol_table->new_symbol(0, 0, SHN_UNDEF);
    symtab_idx++;

    symbol_table->new_symbol(strtab->get_string("temp.nash"), ELF32_ST_INFO(STB_LOCAL, STT_FILE), SHN_ABS);
    symtab_idx++;
    
    symbol_table->new_symbol(0, ELF32_ST_INFO(STB_LOCAL, STT_SECTION), text_section->index);
    symtab_idx++;

    auto label_iter = labels.begin();
    while (label_iter != labels.end()) {
    
        strtab->new_string(label_iter->first); // add the label name to strtab

        if (label_iter->second->visibility == local_label){
            if (label_iter->second->_section == section::_text){
                csym = symbol_table->new_symbol(strtab->get_string(label_iter->first), ELF32_ST_INFO(STB_LOCAL, STT_NOTYPE), text_section->index);
                csym->st_value = label_iter->second->offset;
            }
            else if(label_iter->second->_section == section::_data){
                csym = symbol_table->new_symbol(strtab->get_string(label_iter->first), ELF32_ST_INFO(STB_LOCAL, STT_NOTYPE), data_section->index);
                csym->st_value = label_iter->second->offset;
            }
        }
        else{
            if (label_iter->second->_section == section::_text){
                csym = symbol_table->new_symbol(strtab->get_string(label_iter->first), ELF32_ST_INFO(STB_GLOBAL, STT_NOTYPE), text_section->index);
                csym->st_value = label_iter->second->offset;
            }
            else if(label_iter->second->_section == section::_data){
                csym = symbol_table->new_symbol(strtab->get_string(label_iter->first), ELF32_ST_INFO(STB_GLOBAL, STT_NOTYPE), data_section->index);
                csym->st_value = label_iter->second->offset;
            }
        }

        if (label_iter->second->visibility != local_label){
            symtab_section->section->sh_info =  ELF32_ST_INFO(STB_LOCAL,symtab_idx);
            set_symtab_loc_idx = true;
        }

        symtab_idx++;
        label_iter++;
    }
    if (!set_symtab_loc_idx){
        symtab_section->section->sh_info =  ELF32_ST_INFO(STB_LOCAL,symtab_idx);
    }


    shstrtab->add_strtab(shstrtab_section);
    shstrtab_section->section->sh_name = shstrtab->get_string(".shstrtab");


    strtab->add_strtab(strtab_section);
    strtab_section->section->sh_name = shstrtab->get_string(".strtab");


    symbol_table->add_symtab(symtab_section);


    //rel_tab->new_relocation(1, ELF32_R_INFO(4, R_386_32));

    rel_tab->add_reltab(rel_text_section);

    rel_text_section->section->sh_name = shstrtab->get_string(".rel.text");
    rel_text_section->section->sh_link = symtab_section->index;
    rel_text_section->section->sh_info = text_section->index;


    elf->write(name);

    elf->done();

    delete elf;
    delete symbol_table;
    delete shstrtab;
    delete strtab;
    free(_data_data);

}



void x86_32_Encoder::gen_bin(std::string name){
    if (_format == format::elf32){
        gen_elf32(name);
    }
    else{
        std::cout << "x86_32 encoder does not support that format\n";
        return;
    }
}
