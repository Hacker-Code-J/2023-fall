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

#include <stdio.h>
#include <stdlib.h>
#include "PUBAO.h"

BIGINT* create_bigint(int sign, int wordlen) {
    BIGINT* bigint = (BIGINT*)malloc(sizeof(BIGINT));
    if (!bigint) {
        perror("Memory allocation failed");
        exit(EXIT_FAILURE);
    }
    
    bigint->sign = sign;
    bigint->wordlen = wordlen;
    bigint->val = (u32*)malloc(wordlen * sizeof(u32));
    if (!bigint->val) {
        perror("Memory allocation failed");
        free(bigint);
        exit(EXIT_FAILURE);
    }
    
    // Initialize bigint->val to zero or your desired initial value
    
    return bigint;
}

void destroy_bigint(BIGINT* bigint) {
    if (bigint) {
        free(bigint->val);
        free(bigint);
    }
}

BIGINT* add_bigint(const BIGINT* a, const BIGINT* b, BIGINT* result) {
    int carry = 0;
    int max_wordlen = (a->wordlen > b->wordlen) ? a->wordlen : b->wordlen;
    
    if (result == NULL) {
        result = create_bigint(a->sign, max_wordlen + 1);
    }
    
    for (int i = 0; i < max_wordlen; i++) {
        u32 sum = carry;
        if (i < a->wordlen) {
            sum += a->val[i];
        }
        if (i < b->wordlen) {
            sum += b->val[i];
        }
        
        result->val[i] = sum & 0xFFFFFFFF;
        carry = sum >> 32;
    }
    
    result->val[max_wordlen] = carry;
    
    return result;
}

char* bigint_to_string(const BIGINT* bigint) {
    if (bigint == NULL) {
        return NULL;
    }
    
    int num_digits = bigint->wordlen * 8; // Assuming 32-bit u32 elements
    char* result = (char*)malloc(num_digits + 2); // +2 for sign and null terminator
    
    if (!result) {
        perror("Memory allocation failed");
        exit(EXIT_FAILURE);
    }
    
    int offset = 0;
    
    if (bigint->sign == -1) {
        result[offset++] = '-';
    }
    
    int word_index = bigint->wordlen - 1;
    
    // Skip leading zeros
    while (word_index >= 0 && bigint->val[word_index] == 0) {
        word_index--;
    }
    
    if (word_index < 0) {
        // The entire number is zero
        result[offset++] = '0';
    } else {
        // Convert each word to a string and append to result
        while (word_index >= 0) {
            u32 word = bigint->val[word_index];
            for (int i = 0; i < 8; i++) {
                result[offset++] = '0' + (word % 10);
                word /= 10;
            }
            word_index--;
        }
    }
    
    result[offset] = '\0'; // Null-terminate the string
    return result;
}


int main() {
    BIGINT* operand1 = create_bigint(1, 2); // Positive, wordlen = 3
    operand1->val[0] = 0xaabbccdd;
    operand1->val[1] = 0x33334444;

    BIGINT* operand2 = create_bigint(1, 3); // Negative, wordlen = 2
    operand2->val[0] = 0x99aabbcc;
    operand2->val[1] = 0x55667788;
    operand2->val[2] = 0x11223344;

    BIGINT* result = NULL;
    result = add_bigint(operand1, operand2, result);

    printHex(operand1);
    printHex(operand2);
    printHex(result);
    // Print the result
    //printf("Result: %s\n", bigint_to_string(result));

    // Clean up memory
    destroy_bigint(operand1);
    destroy_bigint(operand2);
    destroy_bigint(result);

    return OK;
}

/*
void delete_BIGINT(BIGINT** bigint) {
    if (*bigint == NULL)
        return;

    free((*bigint)->val);
    free(*bigint);
    *bigint = NULL;
}

void create_BIGINT(BIGINT** bigint, int wordlen) {
    *bigint = (BIGINT*)malloc(sizeof(BIGINT));
    if(*bigint == NULL)
        exit(Err_Overflow);
    
    (*bigint)->wordlen = wordlen;
    (*bigint)->val = (u32*)malloc(wordlen * sizeof(u32));
    if ((*bigint)->val == NULL)
        exit(Err_Overflow);
}
*/

void printHex(BIGINT* bigint) {
    printf("Hex: ");
    for (int i = bigint->wordlen - 1; i >= 0; i--) {
        printf("%08x ", bigint->val[i]);
    }
    printf("\n");
}

void printBin(BIGINT* bigint) {
    printf("Bin: ");
    for (int i = bigint->wordlen - 1; i >= 0; i--) {
        for (int j = 31; j >= 0; j--) {
            printf("%d", (bigint->val[i] >> j) & 1);
        }
        printf(" ");
    }
    printf("\n");
}

int Compare_ABS (BIGINT* x, BIGINT* y)//A>B =1 ,A=B =0 , A<B -1
{
    int n = x->wordlen; 
    int m = y->wordlen;
    if (n>m)
    {
        return 1;
    } 
    if (n<m)
    {
        return -1;
    }
    for (int i = n-1;i>=0;i--)
    {
        if ((x->val)[i] > (y->val)[i])
        {
            return 1;
        }
        else if ((x->val)[i] < (y->val)[i])
        {
           return -1;
        }
        
    }
    return 0;
}

int bi_Compare(BIGINT* x , BIGINT* y)//A>B =1 ,A=B =0 , A<B -1
{
    if ((x->sign = 0) && (y->sign =-1))
    {
        return 1;
    }

    if ((x->sign = -1) && (y->sign =0))
    {
        return -1;
    }

    int ret = Compare_ABS(x,y);
    if (x->sign = 0)
    {
        return ret;
    }
    else
    {
        return (ret * -1);
    }
}
