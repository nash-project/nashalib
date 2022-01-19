#include <utils/bin.hpp>
#include <stdio.h>

extern "C" void binary(unsigned char n) {
    unsigned char i;
    
    printf("0b");
    for (i = 1 << 7; i > 0; i >>= 1)
        printf("%u", !!(n & i));
}


extern "C" unsigned char cat_binary(unsigned char original, unsigned char more, int more_amount, int start_pos){
    int n =  (8 - more_amount) - (start_pos); // 8 is the size of a unsigned char;
    return (more << n) ^ original;
}