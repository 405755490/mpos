
#ifndef _FONT_H
#define _FONT_H

struct font_desc {
    int idx;
    const char *name;
    int width, height;
    const unsigned char *data;
    int pref;
};

#define VGA8x8_IDX	0
#define VGA8x16_IDX	1
#define PEARL8x8_IDX	2
#define VGA6x11_IDX	3
#define FONT7x14_IDX	4
#define	FONT10x18_IDX	5
#define SUN8x16_IDX	6
#define SUN12x22_IDX	7
#define ACORN8x8_IDX	8
#define	MINI4x6_IDX	9

extern const struct font_desc font_10x18;

#endif
