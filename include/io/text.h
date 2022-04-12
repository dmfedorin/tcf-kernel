#ifndef TEXT_H_Smuf1wp6edV672167HAHWASVk7XhzAbs
#define TEXT_H_Smuf1wp6edV672167HAHWASVk7XhzAbs

#include <stdint.h>

#define TAB_SIZE 8

void
put_char(char c);

void
put_str(const char *s);

void
put_hex(const void *h, int size);

void
clear_screen(void);

void
set_text_back_stop_pos(int bsp);

int
text_cursor_pos(void);

typedef enum
{
        TEXT_COLOR_BLACK = 0x0,
        TEXT_COLOR_BLUE = 0x1,
        TEXT_COLOR_GREEN = 0x2,
        TEXT_COLOR_CYAN = 0x3,
        TEXT_COLOR_RED = 0x4,
        TEXT_COLOR_MAGENTA = 0x5,
        TEXT_COLOR_BROWN = 0x6,
        TEXT_COLOR_LIGHT_GRAY = 0x7,
        TEXT_COLOR_GRAY = 0x8,
        TEXT_COLOR_LIGHT_BLUE = 0x9,
        TEXT_COLOR_LIGHT_GREEN = 0xa,
        TEXT_COLOR_LIGHT_CYAN = 0xb,
        TEXT_COLOR_LIGHT_RED = 0xc,
        TEXT_COLOR_LIGHT_MAGENTA = 0xd,
        TEXT_COLOR_LIGHT_BROWN = 0xe,
        TEXT_COLOR_WHITE = 0xf,
} text_color;

void
set_text_attr(text_color fg, text_color bg);

text_color
text_bg_color(void);

text_color
text_fg_color(void);

/* scrolling will lose information */
void
scroll_text_down(void);

void
put_ptr(const void *ptr);

#endif
