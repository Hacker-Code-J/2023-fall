#ifndef _PUBAO_OPR_H
#define _PUBAO_OPR_H

/*Addition and Subtraction */
void add_xyk(WORD x, WORD y, WORD k, WORD* res, WORD* carry);
void add_xyz(BINT* X, BINT* Y, BINT* Z);
void ADD_xyz(BINT* X, BINT* Y, BINT* Z);

void sub_xby(WORD x, WORD b, WORD y, WORD* res, WORD* borrow); 
void sub_xyz(BINT* X, BINT* Y, BINT* Z);
void SUB_xyz(BINT* X, BINT* Y, BINT* Z);

#endif