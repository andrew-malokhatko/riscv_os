#include "common.h"

void putchar(char ch);

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