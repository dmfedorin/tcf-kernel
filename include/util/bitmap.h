#ifndef BITMAP_H_UsvCCAN8rtbvMJwG8VpeKXag4b4KZq7T
#define BITMAP_H_UsvCCAN8rtbvMJwG8VpeKXag4b4KZq7T

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

typedef struct
{
        uint8_t *data;
        size_t size_bits;
} bitmap;

bool
bitmap_bit(const bitmap *bm, size_t ind);

void
set_bitmap_bit(bitmap *bm, size_t ind, bool state);

void
print_bitmap(const bitmap *bm);

#endif
