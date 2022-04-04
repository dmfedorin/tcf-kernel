#ifndef STRING_H_vQF06FotN08vb2MkV4Zt2yspFF2ZYOlt
#define STRING_H_vQF06FotN08vb2MkV4Zt2yspFF2ZYOlt

#include <stdint.h>

void
memset(void *dst, uint8_t b, int size);

void
memcpy(void *restrict dst, const void *restrict src, int size);

void
strcpy(char *restrict dst, const char *restrict src);

void
strncpy(char *restrict dst, const char *restrict src, int size);

void
strcat(char *restrict dst, const char *restrict src);

void
strncat(char *restrict dst, const char *restrict src, int size);

int
strlen(const char *s);

int
strcmp(const char *restrict s1, const char *restrict s2);

void
memmove(void *dst, const void *src, int size);

#endif
