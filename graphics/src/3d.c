/*
Astrid Moore (Bruce A. Maxwell)
Fall 2014

Generates a required image that looks 3D.
*/

#include "graphics.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
	const int nPoints = 1000;
	Polyline box;
	Image *src;
	Point p[nPoints];
	Color black;
	Color grey;
	int rows = 500;
	int cols = 500;

	// create an image
	src = image_create(rows, cols);

	// set up color palette
	color_set(&black, 0.0, 0.0, 0.0);
	color_set(&grey, 0.38, 0.39, 0.4);

	// draw a box
	point_set2D(&p[0], 150, 100);
	point_set2D(&p[1], 150, 350);
	point_set2D(&p[2], 400, 330);
	point_set2D(&p[3], 400, 70);
	point_set2D(&p[4], 150, 100);

	//set up polyline
	polyline_init(&box);
	polyline_set(&box, 5, &(p[0]));
	polyline_draw(&box, src, grey);

	image_write(src, "test3A.ppm");

	polyline_clear(&box);
	image_free(src);

	return(0);
}