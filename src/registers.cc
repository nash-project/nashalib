#include <registers.hpp>


/**
 * all registers supported by x86 32 bit assembly
 * 
 */
struct register_info registers_table[] = {

    // 8 bit registers
    { 0x00, 8, false},
    { 0x01, 8, false},
    { 0x02, 8, false},
    { 0x03, 8, false},
    { 0x04, 8, false},
    { 0x05, 8, false},
    { 0x06, 8, false},
    { 0x07, 8, false},

    // 16 bit registers
    { 0x00, 16, false},
    { 0x01, 16, false},
    { 0x02, 16, false},
    { 0x03, 16, false},
    { 0x04, 16, false},
    { 0x05, 16, false},
    { 0x06, 16, false},
    { 0x07, 16, false},

    //32 bit registers
    { 0x00, 32, false},
    { 0x01, 32, false},
    { 0x02, 32, false},
    { 0x03, 32, false},
    { 0x04, 32, false},
    { 0x05, 32, false},
    { 0x06, 32, false},
    { 0x07, 32, false},

    //64 bit registers
    { 0x00, 64, false},
    { 0x01, 64, false},
    { 0x02, 64, false},
    { 0x03, 64, false},
    { 0x04, 64, false},
    { 0x05, 64, false},
    { 0x06, 64, false},
    { 0x07, 64, false},


    // segment registers
    { 0x00, 16, true},
    { 0x01, 16, true},
    { 0x02, 16, true},
    { 0x03, 16, true},
    { 0x04, 16, true},
    { 0x05, 16, true},
    { 0x06, 16, true},
    { 0x07, 16, true},
};
