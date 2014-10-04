/*
Astrid Moore
Fall 2014

Generates a required image that looks 3D.
*/

#include "graphics.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
	
    // create an image
    Image *src;
    int rows = 600;
    int cols = 500;
    src = image_create(rows, cols);

    // set up point structure
    const int nPoints = 1000;
    Point *pt[nPoints];
    Ellipse *nose;

    // declare shapes
	Polygon *body, *wings;
    
	// declare colors 
	Color Grey, White, dkGrey, ltGrey, ltRed, Red, dkRed, ltBlue;
	
	// set up color palette
	color_set(&White, 1.0, 1.0, 1.0);
    color_set(&Grey, 0.38, 0.39, 0.4);
    color_set(&ltGrey, 0.5, 0.5, 0.5);
    color_set(&dkGrey, 0.3, 0.3, 0.3);
    color_set(&Red, 0.7, 0.04, 0.05);    
    color_set(&ltRed, 0.86, 0.0, 0.07);
    color_set(&dkRed, 0.43, 0.04, 0.004);
    color_set(&ltBlue, 1.0, 1.0, 0.9);

    // wings of space shuttle - dark grey triangle for trim
    point_set2D(pt[4], 50, 480);
    point_set2D(pt[5], 250, 300);
    point_set2D(pt[6], 450, 480);
    wings = polygon_createp(3, pt[4]);
    printf("drawing dark frame of shuttles wings\n");
    polygon_drawFillB(wings, src, dkGrey);
    // wings - white triangle overlay
    point_set2D(pt[7], 75, 465);
    point_set2D(pt[8], 250, 300);
    point_set2D(pt[9], 425, 465);
    wings = polygon_createp(3, pt[7]);
    printf("overlaiying white onto wings\n");
    polygon_drawFillB(wings, src, White);
    // wings - white polygon for outer tips
    point_set2D(pt[13], 180, 370);
    point_set2D(pt[14], 200, 180);
    point_set2D(pt[15], 300, 180);
    point_set2D(pt[16], 320, 370);
    point_set2D(pt[17], 180, 370);
    wings = polygon_createp(5, pt[13]);
    printf("extending wings\n");
    polygon_drawFill(wings, src, White);
    
    // body - grey rectanlge
    point_set2D(pt[0], 200, 465);
    point_set2D(pt[1], 200, 180); 
    point_set2D(pt[2], 300, 180);
    point_set2D(pt[3], 300, 465);
    body = polygon_createp(4, pt[0]);
    printf("drawing body of shuttle\n");
    polygon_drawFill(body, src, ltGrey);

    // nose - white ellipse
    point_set2D(pt[50], 250.0, 300.0);
    ellipse_set(nose, *pt[50], 50.0, 100.0);
    printf("drawing nose of shuttle\n");
    ellipse_drawFill(nose, src, White);

    // write out the image 
	image_write(src, "req1.ppm");

    // clear shapes from memory
    polygon_clear(body);
    polygon_clear(wings);


    // free image
    image_free(src);

	return(0);
}