#pragma once
#include <instruction.hpp>
#include <registers.hpp>
#include <stdio.h>
#include <bencoder.hpp>
#include <settings.hpp>

class x86_32_Encoder : public BEncoder {
public:
   x86_32_Encoder(FILE* file, format __format) : BEncoder(file, __format) {};
   void encode(struct inst*);
   void gen_bin(std::string);
private:
   void gen_elf32(std::string);
};
