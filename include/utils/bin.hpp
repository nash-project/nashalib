#pragma once

extern "C" void binary(unsigned char n);

extern "C" unsigned char cat_binary(unsigned char original, unsigned char more, int more_amount, int start_pos);

inline static unsigned char set_bit(unsigned char byte, int n){
    return ((1 << n ) | byte);
}