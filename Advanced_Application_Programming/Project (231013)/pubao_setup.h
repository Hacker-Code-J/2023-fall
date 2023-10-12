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

/*2. Macro*/

/*3. 16-byte BINT Structure */
/**********************************************************************
* +---------------------+
* |   BINT(128-bit)     |
* +---------------------+
* |    sign (int)       |  --> NEGATIVE or NON_NEGATIVE
* +---------------------+
* |   wordlen (int)     |  --> n-word BINT
* +---------------------+
* |    val (WORD*)      |  --> [addr]-->+---------+---------+---+---------+
* +---------------------+               | WORD[0] | WORD[1] |...| WORD[n] |
*                                       +---------+---------+---+---------+
**********************************************************************/
typedef struct {
    int sign; // 0 = NON_NEGATIVE, 1 = NEGATIVE
    int wordlen; // n-word BINT, n = wordlen
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
BINT* init_bint(BINT** bint_ptr, int wordlen);

// Function to delete a BINT structure
void delete_bint(BINT** bint_ptr);

void printHex(BINT* X);

/**********************************************************************
* x: [sgn] 0x ######## ######## 
* y: [sgn] 0x ######## ######## 
**********************************************************************/
void custom_printHex_xy(BINT* X, BINT* Y, int n);

/**********************************************************************
*   [sgn] 0x ######## ######## 
* @ [sgn] 0x ######## ######## 
* ----------------------------
*   [sgn] 0x ######## ########
*
* @:option - 0: '+' | 1: '-' | 2: '*'
**********************************************************************/
void custom_printHex(BINT* X, BINT* Y, BINT* Z,  int option);

void refine_BINT(BINT* X);

//Generate Random BINT

void rand_array(WORD* dst, int wordlen);
void rand_bint(BINT**x, int sign, int wordlen);

//Copy Arrary
void array_copy_x2y(WORD* X, WORD* Y, int wordlen);

//Assign Y<-X
void assgin_x2y(BINT* X, BINT** Y);

//Compare
// X>Y return 1
// X<Y return -1
// X=Y return 0
int compare_xy(BINT* X, BINT* Y);

//Author: Moon Ye-chan
int Get_bitlen(BINT* x);
int Get_sign(BINT* x);
void Flip_sign(BINT* x);

//Author: Kim Ye-chan
void DIV_Shift(BINT* bigint, BINT* result, int N);// DIV shift  
void MUL_Shift(BINT* bigint, BINT* result , int N); // MUL shift

#endif