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
* Last Modified: 2023-09-21
*
* Note: This library aims to provide a robust and efficient solution for
*       performing arithmetic on large integers beyond the limitations of
*       standard data types.
**********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "PUBAO.h"


int main() {
    BIGINT *b;
    create_BIGINT(&b, 4);
    
    b->sign = 1;
    b->a[0] = 16;
    b->a[1] = 0x9abcdef0;
    b->a[2] = 0x00000001;
    b->a[3] = 0xffffffff;

    show_hex_BIGINT(b);
    show_bin_BIGINT(b);

    delete_BIGINT(&b);
    
    return OK;
}

void delete_BIGINT(BIGINT** bigint) {
    if (*bigint == NULL)
        return;

    free((*bigint)->a);
    free(*bigint);
    *bigint = NULL;
}

void create_BIGINT(BIGINT** bigint, int wordlen) {
    *bigint = (BIGINT*)malloc(sizeof(BIGINT));
    if(*bigint == NULL)
        exit(Err_Overflow);
    
    (*bigint)->wordlen = wordlen;
    (*bigint)->a = (u32*)malloc(wordlen * sizeof(u32));
    if ((*bigint)->a == NULL)
        exit(Err_Overflow);
}

void show_hex_BIGINT(BIGINT* bigint) {
    printf("Hex: ");
    for (int i = 0; i < bigint->wordlen; i++) {
        printf("%08x ", bigint->a[i]);
    }
    printf("\n");
}
void show_bin_BIGINT(BIGINT* bigint) {
    printf("Bin: ");
    int size = sizeof(u32)*8;
    for (int i = 0; i < bigint->wordlen; i++) {
        for (int j = size-1; j >= 0; j--) {
            printf("%d", (bigint->a[i] >> j) & 1);
        }
        printf(" ");
    }
    printf("\n");
}
