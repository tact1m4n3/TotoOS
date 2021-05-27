#include <core/utils.h>

char* convert(uint64_t num, uint64_t base)
{
    static char chrs[] = "0123456789ABCDEF";
    static char buffer[50];
    char* ptr = &buffer[49];

    *ptr = '\0';

    do
    {
        *--ptr = chrs[num % base];
        num /= base;
    } while (num != 0);
    
    return ptr;
}
