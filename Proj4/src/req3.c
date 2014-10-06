/*
Astrid Moore
Fall 2014

Generates a creature that looks 3D.
*/

#include "graphics.h"
#include <stdio.h>
#include <stdlib.h>


int main(int argc, char *argv[]){
	
    // create an image
    Image *src;
    int rows = 500;
    int cols = 500;
    int k, x, y;
    src = image_create(rows, cols);

    // set up point structure
    const int nPoints = 1000;
    Point pt[nPoints];

    // declare shapes
    Ellipse head, body; 
    Polyline whisker;
    Polygon ear;   

    
	// declare colors 
	Color Black, Grey, White, dkGrey, vdkGrey, ltGrey, 
        ltRed, Red, dkRed, ltBlue, dkBlue, ltGreen, 
        Green, dkGreen, ltYellow, Yellow, dkYellow;

	// set up color palette
    color_set(&Black, 0.0, 0.0, 0.0);
	color_set(&White, 1.0, 1.0, 1.0);
    color_set(&Grey, 0.38, 0.39, 0.4);
    color_set(&ltGrey, 0.5, 0.5, 0.5);
    color_set(&dkGrey, 0.3, 0.3, 0.3);
    color_set(&vdkGrey, 0.2, 0.2, 0.2);
    color_set(&Red, 0.7, 0.04, 0.05);    
    color_set(&ltRed, 0.86, 0.0, 0.07);
    color_set(&dkRed, 0.43, 0.04, 0.004);
    color_set(&ltBlue, 0.1, 0.2, 0.5);
    color_set(&dkBlue, 0.1, 0.2, 0.3);
    color_set(&ltGreen, 0.44, 0.65, 0.02);
    color_set(&Green, 0.33, 0.54, 0.21);
    color_set(&dkGreen, 0.28, 0.4, 0.16);
    color_set(&ltYellow, 1.0, 1.0, 0.7);
    color_set(&Yellow, 1.0, 0.84, 0.35);
    color_set(&dkYellow, 0.78, 0.6, 0.17);

    // body
    point_set2D(&(pt[37]), 250, 310);
    ellipse_set(&body, pt[37], 30, 40);
    ellipse_drawFill(&body, src, dkGrey);
    point_set2D(&(pt[38]), 255, 310);
    ellipse_set(&body, pt[38], 30, 40);
    ellipse_drawFill(&body, src, Grey);
    // hindpaws 
    point_set2D(&(pt[42]), 235, 335);
    ellipse_set(&body, pt[42], 20, 10);
    ellipse_drawFill(&body, src, dkGrey);
    point_set2D(&(pt[43]), 275, 338);
    ellipse_set(&body, pt[43], 15, 10);
    ellipse_drawFill(&body, src, dkGrey);
    point_set2D(&(pt[44]), 235, 340);
    ellipse_set(&body, pt[44], 10, 5);
    ellipse_drawFill(&body, src, Grey);
    point_set2D(&(pt[45]), 275, 340);
    ellipse_set(&body, pt[45], 10, 5);
    ellipse_drawFill(&body, src, Grey);
    // legs
    point_set2D(&(pt[39]), 245, 325);
    ellipse_set(&body, pt[39], 8, 28);
    ellipse_drawFill(&body, src, dkGrey);
    point_set2D(&(pt[40]), 247, 325);
    ellipse_set(&body, pt[40], 8, 28);
    ellipse_drawFill(&body, src, ltGrey);
    point_set2D(&(pt[41]), 268, 325);
    ellipse_set(&body, pt[41], 8, 28);
    ellipse_drawFill(&body, src, dkGrey);
    point_set2D(&(pt[41]), 270, 325);
    ellipse_set(&body, pt[41], 8, 28);
    ellipse_drawFill(&body, src, ltGrey);
    // forepaws
    point_set2D(&(pt[46]), 245, 350);
    ellipse_set(&body, pt[46], 8, 5);
    ellipse_drawFill(&body, src, ltGrey);
    point_set2D(&(pt[47]), 270, 350);
    ellipse_set(&body, pt[47], 8, 5);
    ellipse_drawFill(&body, src, ltGrey);

    
    // head
    point_set2D(&(pt[0]), 255, 250);
    ellipse_set(&head, pt[0], 51, 35);
    ellipse_drawFill(&head, src, dkGrey);
    point_set2D(&(pt[1]), 260, 250);
    ellipse_set(&head, pt[1], 50, 35);
    ellipse_drawFill(&head, src, ltGrey);
    point_set2D(&(pt[2]), 245, 250);
    ellipse_set(&head, pt[2], 14, 10);
    ellipse_drawFill(&head, src, Grey);
    point_set2D(&(pt[3]), 290, 250);
    ellipse_set(&head, pt[3], 14, 10);
    ellipse_drawFill(&head, src, Grey);
    // eyes
    point_set2D(&(pt[4]), 245, 250);
    ellipse_set(&head, pt[4], 12, 8);
    ellipse_drawFill(&head, src, Black);
    point_set2D(&(pt[5]), 290, 250);
    ellipse_set(&head, pt[5], 12, 8);
    ellipse_drawFill(&head, src, Black);
    point_set2D(&(pt[6]), 245, 250);
    ellipse_set(&head, pt[6], 6, 8);
    ellipse_drawFill(&head, src, dkGreen);
    point_set2D(&(pt[7]), 290, 250);
    ellipse_set(&head, pt[7], 6, 8);
    ellipse_drawFill(&head, src, dkGreen);
    point_set2D(&(pt[8]), 245, 250);
    ellipse_set(&head, pt[8], 5, 8);
    ellipse_drawFill(&head, src, ltGreen);
    point_set2D(&(pt[9]), 290, 250);
    ellipse_set(&head, pt[9], 5, 8);
    ellipse_drawFill(&head, src, ltGreen);
    point_set2D(&(pt[10]), 245, 250);
    ellipse_set(&head, pt[10], 3, 8);
    ellipse_drawFill(&head, src, Black);
    point_set2D(&(pt[11]), 290, 250);
    ellipse_set(&head, pt[11], 3, 8);
    ellipse_drawFill(&head, src, Black);
    // nose
    point_set2D(&(pt[12]), 267, 265);
    ellipse_set(&head, pt[12], 7, 4);
    ellipse_drawFill(&head, src, dkGrey);
    point_set2D(&(pt[13]), 265, 265);
    ellipse_set(&head, pt[13], 2, 2);
    ellipse_drawFill(&head, src, Black);
    point_set2D(&(pt[14]), 270, 265);
    ellipse_set(&head, pt[14], 2, 2);
    ellipse_drawFill(&head, src, Black);
    // whiskers
    point_set2D(&(pt[15]), 267, 267);
    point_set2D(&(pt[16]), 267, 272);
    point_set2D(&(pt[17]), 268, 273);
    point_set2D(&(pt[17]), 269, 273);
    point_set2D(&(pt[18]), 270, 273);
    point_set2D(&(pt[19]), 270, 272);
    polyline_set(&whisker, 5, &(pt[15]));
    polyline_draw(&whisker, src, Black);
    point_set2D(&(pt[20]), 267, 272);
    point_set2D(&(pt[21]), 266, 273);
    point_set2D(&(pt[22]), 265, 273);
    point_set2D(&(pt[23]), 264, 273);
    point_set2D(&(pt[24]), 264, 272);
    polyline_set(&whisker, 5, &(pt[20]));
    polyline_draw(&whisker, src, Black);
    // ears
    point_set2D(&(pt[25]), 220, 225);
    point_set2D(&(pt[26]), 240, 195);
    point_set2D(&(pt[27]), 255, 225);
    polygon_set(&ear, 3, &(pt[25]));
    polygon_drawFillB(&ear, src, dkGrey);
    point_set2D(&(pt[28]), 260, 225);
    point_set2D(&(pt[29]), 280, 195);
    point_set2D(&(pt[30]), 295, 225);
    polygon_set(&ear, 3, &(pt[28]));
    polygon_drawFillB(&ear, src, dkGrey);
    point_set2D(&(pt[31]), 225, 225);
    point_set2D(&(pt[32]), 240, 200);
    point_set2D(&(pt[33]), 252, 225);
    polygon_set(&ear, 3, &(pt[31]));
    polygon_drawFillB(&ear, src, Grey);
    point_set2D(&(pt[34]), 265, 225);
    point_set2D(&(pt[35]), 280, 200);
    point_set2D(&(pt[36]), 292, 225);
    polygon_set(&ear, 3, &(pt[34]));
    polygon_drawFillB(&ear, src, Grey);

    // write out the image 
	image_write(src, "req3.ppm");

    // clear shapes from memory

    // free image
    image_free(src);

	return(0);
}