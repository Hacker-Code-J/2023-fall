#ifndef _PUBAO_OPR_H
#define _PUBAO_OPR_H
// Function prototypes for BINT arithmetic operations.

/************************************
* W := 2^{sizeof(WORD)*8}
* x + y + k = carry * W + res
************************************/
void add_xyk(WORD x, WORD y, WORD k, WORD* res, WORD* carry);

// Z = X + Y with wordlen(X) >= wordlen(Y)
void add_xyz(BINT* X, BINT* Y, BINT* Z);


// Integrate ADD
void ADD_xyz(BINT* X, BINT* Y, BINT* Z);

/************************************ 
* W := 2^{sizeof(WORD)*8}
* x - b - y = - brrow * W + res
************************************/
void sub_xby(WORD x, WORD b, WORD y, WORD* res, WORD* borrow); 

// Z = X - Y with X >= Y >= 0.
void sub_xyz(BINT* X, BINT* Y, BINT* Z);

// Integrate SUB
void SUB_xyz(BINT* X, BINT* Y, BINT* Z);

//Author: Moon Ye-chan
void mult_xyc(WORD x, WORD y , WORD* C);

#endif