#ifndef _PUBAO_SETUP_H
#define _PUBAO_SETUP_H

 /*1. WORD in {2^8, 2^16, 2^32, 2^64} */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef unsigned long u64;

#define NON_NEGATIVE 0
#define NEGATIVE 1
#define WORD u32
#define MASK 0xFFFFFFFF //Mask to extract lower 32 bits.

/*2. Macro*/

/*3. 16-byte BINT Structure */
/**********************************************************************
* +---------------------+
* |   BINT(128-bit)     |
* +---------------------+
* |    sign (int)       |  --> NEGATIVE or NON_NEGATIVE
* +---------------------+
* |   wordlen (int)     |  --> n-word BINT
* *+---------------------+
* |    val (WORD*)      |  --> [addr]-->+---------+---------+---+---------+
* +---------------------+               | WORD[0] | WORD[1] |...| WORD[n] |
*                                       +---------+---------+---+---------+
**********************************************************************/
typedef struct {
    int sign; // + or -
    int wordlen; // n-word BINT
    WORD* val; // address for BINT
} BINT; //16-byte, i.e., 128-bit (32+32+64)

/*4. Error*/

/*5. Basic Funtions*/
/**********************************************************************
* --------------------------
* | BINT Pointer (bint_ptr) |
* --------------------------
*       |
*       |
*       V
* ------------------------------------------------------------------
* | BINT Structure                                                 |
* ------------------------------------------------------------------
* | sign (4 bytes) | wordlen (4 bytes) | val Pointer (8 bytes)     |
* ------------------------------------------------------------------
*                                       |
*                                       |
*                                       V
* ------------------------------------------------------------------
* | WORD Array (val)                                               |  
* ------------------------------------------------------------------
* | WORD (4 bytes) | WORD (4 bytes) | WORD (...)  | ...            |
* ------------------------------------------------------------------
**********************************************************************/
BINT* init_bint(BINT** bint_ptr, int wordlen) {
    // Allocate memory for BINT structure
    *bint_ptr = (BINT*)malloc(sizeof(BINT));
    if(!*bint_ptr) {
        fprintf(stderr, "Error: Unable to allocate memory for BINT.\n");
        exit(1);
    }
    // Allocate memory for val (array of WORD)
    (*bint_ptr)->val = (WORD*)calloc(wordlen,sizeof(WORD));
    if (!(*bint_ptr)->val) {
        free(*bint_ptr); // freeing the already allocated BINT memory before exiting
        fprintf(stderr, "Error: Unable to allocate memory for BINT val.\n");
        exit(1);
    }
    // Initialize structure members
    (*bint_ptr)->sign = NON_NEGATIVE;
    (*bint_ptr)->wordlen = wordlen;
    return *bint_ptr;
}

// Function to delete a BINT structure
void delete_bint(BINT** bint_ptr) {
    if (bint_ptr && *bint_ptr) {
        free((*bint_ptr)->val); // Free the allocated memory for val
        free(*bint_ptr); // Free the allocated memory for BINT structure
        *bint_ptr = NULL; // Set the pointer to NULL after freeing memory to avoid using a dangling pointer
    }
}

void printHex(BINT* X) {
    printf("0x ");
    for (int i=X->wordlen-1; i>=0; i--)
        printf("%08x ", X->val[i]);
    printf("\n");
}

void custom_printHex_xyz(BINT* X, BINT* Y, BINT* Z, int n) {
    //print X 
    printf("0x ");
    for(int i=0; i<(n-X->wordlen); i++)
        printf("%08x ", 0);
    for (int i=X->wordlen-1; i>=0; i--)
        printf("%08x ", X->val[i]);
    printf("\n");

    //print Y
    printf("0x ");
    for(int i=0; i<(n-Y->wordlen); i++)
        printf("%08x ", 0);
    for (int i=Y->wordlen-1; i>=0; i--)
        printf("%08x ", Y->val[i]);
    printf("\n");

    //print line
    printf("--");
    for(int i=0; i<n; i++) {
        printf("-");
        printf("--------");
    } printf("\n");

    //print Z
    printf("0x ");
    for(int i=0; i<n-Z->wordlen; i++)
        printf("%08x ", 0);
    for (int i=Z->wordlen-1; i>=0; i--)
        printf("%08x ", Z->val[i]);
    printf("\n");
}

void custom_printHex_xy(BINT* X, BINT* Y, int n) {
    //print X 
    printf("x: 0x ");
    for(int i=0; i<(n-X->wordlen); i++)
        printf("%08x ", 0);
    for (int i=X->wordlen-1; i>=0; i--)
        printf("%08x ", X->val[i]);
    printf("\n");

    //print Y
    printf("y: 0x ");
    for(int i=0; i<(n-Y->wordlen); i++)
        printf("%08x ", 0);
    for (int i=Y->wordlen-1; i>=0; i--)
        printf("%08x ", Y->val[i]);
    printf("\n");
}

void refine_BINT(BINT* X) {
    if(X == NULL) return;

    int new_wordlen = X->wordlen;
    while (new_wordlen > 1) { // at least one word needed
        if(X->val[new_wordlen-1] != 0)
            break;
        new_wordlen--;
    }
    if(X->wordlen != new_wordlen) {
        X->wordlen = new_wordlen;
        X->val = (WORD*)realloc(X->val, sizeof(WORD)*new_wordlen);
    }

    if((X->wordlen == 1) && (X->val[0] == 0))
        X->sign = NON_NEGATIVE;
}

//Generate Random BINT
void rand_bint(BINT**x, int sign, int wordlen) {
    init_bint(x, wordlen);
    (*x)->sign = sign;
    rand_array((*x)->val, wordlen);

    refine_BINT(*x);
}
void rand_array(WORD* dst, int wordlen) {
    u8* p = (u8*)dst; //u8 = byte
    int cnt = wordlen * sizeof(WORD);
    while(cnt>0) {
        *p = rand() & 0xFF;
        p++;
        cnt--;
    }
}


/* 6. Addition and Subtraction */
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

    // Allocate space for Z = X + Y;
    /*
    BINT* Z = (BINT*)malloc(sizeof(BINT));
    if (!Z) { //Z(BINT* == NULL
        perror("Unable to allocate memory");
        exit(1);
    }
    Z->val = (WORD*)calloc(n + 1,sizeof(WORD)); // +1 for possible carry
    if (!Z->val) {
        perror("Unable to allocate memory");
        free(Z);
        exit(1);
    }*/

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
