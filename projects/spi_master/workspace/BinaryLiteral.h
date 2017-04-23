
#pragma once

// http://stackoverflow.com/questions/2611764/can-i-use-a-binary-literal-in-c-or-c
// http://stackoverflow.com/a/15114188

#define B(x) BinaryLiteral(#x)

static inline unsigned long long BinaryLiteral(const char *s)
{
    unsigned long long i = 0;
    while (*s) {
        i <<= 1;
        i += *s++ - '0';
    }
    return i;
}