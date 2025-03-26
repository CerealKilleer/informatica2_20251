#include <iostream>
#include <lib_int_to_bin.hpp>

bool int_to_bin(u_int8_t num, u_int8_t *binary)
{
    int8_t bits = BITS_ON_BYTES - 1;
    for (; bits>=0; bits--) {
        *(binary + bits) = num % 2;
        num = num / 2;
    }
    return true;
}

u_int8_t bin_to_int(u_int8_t *binary)
{
    u_int8_t num = 0;
    for (u_int8_t i=0; i < BITS_ON_BYTES; i++) {
        num = 2*num + binary[i];
    }
    return num;
}