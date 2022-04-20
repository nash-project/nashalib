#pragma once
#include <nashalib/instruction.hpp>
#include <nashalib/registers.hpp>
#include <stdio.h>
#include <nashalib/bencoder.hpp>
#include <nashalib/settings.hpp>

namespace nashalib{

class x86_32_Encoder : public BEncoder {
public:
   x86_32_Encoder(FILE* file, format __format) : BEncoder(file, __format) {};
   void encode(struct inst*);
   void gen_bin(std::string);
private:
   void gen_elf32(std::string);
};


}