
#ifndef __C_LIB_H_
#define __C_LIB_H_
#include "stdio.h"
#define LENGTH(x)  (sizeof(x) / sizeof((x)[0]))
#define println(format, ...) printf(format "\n", __VA_ARGS__)

#include "./memory.h"

// char* to_base_n(int x, unsigned int base){
//     char* result;
//     int remainder, quotient, acc = x;
    
//     while (acc > base)
//     {
//         quotient = acc / base;
//         remainder = acc - ( quotient * base );
//         sprintf(result, "%s%d", result, remainder);
//         acc = quotient;
//     }
//     return result;     
// }

#endif
