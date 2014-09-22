#ifndef COLOR_H

#define COLOR_H

typedef struct {
	float c[3];
} Color;

void Color_copy(Color *to, Color *from);
void Color_set(Color *to, float r, float g, float b);

#endif
