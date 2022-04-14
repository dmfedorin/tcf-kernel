#ifndef STRING_H_vQF06FotN08vb2MkV4Zt2yspFF2ZYOlt
#define STRING_H_vQF06FotN08vb2MkV4Zt2yspFF2ZYOlt

#include <stdint.h>
#include <stddef.h>

void
memset(void *dst, uint8_t b, size_t size);

void
memcpy(void *restrict dst, const void *restrict src, size_t size);

void
strcpy(char *restrict dst, const char *restrict src);

void
strncpy(char *restrict dst, const char *restrict src, size_t size);

void
strcat(char *restrict dst, const char *restrict src);

void
strncat(char *restrict dst, const char *restrict src, size_t size);

size_t
strlen(const char *s);

size_t
strcmp(const char *restrict s1, const char *restrict s2);

void
memmove(void *dst, const void *src, size_t size);

#endif
