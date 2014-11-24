#ifndef COLOR_H

#define COLOR_H

typedef struct {
	float c[3];
} Color;

void color_copy(Color *to, Color *from);
void color_set(Color *to, float r, float g, float b);
int color_compare(Color a, Color b);
void color_print(Color c, FILE *fp);

#endif
