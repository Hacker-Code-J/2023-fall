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
#define OK 0
#define Err_Overflow 1

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
    printf("Hex: ");
    for (int i = X->wordlen - 1; i >= 0; i--) {
        printf("%*x ", 3, X->val[i]);
    }
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

/* 6. Addition and Subtraction */

typedef struct {
    WORD sum;
    WORD carry;
} SumAndCarry;

SumAndCarry ADD_XYk(WORD x, WORD y, WORD k) {
    SumAndCarry sc;
    unsigned long long res = (unsigned long long) x + y + k;  // casting to prevent overflow
    sc.sum = (WORD) (res & 0xFFFFFFFF); // assuming 32-bit words, adjust mask as needed
    sc.carry = (WORD) (res >> 32);
    printf("%08x + %08x = %08x * W + %08x\n", x, y, sc.carry, sc.sum);
    return sc;
}

BINT* add_xy(BINT* X, BINT* Y) {
    int n = X->wordlen;
    int m = Y->wordlen;

    // Allocate space for Z and perform addition
    BINT* Z = malloc(sizeof(BINT));
    if (Z == NULL) {
        perror("Unable to allocate memory");
        exit(EXIT_FAILURE);
    }

    // Allocate space for Z and perform addition
    Z->val = malloc((n + 1) * sizeof(WORD)); // +1 for possible carry
    if (Z->val == NULL) {
        perror("Unable to allocate memory");
        free(Z);
        exit(1);
    }

    // Ensure Y <= X, if not, swap X and Y
    if (Y->wordlen > X->wordlen) {
        BINT* temp = X; X = Y; Y = temp;
    }

    // Extend Y.val with zeros to make Y and X the same length
    WORD* tmp_val = NULL;
    tmp_val = (WORD*)realloc(Y->val, sizeof(WORD)*n);
    if (!tmp_val) {
        perror("Unable to allocate memory");
        exit(1);
    } else {
        Y->val = tmp_val;
    }
    for (int i = Y->wordlen; i < X->wordlen; i++) {
        Y->val[i] = (WORD)0;
    }

    WORD k = 0;
    for (int i = 0; i < X->wordlen; i++) {
        SumAndCarry sc = ADD_XYk(X->val[i], Y->val[i], k);
        Z->val[i] = sc.sum;
        k = sc.carry;
    }
    Z->val[X->wordlen] = k;

    // Set the sign and word length of Z
    Z->sign = X->sign; // assuming the same sign for X and Y
    Z->wordlen = (k == 0) ? X->wordlen : X->wordlen + 1;

    // Free or reset the memory for Y->val if needed
    // free(Y->val); // if needed
    // Y->wordlen = original_length; // if needed

    return Z;
}

#endif
