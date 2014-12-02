#ifndef FLOODFILL_H

#define FLOODFILL_H

typedef struct {
	FPixel *p;
	int x;
	int y;
} FPixelStackItem;

void floodfill(Image *src, Color borderc, Color fillc, int xSeed, int ySeed);
#endif
