/**********************************************************************
* Project Name: PUBAO (P.A.N.D.A.'s Unbounded Big Arithmetic Operations)
* Team Name: P.A.N.D.A. (Programmers Aspiring to Navigate DIgital Arithmetic)
* Sub-Meaning: Precision Arithmetic and Number Development Associates.
* 
* File Description: This file contains the definitions and implementations
*                   for large integer arithmetic.
* 
* Author(s): Ji Yong-Hyeon, Kim Ye-chan, Moon Ye-chan, Yoo Geun-oh
* Date Created: 2023-09-21
* Last Modified: 2023-09-30
*
* Note: This library aims to provide a robust and efficient solution for
*       performing arithmetic on large integers beyond the limitations of
*       standard data types.
**********************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<memory.h>
#include<errno.h>

#include "pubao_setup.h"

int main() {
    WORD k;
    printf("Word: 2^%lu\n\n",8*sizeof(k));
    
    u64 f = 0x99aabbcc;
    u64 g = 0xaabbccdd;
    printf("%16lx", f+g);

    printf("\n *************[xyz]*************\n\n");
    
    BINT* x = NULL;
    BINT* y = NULL;
    BINT* z = NULL;

    init_bint(&x, 3);
    x->val[0] = 0x99aabbcc;
    x->val[1] = 0x55667788;
    x->val[2] = 0x11223344;
    printHex(x);

    init_bint(&y, 2);
    y->val[0] = 0xaabbccdd;
    y->val[1] = 0x33334444; 
    printHex(y);
    
    z = add_xy(x,y);

    printf("\n\nResult:\n\n");
    printHex(x);
    printHex(y);
    printHex(z);

    delete_bint(&x);
    delete_bint(&y);
    delete_bint(&z);

    printf("\n *************[abc]*************\n\n");
    
    BINT* a = NULL;
    BINT* b = NULL;
    BINT* c = NULL;

    init_bint(&a, 2);
    a->val[0] = 0x5e6f789a;
    a->val[1] = 0x1a2b3c4d;
    printHex(a);

    init_bint(&b, 2);
    b->val[0] = 0x76543210; 
    b->val[1] = 0xfedcba98; 
    printHex(b);
    
    c = add_xy(a,b);

    printf("\n\nResult:\n\n");
    printHex(a);
    printHex(b);
    printHex(c);

    delete_bint(&a);
    delete_bint(&b);
    delete_bint(&c);
    
    return 0;
}
