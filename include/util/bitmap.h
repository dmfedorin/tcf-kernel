#ifndef BITMAP_H_UsvCCAN8rtbvMJwG8VpeKXag4b4KZq7T
#define BITMAP_H_UsvCCAN8rtbvMJwG8VpeKXag4b4KZq7T

#include <stdint.h>
#include <stdbool.h>

typedef struct
{
        uint8_t *data;
        int size_bits;
} bitmap;

bool
bitmap_bit(const bitmap *bm, int ind);

void
set_bitmap_bit(bitmap *bm, int ind, bool state);

void
print_bitmap(const bitmap *bm);

#endif
