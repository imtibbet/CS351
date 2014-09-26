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
	Polyline back;
    Polyline cab;
    Polyline side;
    Polyline front;
    Polyline hood;
    Polyline grill;
    Line a;
    
    Ellipse wheel1;
    Circle wheel2;
    
	Image *src;
	Point p[nPoints];
	Color grey;
    Color white;
    Color dark_grey;
    Color light_grey;
    Color bright_r;
    Color mid_r;
    Color dark_r;
	int rows = 500;
	int cols = 600;

	// create an image
	src = image_create(rows, cols);
    
	// set up color palette
	color_set(&grey, 0.38, 0.39, 0.4);
    color_set(&light_grey, 0.5, 0.5, 0.5);
    color_set(&bright_r, 0.86, 0.0, 0.07);
    color_set(&dark_r, 0.43, 0.04, 0.004);
    color_set(&dark_grey, 0.3, 0.3, 0.3);
    color_set(&mid_r, 0.7, 0.04, 0.05);
    color_set(&white, 1.0, 1.0, 1.0);
    
    //first wheel
    point_set2D(&p[32], 90, 360);
    ellipse_set(&wheel1, p[32], 34, 29);
    ellipse_drawFill(&wheel1, src, grey);
    point_set2D(&p[33], 94, 360);
    circle_set(&wheel2, p[33], 29);
    circle_drawFill(&wheel2, src, dark_grey);
    
    point_set2D(&p[36], 94, 360);
    circle_set(&wheel2, p[36], 29);
    circle_draw(&wheel2, src, light_grey);

    // draw the side of the truck
	point_set2D(&p[0], 300, 260);
	point_set2D(&p[1], 300, 350);
	point_set2D(&p[2], 500, 315);
	point_set2D(&p[3], 500, 230);
	point_set2D(&p[4], 300, 260);

	//set up polyline
	polyline_init(&side);
	polyline_set(&side, 5, &(p[0]));
	polyline_draw(&side, src, white);
    floodfill(src, bright_r, white, 350, 270);
    
// draw the back of the truck
    point_set2D(&p[5], 500, 230);
    point_set2D(&p[6], 350, 230);
    point_set2D(&p[7], 300, 240);
    
    //set up polyline
    polyline_init(&back);
    polyline_set(&back, 3, &(p[5]));
    polyline_draw(&back, src, white);
    floodfill(src, dark_r, white, 400, 240);

// draw the cab of the truck
    point_set2D(&p[8], 300, 260);
    point_set2D(&p[9], 300, 200);
    point_set2D(&p[10], 160, 200);
    point_set2D(&p[11], 120, 220);
    point_set2D(&p[12], 260, 220);
    point_set2D(&p[13], 300, 200);

    //set up polyline
    polyline_init(&cab);
    polyline_set(&cab, 6, &(p[8]));
    polyline_draw(&cab, src, white);
    floodfill(src, dark_r, white, 240, 215);
    
// draw the front of the truck
    point_set2D(&p[14], 260, 220);
    point_set2D(&p[15], 240, 290);
    point_set2D(&p[16], 100, 290);
    point_set2D(&p[17], 120, 220);
    
    //set up polyline
    polyline_init(&front);
    polyline_set(&front, 4, &(p[14]));
    polyline_draw(&front, src, white);
    //    floodfill(src, dark_r, white, 300, 240);
    
// draw the hood of the truck
    point_set2D(&p[18], 100, 290);
    point_set2D(&p[19], 40, 310);
    point_set2D(&p[20], 190, 310);
    point_set2D(&p[21], 240, 290);
    
    //set up polyline
    polyline_init(&hood);
    polyline_set(&hood, 4, &(p[18]));
    polyline_draw(&hood, src, white);
    floodfill(src, dark_r, white, 140, 300);
    
    
// draw the grill of the truck
    point_set2D(&p[22], 40, 310);
    point_set2D(&p[23], 40, 370);
    point_set2D(&p[24], 190, 370);
    point_set2D(&p[25], 190, 310);
    
    //set up polyline
    polyline_init(&grill);
    polyline_set(&grill, 4, &(p[22]));
    polyline_draw(&grill, src, white);
    floodfill(src, mid_r, white, 100, 340);
    
// connecting line
    point_set2D(&p[26], 190, 370);
    point_set2D(&p[27], 300, 350);
    
    //set up line
    line_set(&a, p[26], p[27]);
    line_draw(&a, src, white);
    
    floodfill(src, bright_r, white, 240, 360);
    
    
//draw wheels
    point_set2D(&p[30], 450, 330);
    ellipse_set(&wheel1, p[30], 34, 29);
    ellipse_drawFill(&wheel1, src, grey);
    point_set2D(&p[34], 454, 330);
    circle_set(&wheel2, p[34], 29);
    circle_drawFill(&wheel2, src, dark_grey);
    point_set2D(&p[37], 454, 330);
    circle_set(&wheel2, p[37], 29);
    circle_draw(&wheel2, src, light_grey);
    
    point_set2D(&p[31], 250, 365);
    ellipse_set(&wheel1, p[31], 34, 29);
    ellipse_drawFill(&wheel1, src, grey);
    point_set2D(&p[35], 254, 365);
    circle_set(&wheel2, p[35], 29);
    circle_drawFill(&wheel2, src, dark_grey);
    point_set2D(&p[38], 254, 365);
    circle_set(&wheel2, p[38], 29);
    circle_draw(&wheel2, src, light_grey);
    
	image_write(src, "test3A.ppm");

	polyline_clear(&back);
    polyline_clear(&side);
    polyline_clear(&cab);
    polyline_clear(&hood);
    
    image_free(src);

	return(0);
}