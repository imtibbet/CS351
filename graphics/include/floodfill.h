#ifndef FLOODFILL_H

#define FLOODFILL_H

typedef struct {
	FPixel *p;
	int x;
	int y;
} FPixelStackItem;

void polygon_drawFill(Image *src, Color borderc, Color fillc, int xSeed, int ySeed);
#endif
