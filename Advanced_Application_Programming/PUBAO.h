/*1. Maximum Number of Bits and Parameters*/
#define MAX_BITS 4096; //2^12

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef unsigned long u64;

/*2. Macro*/

/*3. BIGINT Structure*/
typedef struct {
    int sign; // + or -
    int wordlen; // >=0
    u32* a; // address for BIGINT
} BIGINT;

/*4. Error*/
#define OK 0
#define Err_Overflow -1

/*5. Funtions*/
void create_BIGINT(BIGINT**, int);
void delete_BIGINT(BIGINT**);

void show_hex_BIGINT(BIGINT*);
void show_dec_BIGINT(BIGINT*);
void show_bin_BIGINT(BIGINT*);

// bigint <- base string
int set_by_array_BIGINT(BIGINT**, int, u32*, int);
int set_by_string_BIGINT(BIGINT**, int, char*, int);

void refine_BIGINT(BIGINT*);

void assign_BIGINT(BIGINT*, BIGINT*);

void gen_rand_BIGINT(BIGINT**, int, int);
void arrary_rand(u32*, int);

void set_zero_BIGINT(BIGINT**);
void set_one_BIGINT(BIGINT**);
