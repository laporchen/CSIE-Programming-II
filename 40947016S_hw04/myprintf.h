#pragma once
#include "stdarg.h"
#include "stdint.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
typedef char string[10000];
int myprintf(const string re, ...);
void int2str(string s, int32_t n);
void reverse(string s);
void u2h(string s, uint32_t n, char mode);