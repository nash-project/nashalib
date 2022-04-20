#include <nashalib/assembler.hpp>
#include <stdio.h>
#include <cstdarg>
#include <iostream>


namespace nashalib{
	Assembler::Assembler(architecture arch, int bsz, format f){

		ofile = fopen("temp.out", "wb");

		if (arch == architecture::x86 && bsz == 32){
			encoder = new x86_32_Encoder(ofile, f);
		}
	}
	void Assembler::encode(struct inst* instruction){
		encoder->encode(instruction);
	}
	struct inst * Assembler::mInstruction(mnemonic mnemonic_, operand_list& operands){

		struct inst * instruction = (struct inst*)calloc(1, sizeof(struct inst));

		instruction->mnemonic = mnemonic_;

		for (auto operand: operands){
			new_operand(instruction, operand);
		
		}
		//instructions.push_back(instruction);
		return instruction;
	}
	void Assembler::freeInstruction(struct inst* instruction){
		if (instruction == NULL){
			return;
		}
		free_instruction(instruction);
	}

	int Assembler::label_as_relative(std::string label){
		return (encoder->_get_cpos() - encoder->_get_label(label));
	}
	int Assembler::get_label(std::string label){
		return encoder->_get_label(label);
	}

	void Assembler::add_label(std::string label, int vis){
		encoder->_add_label(label, vis, section::_text);
	}

	void Assembler::write(std::string name){
		encoder->_resolve_labels();
		fclose(ofile);
		encoder->gen_bin(name);
		
	}
	void Assembler::new_data(Data* data){
		encoder->_add_label(data->label, data->vis, section::_data);
		encoder->_add_data(data);
	}
	Label * Assembler::get_label_obj(std::string label){
		return encoder->_get_label_obj(label);
	}
};