#include<stdio.h>
#include<stdlib.h>

#include "pubao_setup.h"
#include "pubao_opr.h"

/*Addition and Subtraction */
void add_xyk(WORD x, WORD y, WORD k, WORD* res, WORD* carry) {
    /****************
    *carry = 0;
    *res = x+y;
    if(*res < x)
        *carry = 1;

    *res = *res + k;
    if(*res < k)
        *carry += 1;
    ****************/

    //Optimize
    *res = x + y;
    *carry = (*res < x);
    *res += k;
    *carry += (*res < (x+y));

    printf("%08x + %08x + %d = %08x * W + %08x\n", x, y, k, *carry, *res);
}

void add_xyz(BINT* X, BINT* Y, BINT* Z) {
    int n = X->wordlen;
    int m = Y->wordlen;

    WORD k = 0;
    WORD res, carry;

    // Loop until the shorter of the two numbers ends
    int i;
    for (i=0; i<m; i++) {
        add_xyk(X->val[i], Y->val[i], k, &res, &carry);
        Z->val[i] = res;
        k = carry;
    }
    // Continue adding any remaining X values with the carry, since Y is shorter
    for (; i<n; i++) {
        add_xyk(X->val[i], 0, k, &res, &carry); // just adding X values since Y is shorter
        Z->val[i] = res;
        k = carry;
    }

    if(k) Z->val[n] = k;

    // Set the sign and word length of Z
    Z->wordlen = (k == 0) ? n : n+1;

    refine_BINT(Z);
    //return Z;
}

void ADD_xyz(BINT* X, BINT* Y, BINT* Z) {
    ///*
    if(X->sign==NON_NEGATIVE && Y->sign==NEGATIVE) {
        SUB_xyz(X,Y,Z);
    } else if(X->sign==NEGATIVE && Y->sign == NON_NEGATIVE) {
        SUB_xyz(Y,X,Z);
    } else if(X->wordlen >= Y->wordlen) {
        add_xyz(X,Y,Z);
    } else {
        add_xyz(Y,X,Z);
    }
    //*/

    //Optimize
    /*
    if (X->sign == Y->sign) {
        // Both numbers have the same sign, proceed with normal addition.
        // Choose the larger number as the first operand to simplify the addition operation.
        if (X->wordlen >= Y->wordlen)
            add_xyz(X, Y, Z);
        else
            add_xyz(Y, X, Z);
    } else {
        // Numbers have different signs, proceed with subtraction.
        if (X->sign == NON_NEGATIVE)
            SUB_xyz(X, Y, Z);
        else
            SUB_xyz(Y, X, Z);
    }
    */
}

void sub_xby(WORD x, WORD b, WORD y, WORD* res, WORD* borrow) {
	if(y>x) {
        int tmp; tmp=x; x=y; y=tmp;
    }
    /****************
    *brrow = 0;
    *res = x-borrow;
    if(x < b)
        *borrow = 1;
    if(*res < y)
        *borrow += 1;
    *res = *res - y;
    ****************/
    //Optimize
    *res = x-b;
    *borrow = (x < b);
    *borrow += (*res < y);
    *res -= y;
    printf("%08x - %d - %08x = -%08x * W + %08x\n", x, b, y, *borrow, *res);
}

void sub_xyz(BINT* X, BINT* Y, BINT* Z) {//X>=Y>0
    int n = X->wordlen;
    int m = Y->wordlen;

    WORD* tmp;
    tmp = (WORD*)realloc(Y->val,n*sizeof(WORD));
    Y->val = tmp;

    for(int i=m; i<n; i++)
        Y->val[i] = 0;

    WORD b = 0;
    WORD res, borrow;

    //
    for(int i=0; i<n; i++) {
        sub_xby(X->val[i], b, Y->val[i], &res, &borrow);
        Z->val[i] = res;
    }
    
    refine_BINT(Z);
}

void SUB_xyz(BINT* X, BINT* Y, BINT* Z) {
    ///*
    if(X->sign==NON_NEGATIVE && Y->sign==NON_NEGATIVE) {
        if(compare_xy(X,Y)==1 || compare_xy(X,Y)==0) {
            sub_xyz(X,Y,Z);
        } else if(compare_xy(X,Y)==-1) {
            Z->sign = NEGATIVE;
            sub_xyz(Y,X,Z);
        }
    } else if(X->sign==NEGATIVE && X->sign==NEGATIVE) {
        if(compare_xy(X,Y)==1 || compare_xy(X,Y)==0) {
            sub_xyz(Y,X,Z);
        } else if(compare_xy(X,Y)==-1) {
            Z->sign = NEGATIVE;
            sub_xyz(X,Y,Z);
        }
    } else if(X->sign==NON_NEGATIVE && Y->sign==NEGATIVE) {
        ADD_xyz(X,Y,Z);
    } else {
        Z->sign = NEGATIVE;
        ADD_xyz(Y,X,Z);
    }
    //*/

    //Optimize
    /*
    int cmp_result = compare_xy(X, Y);

    if (X->sign == NON_NEGATIVE && Y->sign == NON_NEGATIVE) {
        if (cmp_result >= 0) {
            sub_xyz(X, Y, Z);
        } else {
            Z->sign = NEGATIVE;
            sub_xyz(Y, X, Z);
        }
    } else if (X->sign == NEGATIVE && Y->sign == NEGATIVE) {
        if (cmp_result <= 0) {
            Z->sign = NEGATIVE;
            sub_xyz(X, Y, Z);
        } else {
            sub_xyz(Y, X, Z);
        }
    } else if (X->sign == NON_NEGATIVE) {
        ADD_xyz(X, Y, Z);
    } else {
        Z->sign = NEGATIVE;
        ADD_xyz(X, Y, Z);
    }
    */
}