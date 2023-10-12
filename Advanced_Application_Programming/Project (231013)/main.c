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
#include "pubao_opr.h"

int main() {
    srand((unsigned int)time(NULL));

    WORD k;
    printf("Word = 2^%lu\n\n",8*sizeof(k));

    //printf("\n\n%08x\n\n", 0x12345678-0xffffffff);

    clock_t start, end;
    /*Test
    BINT* x = NULL;
    BINT* y = NULL;
    BINT* z = NULL;

    init_bint(&x, 1);
    x->val[0] = 0x00000001;

    init_bint(&y, 1);
    y->val[0] = 0xffffffff;

    custom_printHex_xy(x,y,1);
    init_bint(&z, 2);
    SUB_xyz(x,y,z);

    printf("\n\nResult:\n\n");
    custom_printHex(x,y,z,2);

    delete_bint(&x);
    delete_bint(&y);
    delete_bint(&z);
    */

    ///*
    BINT* a = NULL;
    BINT* b = NULL;
    BINT* c = NULL;

    int n = 0x00;
    int m = 0x00;
    int max;
    int a_sgn, b_sgn;
    
    //0: '+', 1: '-', 2: '*'
    int opt;

    for(int i=0; i<5; i++) {
        opt = rand() % 0x02;
        //opt = 2;
        
        a_sgn = rand() % 0x02;
        b_sgn = rand() % 0x02;
        
        n = rand() % 0x3; n++;
        m = rand() % 0x3; m++;
        max = (n>m)? n:m;

        start = clock();

        printf("\n****************************\n[Test %d]\n****************************\n", i+1);
        printf("n m: %d %d\n", n,m);
        rand_bint(&a, a_sgn, n);
        rand_bint(&b, b_sgn, m);
        //rand_bint(&a, NON_NEGATIVE, n);
        //rand_bint(&b, NON_NEGATIVE, m);
        if(opt == 2) {
            max *= 2;
            init_bint(&c, max);
        }    
        else
            init_bint(&c, max);
        
        custom_printHex_xy(a,b,max);

        if(opt == 0) {
            ADD_xyz(a,b,c);
        } else if(opt == 1) {
            SUB_xyz(a,b,c);
        } else {
            //mult_xyc(a->val,b->val,c->val);
        }

        printf("\nResult:\n\n");
        a->sign = a_sgn;
        b->sign = b_sgn;
        custom_printHex(a,b,c,opt);

        delete_bint(&a);
        delete_bint(&b);
        delete_bint(&c);

        end = clock();

        double time_taken = ((double) end - start) / CLOCKS_PER_SEC;
        printf("\nTime: %f.\n", time_taken);
    }
    //*/
    
    return 0;
}