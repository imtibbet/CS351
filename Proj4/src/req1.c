/*
Astrid Moore
Fall 2014

Generates a space ship that looks 3D.
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
    Point pt[nPoints];
    Ellipse nose, jets;

    // declare shapes
	Polygon *body, *wings, *jetpack;
    
	// declare colors 
	Color Grey, White, dkGrey, vdkGrey, ltGrey, ltRed, Red, dkRed, ltBlue, dkBlue;
	
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

    // wings - dark grey polygon
    point_set2D(&(pt[0]), 50, 475);
    point_set2D(&(pt[1]), 75, 415);
    point_set2D(&(pt[2]), 190, 265);
    point_set2D(&(pt[3]), 310, 265);
    point_set2D(&(pt[4]), 425, 415);
    point_set2D(&(pt[5]), 450, 475);
    point_set2D(&(pt[6]), 50, 475);
    wings = polygon_createp(7, &(pt[0]));
    printf("drawing outer wing trim\n");
    polygon_drawFill(wings, src, dkGrey);
    // wings - white polygon 
    point_set2D(&(pt[7]), 75, 465);
    point_set2D(&(pt[8]), 90, 430);
    point_set2D(&(pt[9]), 200, 280);
    point_set2D(&(pt[10]), 300, 280);
    point_set2D(&(pt[11]), 410, 430);
    point_set2D(&(pt[12]), 425, 465);
    point_set2D(&(pt[13]), 75, 465);
    wings = polygon_createp(7, &(pt[7]));
    printf("drawing front wings\n");
    polygon_drawFill(wings, src, White);
    // wings - white polygon for outer tips
    point_set2D(&(pt[14]), 180, 370);
    point_set2D(&(pt[15]), 200, 180);
    point_set2D(&(pt[16]), 300, 180);
    point_set2D(&(pt[17]), 320, 370);
    point_set2D(&(pt[18]), 180, 370);
    wings = polygon_createp(5, &(pt[14]));
    printf("extending wings\n");
    polygon_drawFill(wings, src, White);
    
    // body - grey rectangle
    point_set2D(&(pt[19]), 200, 465);
    point_set2D(&(pt[20]), 200, 180);
    point_set2D(&(pt[21]), 300, 180);
    point_set2D(&(pt[22]), 300, 465);
    body = polygon_createp(4, &(pt[19]));
    printf("drawing body of shuttle\n");
    polygon_drawFill(body, src, ltGrey);
    // body - dark blue rectangle
    point_set2D(&(pt[23]), 225, 465);
    point_set2D(&(pt[24]), 225, 180);
    point_set2D(&(pt[25]), 275, 180);
    point_set2D(&(pt[26]), 275, 465);
    body = polygon_createp(4, &(pt[23]));
    printf("drawing body of shuttle\n");
    polygon_drawFill(body, src, dkBlue);

    // nose - white ellipse
    point_set2D(&(pt[27]), 250, 140);
    ellipse_set(&nose, pt[27], 50, 100);
    printf("drawing nose of shuttle\n");
    ellipse_drawFill(&nose, src, White);
    // nose - dark grey ellipse
    point_set2D(&(pt[28]), 250, 160);
    ellipse_set(&nose, pt[28], 50, 100);
    printf("drawing nose of shuttle\n");
    ellipse_drawFill(&nose, src, ltBlue);
    // nose - white ellipse
    point_set2D(&(pt[29]), 250, 175);
    ellipse_set(&nose, pt[29], 50, 100);
    printf("drawing nose of shuttle\n");
    ellipse_drawFill(&nose, src, White);

    // jets - rectangle
    point_set2D(&(pt[30]), 175, 520);
    point_set2D(&(pt[31]), 175, 465);
    point_set2D(&(pt[32]), 325, 465);
    point_set2D(&(pt[33]), 325, 520);
    jetpack = polygon_createp(4, &(pt[30]));
    printf("drawing jets\n");
    polygon_drawFill(jetpack, src, vdkGrey);
    point_set2D(&(pt[34]), 200, 520);
    ellipse_set(&jets, pt[34], 25, 5);
    ellipse_drawFill(&jets, src, Red);
    point_set2D(&(pt[35]), 250, 520);
    ellipse_set(&jets, pt[35], 25, 5);
    ellipse_drawFill(&jets, src, Red);
    point_set2D(&(pt[36]), 300, 520);
    ellipse_set(&jets, pt[36], 25, 5);
    ellipse_drawFill(&jets, src, Red);
    point_set2D(&(pt[37]), 225, 530);
    ellipse_set(&jets, pt[37], 25, 5);
    ellipse_drawFill(&jets, src, dkRed);
    point_set2D(&(pt[38]), 275, 530);
    ellipse_set(&jets, pt[38], 25, 5);
    ellipse_drawFill(&jets, src, dkRed);
    
    // write out the image 
	image_write(src, "req1.ppm");

    // clear shapes from memory
    polygon_clear(body);
    polygon_clear(wings);
    polygon_clear(jetpack);

    // free image
    image_free(src);

	return(0);
}