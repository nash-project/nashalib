


int main(){
	assembler::Assembler *assembler = new assembler::Assembler(assembler::architecture::x86, 32); 

    struct inst * instruction = assembler->mInstruction(mnemonic::ADD, 
    	create_reg(registers::cx), 
    	create_scaled_reg(registers::ax));

    
    struct inst * instruction0 = assembler->mInstruction(mnemonic::PUSH, create_(registers::cx));


    struct inst* instruction1 = assembler->mInstruction(mnemonic::ADD, 
    	create_reg(registers::eax), create_scale_reg( create_reg(registers::ecx), registers::ebx, 2);

    // mov eax, base + (index + scale)
    // mov eax, ecx + ( ebx * 4 )

    assembler->encode(instruction0);

    assembler->encode(instruction);

    assembler->freeInstruction(instruction);

	return 0;
}