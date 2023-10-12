#ifndef _PUBAO_OPERATION_H
#define _PUBAO_OPERATION_H

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
    printf("%08x + %08x = %08x * W + %08x\n", x, y, *carry, *res);
}
void add_xyk2(WORD x, WORD y, WORD k, WORD* res, WORD* carry) {
    u64 sum = (u64) x + y + k;  // casting to prevent overflow
    *res = (WORD) (sum & MASK); // assuming 32-bit words, adjust mask as needed
    *carry = (WORD) (sum >> 32);
    printf("%08x + %08x = %08x * W + %08x\n", x, y, *carry, *res);
}

BINT* add_xy(BINT* X, BINT* Y) {
    int n = X->wordlen;
    int m = Y->wordlen;

    BINT* Z = NULL;
    init_bint(&Z, n+1);

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

    Z->val[n] = k;

    // Set the sign and word length of Z
    Z->sign = X->sign; // assuming the same sign for X and Y
    Z->wordlen = (k == 0) ? n : n+1;

    return Z;
}

#endif
