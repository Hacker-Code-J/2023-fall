#include <stdio.h>

#define unsigned int u32

typedef struct {
  int sign;
  int wordlen;
  u32* a;
} BIGINT;
