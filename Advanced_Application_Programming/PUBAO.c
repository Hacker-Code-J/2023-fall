#include <stdio.h>

#define MAX_BITS 4096;
#define unsigned int u32

typedef struct {
  int sign;
  int wordlen;
  u32* a;
} BIGINT;

void show_hex_BIGINT(BIGINT* x) {
  int i,j,k;

  int size_u32 = sizeof(u32);
  int result = OK;

  static char str[MAX_BITS];
}
