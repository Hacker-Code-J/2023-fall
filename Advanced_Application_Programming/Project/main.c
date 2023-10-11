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
    //BINT* a2 = NULL;
    //BINT* b2 = NULL;
    //BINT* c2 = NULL;
    int n, m, max;
    int a_sgn, b_sgn;
    for(int i=0; i<3; i++) {
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
        init_bint(&c, max);
        //init_bint(&c2, max);

        custom_printHex_xy(a,b,max);

        add_xyz(a,b,c);

        printf("\nResult:\n\n");
        
        custom_printHex(a,b,c,1);

        //Addition
        /*
        printf("\nCheck[ADD]:\n\n");
        
        assgin_x2y(c, &a2);
        assgin_x2y(b, &b2);

        custom_printHex_xy(a2,b2,max);

        ADD_xyz(a2,b2,c2);

        custom_printHex(a2,b2,c2,1);   
        */

        delete_bint(&a);
        delete_bint(&b);
        delete_bint(&c);
        /*
        delete_bint(&a2);
        delete_bint(&b2);
        delete_bint(&c2);
        */
        end = clock();

        double time_taken = ((double) end - start) / CLOCKS_PER_SEC;
        printf("\nTime: %f.\n", time_taken);
    }
    //*/
    
    return 0;
}
