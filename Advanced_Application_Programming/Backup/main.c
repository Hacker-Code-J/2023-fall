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
* Last Modified: 2023-10-04
*
* Note: This library aims to provide a robust and efficient solution for
*       performing arithmetic on large integers beyond the limitations of
*       standard data types.
**********************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<memory.h>
#include<errno.h>

#include "pubao_setup.h"

int main() {
    WORD k;
    printf("W = 2^%lu\n",8*sizeof(k));
    
    clock_t start, end;
    /*Test
    BINT* x = NULL;
    BINT* y = NULL;
    BINT* z = NULL;

    init_bint(&x, 2);
    x->val[0] = 0x87654321;
    x->val[1] = 0x9;

    init_bint(&y, 2);
    y->val[0] = 0x98765432;
    y->val[1] = 0xfedcba;

    custom_printHex_xy(x,y,2);
    
    z = add_xy(x,y);

    printf("\n\nResult:\n\n");
    custom_printHex_xyz(x,y,z,2);

    delete_bint(&x);
    delete_bint(&y);
    delete_bint(&z);
    */


    BINT* a = NULL;
    BINT* b = NULL;
    BINT* c = NULL;
    int n, m, max;
    for(int i=0; i<3; i++) {
        n = rand() % 0x3;
        m = rand() % 0x3;
        max = (n>m)? n:m;

        start = clock();
        printf("\n/****************************\n[Test %d]\n****************************/\n", i+1);
        rand_bint(&a, NON_NEGATIVE, n);
        rand_bint(&b, NON_NEGATIVE, m);

        custom_printHex_xy(a,b,max);

        c = add_xy(a,b);

        printf("\nResult:\n\n");
        
        custom_printHex_xyz(a,b,c,max);
        
        delete_bint(&a);
        delete_bint(&b);
        delete_bint(&c);

        end = clock();

        double time_taken = ((double) end - start) / CLOCKS_PER_SEC;
        printf("\nTime: %f.\n", time_taken);
    }
    
    return 0;
}
