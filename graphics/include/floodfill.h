#ifndef FLOODFILL_H

#define FLOODFILL_H

typedef struct {
	FPixel *p;
	int r;
	int c;
} FPixelStackItem;

void floodfill(Image *src, Color c, int xSeed, int ySeed);
#endif
