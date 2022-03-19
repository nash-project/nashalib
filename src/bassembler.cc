#include <bencoder.hpp>
#include <stdio.h>


void BEncoder::add_byte(unsigned char byte){
	fwrite(&byte, sizeof(unsigned char), 1, ofile);
    cpos++;
    //printf("%02x",byte);
}

void BEncoder::add_int(int number, int endianess){
    (void)endianess;
	fwrite(&number, sizeof(int), 1, ofile);
    cpos += 4;
    //printf("%08x", cnumber);
}

void BEncoder::add_short(int number, int endianess){
    (void)endianess;
	fwrite(&number, sizeof(short), 1, ofile);
    cpos += 2;
    //printf("[%04x]", cnumber);
}

void BEncoder::add_imm(int value, int size, int endianess){
    (void)endianess;

    switch (size){
        case 32:
            add_int(value, endianess);
            break;
        case 16:
            add_short(value, endianess);
            break;
        case 8:
            add_byte(value);
            break;
    }
}

void BEncoder::add_label(std::string label){
    labels.insert({label, cpos});
}

int BEncoder::get_label(std::string label){
    return labels[label];
}

int BEncoder::get_cpos(){
    return cpos;
}