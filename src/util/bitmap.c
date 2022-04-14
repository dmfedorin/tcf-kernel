#include "util/bitmap.h"

#include "io/text.h"

bool
bitmap_bit(const bitmap *bm, size_t ind)
{
        size_t byte = ind / 8;
        size_t bit = ind % 8;
        uint8_t mask = 1 << bit;
        return (bm->data[byte] & mask) > 0;
}

void
set_bitmap_bit(bitmap *bm, size_t ind, bool state)
{
        size_t byte = ind / 8;
        size_t bit = ind % 8;
        uint8_t mask = 1 << bit;
        bm->data[byte] &= ~mask;
        if (state)
                bm->data[byte] |= mask;
}

void
print_bitmap(const bitmap *bm)
{
        for (size_t i = 0; i < bm->size_bits; ++i)
                put_char(bitmap_bit(bm, i) ? '1' : '0');
        put_char('\n');
}
