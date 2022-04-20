#pragma once
namespace nashalib{

/**
 * all supported mnemonics
 * 
 */
enum class mnemonic {
    ADD = 0,
    MOV,
    PUSH,
    POP,
    RETN,
    CALL,
    INT,
};

}