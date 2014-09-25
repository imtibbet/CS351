#ifndef FLOODFILL_H

#define FLOODFILL_H

typedef struct {
    Pixel pix;
    Pixel push;
    Color color;
}

void floodfill(Point *vlist, Image *src, Color c);