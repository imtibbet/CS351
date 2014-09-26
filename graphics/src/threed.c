/*
  Ian Tibbetts (Bruce A. Maxwell)
  Fall 2014

  Creative required 3D image
 */

#include "graphics.h"

// draw a flower
static int flower( Image *src, Color lineColor, Color pedalColor, Color centerColor, 
								int x, int y, int x0, int y0 );
static int flower( Image *src, Color lineColor, Color pedalColor, Color centerColor, 
								int x, int y, int x0, int y0 ) {
	Circle circ;
	Point p;
	Line line;
	
	point_set2D( &p, x, y );
	circle_set( &circ, p, 20 );
	circle_draw( &circ, src, lineColor );
	floodfill(src, centerColor, lineColor, x, y);
	
	point_set2D( &p, x-20, y-20 );
	circle_set( &circ, p, 30 );
	circle_drawoct( &circ, src, lineColor, 4, 7 );
	point_set2D( &p, x-20, y+20 );
	circle_set( &circ, p, 30 );
	circle_drawoct( &circ, src, lineColor, 2, 5 );
	
	point_set2D( &p, x+20, y-20 );
	circle_set( &circ, p, 30 );
	circle_drawoct( &circ, src, lineColor, 6, 8 );
	point_set2D( &p, x+20, y-20 );
	circle_set( &circ, p, 30 );
	circle_drawoct( &circ, src, lineColor, 1, 1 );
	point_set2D( &p, x+20, y+20 );
	circle_set( &circ, p, 30 );
	circle_drawoct( &circ, src, lineColor, 8, 8 );
	point_set2D( &p, x+20, y+20 );
	circle_set( &circ, p, 30 );
	circle_drawoct( &circ, src, lineColor, 1, 3 );
	
	floodfill(src, pedalColor, lineColor, x, y+35);
	
	line_set2D( &line, x0, y0, x, y+45 );
	line_draw( &line, src, lineColor );
	return(0);
}

// draw a 3D object
int main(int argc, char *argv[]) {
	Image *src;
	Color White;
	Color Red;
	Color Green;
	Color Blue;
	Color Black;
	Color Yellow;
	Point p;
	Ellipse e;
	int i;
	
	color_set( &White, 1.0, 1.0, 1.0 );
	color_set( &Red, 0.9, 0.05, 0.05 );
	color_set( &Yellow, 0.9, 0.9, 0.4 );
	color_set( &Green, 0.0, 1.0, 0.0 );
	color_set( &Black, 0.0, 0.0, 0.0 );
	color_set( &Blue, 0.0, 0.0, 1.0 );

	src = image_create( 600, 400 );
	
	//draw cone
	for(i=1;i<=40;i++){
		point_set2D( &p, 200, 500-i*5 );
		ellipse_set( &e, p, 2+2*i, 1+1*i );
		ellipse_drawquad( &e, src, White, 1, 2 );
	}
	for(i=1;i<=40;i+=2){
		floodfill(src, Red, White, 200, 500-i*4);
	}
	point_set2D( &p, 200, 500-40*5 );
	ellipse_set( &e, p, 2+2*40, 1+1*40 );
	ellipse_drawquad( &e, src, White, 1, 4 );
	
	// draw flowers
	flower(src, White, Yellow, Red, 100, 200, 150, 300);
	flower(src, White, Yellow, Red, 200, 150, 200, 300);
	flower(src, White, Yellow, Red, 300, 200, 250, 300);
	
	// color cone
	floodfill(src, Green, White, p.val[0], p.val[1]);
	
	image_write( src, "threed.ppm" );

	image_free( src );

	return(0);
}
