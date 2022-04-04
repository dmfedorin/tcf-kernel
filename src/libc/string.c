#include "libc/string.h"

#include <stdbool.h>

void
memset(void *dst, uint8_t b, int size)
{
        for (int i = 0; i < size; ++i)
                *((uint8_t *)dst + i) = b;
}

void
memcpy(void *restrict dst, const void *restrict src, int size)
{
        for (int i = 0; i < size; ++i)
                *((uint8_t *)dst + i) = *((uint8_t *)src + i);
}

void
strcpy(char *restrict dst, const char *restrict src)
{
        int i;
        for (i = 0; src[i] != '\0'; ++i)
                dst[i] = src[i];
        dst[i + 1] = '\0'; /* add null terminator */
}

void
strncpy(char *restrict dst, const char *restrict src, int size)
{
        int i;
        for (i = 0; src[i] != '\0' && i < size; ++i)
                dst[i] = src[i];
        dst[i + 1] = '\0'; /* add null terminator */
}

void
strcat(char *restrict dst, const char *restrict src)
{
        for (; *dst != '\0'; ++dst)
                continue;
        strcpy(dst, src);
}

void
strncat(char *restrict dst, const char *restrict src, int size)
{
        for (; *dst != '\0'; ++dst)
                continue;
        strncpy(dst, src, size);
}

int
strlen(const char *s)
{
        int len;
        for (len = 0; s[len] != '\0'; ++len)
                continue;
        return len;
}

int
strcmp(const char *restrict s1, const char *restrict s2)
{
        while (*s1 != '\0' || *s2 != '\0')
        {
                if (*s1 > *s2)
                        return 1;
                else if (*s1 < *s2)
                        return -1;
                else
                {
                        ++s1;
                        ++s2;
                }
        }
        return 0;
}

void
memmove(void *dst, const void *src, int size)
{
        for (int i = 0; i < size; ++i)
                *((uint8_t *)dst + i) = *((uint8_t *)src + i);
}
