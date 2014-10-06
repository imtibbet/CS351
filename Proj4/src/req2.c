/*
Astrid Moore
Fall 2014

Generates a flower that looks 3D.
*/

#include "graphics.h"
#include <stdio.h>
#include <stdlib.h>


int main(int argc, char *argv[]){
	
    // create an image
    Image *src;
    int rows = 600;
    int cols = 500;
    int k, x, y;
    src = image_create(rows, cols);

    // set up point structure
    const int nPoints = 1000;
    Point pt[nPoints];

    // declare shapes
	Polygon *stem;
    Circle center, petal;
    
	// declare colors 
	Color Grey, White, dkGrey, vdkGrey, ltGrey, 
        ltRed, Red, dkRed, ltBlue, dkBlue, ltGreen, 
        Green, dkGreen, ltYellow, Yellow, dkYellow;

	// set up color palette
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

    Color *centerPistils[4]={&ltYellow, &Yellow, &dkYellow, &ltRed};

    // stem - light green rectangle
    point_set2D(&(pt[0]), 240, 450);
    point_set2D(&(pt[1]), 240, 250);
    point_set2D(&(pt[2]), 260, 250);
    point_set2D(&(pt[3]), 260, 450);
    stem = polygon_createp(4, &(pt[0]));
    polygon_drawFill(stem, src, ltGreen);
    point_set2D(&(pt[4]), 240, 450);
    point_set2D(&(pt[5]), 240, 250);
    point_set2D(&(pt[6]), 255, 250);
    point_set2D(&(pt[7]), 255, 450);
    stem = polygon_createp(4, &(pt[4]));
    polygon_drawFill(stem, src, Green);
    point_set2D(&(pt[8]), 240, 450);
    point_set2D(&(pt[9]), 240, 250);
    point_set2D(&(pt[10]), 245, 250);
    point_set2D(&(pt[11]), 245, 450);
    stem = polygon_createp(4, &(pt[8]));
    polygon_drawFill(stem, src, dkGreen);   

    // petals of the flower
    point_set2D(&(pt[13]), 250, 270);
    circle_set(&petal, pt[13], 35);
    circle_drawFill(&petal, src, ltBlue);
    point_set2D(&(pt[14]), 250, 265);
    circle_set(&petal, pt[14], 30);
    circle_drawFill(&petal, src, White);
    point_set2D(&(pt[15]), 250, 260);
    circle_set(&petal, pt[15], 25);
    circle_drawFill(&petal, src, dkBlue);
    //
    point_set2D(&(pt[16]), 210, 255);
    circle_set(&petal, pt[16], 35);
    circle_drawFill(&petal, src, ltBlue);
    point_set2D(&(pt[17]), 215, 250);
    circle_set(&petal, pt[17], 30);
    circle_drawFill(&petal, src, White);
    point_set2D(&(pt[18]), 220, 245);
    circle_set(&petal, pt[18], 25);
    circle_drawFill(&petal, src, dkBlue);
    //
    point_set2D(&(pt[19]), 200, 220);
    circle_set(&petal, pt[19], 35);
    circle_drawFill(&petal, src, ltBlue);
    point_set2D(&(pt[20]), 210, 218);
    circle_set(&petal, pt[20], 30);
    circle_drawFill(&petal, src, White);
    point_set2D(&(pt[21]), 215, 216);
    circle_set(&petal, pt[21], 25);
    circle_drawFill(&petal, src, dkBlue);
    //
    point_set2D(&(pt[22]), 210, 185);
    circle_set(&petal, pt[22], 35);
    circle_drawFill(&petal, src, ltBlue);
    point_set2D(&(pt[23]), 214, 190);
    circle_set(&petal, pt[23], 30);
    circle_drawFill(&petal, src, White);
    point_set2D(&(pt[24]), 218, 193);
    circle_set(&petal, pt[24], 25);
    circle_drawFill(&petal, src, dkBlue);
    //
    point_set2D(&(pt[25]), 250, 170);
    circle_set(&petal, pt[25], 35);
    circle_drawFill(&petal, src, ltBlue);
    point_set2D(&(pt[26]), 250, 175);
    circle_set(&petal, pt[26], 30);
    circle_drawFill(&petal, src, White);
    point_set2D(&(pt[27]), 250, 180);
    circle_set(&petal, pt[27], 25);
    circle_drawFill(&petal, src, dkBlue);
    //
    point_set2D(&(pt[28]), 290, 185);
    circle_set(&petal, pt[28], 35);
    circle_drawFill(&petal, src, ltBlue);
    point_set2D(&(pt[29]), 285, 190);
    circle_set(&petal, pt[29], 30);
    circle_drawFill(&petal, src, White);
    point_set2D(&(pt[30]), 280, 193);
    circle_set(&petal, pt[30], 25);
    circle_drawFill(&petal, src, dkBlue);   
    //
    point_set2D(&(pt[31]), 295, 235);
    circle_set(&petal, pt[31], 35);
    circle_drawFill(&petal, src, ltBlue);
    point_set2D(&(pt[32]), 290, 230);
    circle_set(&petal, pt[32], 30);
    circle_drawFill(&petal, src, White);
    point_set2D(&(pt[33]), 285, 225);
    circle_set(&petal, pt[33], 25);
    circle_drawFill(&petal, src, dkBlue);

    // center
    srand(time(NULL));
    for(k = 34; k < 300; k++){
        // generate random coords within the 
        // general circ of the center
        x = rand() % 40 + 230;
        y = rand() % 40 + 200;

        printf("x:%d\n", x);
        printf("y:%d\n", y);

        point_set2D(&(pt[k]), x, y);
        circle_set(&center, pt[k], 2);
        // draw pistils as one of 4 colors, chosen randomly
        circle_drawFill(&center, src, *centerPistils[rand() % 4]);
    }

    // write out the image 
	image_write(src, "req2.ppm");

    // clear shapes from memory
    polygon_clear(stem);

    // free image
    image_free(src);

	return(0);
}