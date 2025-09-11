#include "common.h"

void putchar(char ch);

void* memset(void* buf, char c, size_t n)
{
    uint8_t *p = (uint8_t*) buf;
    while (n--)
    {
        *p++ = c;
    }
    return buf;
}

void* memcpy(void* dst, const void* src, size_t n)
{
    uint8_t* d = (uint8_t*)dst;
    uint8_t* s = (uint8_t*)src; 
    while (n--)
    {
        *d++ = *s++;
    }
    return dst;
}

void* strcpy(char* dst, const char* src)
{
    char* d = dst;
    while (*src)
    {
        *d++ = *src++;
    }

    *d = '\0';
    return dst;
}

int strcmp(const char* s1, const char* s2)
{
    while (*s1 && *s2)
    {
        if (*s1 != *s2)
            break;

        s1++;
        s2++;
    }

    return *(unsigned char*)s1 - *(unsigned char*)s2;
}

void printf(const char* fmt, ...)
{
    va_list vargs;
    va_start(vargs, fmt);

    while (*fmt)
    {
        if (*fmt != '%')
        {
            putchar(*fmt);
        }
        else    // handle format
        {
            fmt++; // skip '%'
            switch(*fmt)
            {
                case '\0':
                    putchar('%');
                    goto end;

                case '%':   // print '%'
                    putchar('%');
                    break;

                case 's':   // print string
                {
                    const char* s = va_arg(vargs, const char*);
                    while (*s)
                    {
                        putchar(*s);
                        s++;
                    }
                    break;
                }

                case 'd':   // print integral in decimal
                {
                    int value = va_arg(vargs, int);
                    unsigned magnitude = value;
                    if (value < 0)
                    {
                        putchar('-');
                    }

                    unsigned divisor = 1;
                    while (magnitude / divisor > 9)
                    {
                        divisor *= 10;
                    }

                    while (divisor > 0)
                    {
                        putchar('0' + magnitude / divisor);
                        magnitude %= divisor;
                        divisor /= 10;
                    }
                    break;
                }

                case 'x':   // print integral in hexadecimal
                {
                    unsigned value = va_arg(vargs, unsigned);
                    for (int i = 7; i >= 0; i--)
                    {
                        unsigned nibble = (value >> (i * 4)) & 0xf;
                        putchar("0123456789abcdef"[nibble]);
                    }
                    break;
                }
            }
        }

        fmt++;
    }

end:
    va_end(vargs);
}