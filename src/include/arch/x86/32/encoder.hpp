#pragma once
#include <instruction.hpp>
#include <registers.hpp>
#include <stdio.h>
#include <bencoder.hpp>



extern "C" void encode(struct inst*);

class x86_32_Encoder : public BEncoder {
public:
   x86_32_Encoder(FILE* file) : BEncoder(file) {};
   void encode(struct inst*);

};
