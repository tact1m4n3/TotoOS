#pragma once

#include <core/utils.h>

#define nullptr 0

typedef unsigned char uint8_t;
typedef unsigned short uint16_t;
typedef unsigned int uint32_t;
typedef unsigned long long uint64_t;
typedef unsigned long long size_t;

char* convert(size_t num, size_t base);
