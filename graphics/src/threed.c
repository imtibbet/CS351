/*
  Ian Tibbetts (Bruce A. Maxwell)
  Fall 2014

  Creative required 3D image
 */

#include "graphics.h"

// draw a flower
static int flower( Image *src, Color color, int x, int y, int x0, int y0 );
static int flower( Image *src, Color color, int x, int y, int x0, int y0 ) {
	Circle circ;
	Point p;
	Line line;
	
	point_set2D( &p, x, y );
	circle_set( &circ, p, 20 );
	circle_drawFill( &circ, src, color );
	
	point_set2D( &p, x-20, y-20 );
	circle_set( &circ, p, 30 );
	circle_drawoct( &circ, src, color, 4, 7 );
	point_set2D( &p, x-20, y+20 );
	circle_set( &circ, p, 30 );
	circle_drawoct( &circ, src, color, 2, 5 );
	
	point_set2D( &p, x+20, y-20 );
	circle_set( &circ, p, 30 );
	circle_drawoct( &circ, src, color, 6, 8 );
	point_set2D( &p, x+20, y-20 );
	circle_set( &circ, p, 30 );
	circle_drawoct( &circ, src, color, 1, 1 );
	point_set2D( &p, x+20, y+20 );
	circle_set( &circ, p, 30 );
	circle_drawoct( &circ, src, color, 8, 8 );
	point_set2D( &p, x+20, y+20 );
	circle_set( &circ, p, 30 );
	circle_drawoct( &circ, src, color, 1, 3 );
	
	line_set2D( &line, x0, y0, x, y+45 );
	line_draw( &line, src, color );
	return(0);
}

// draw a 3D object
int main(int argc, char *argv[]) {
	Image *src;
	Color White;
	Color Red;
	Point p;
	Ellipse e;
	int i;
	
	
	color_set( &White, 1.0, 1.0, 1.0 );
	color_set( &Red, 0.9, 0.05, 0.05 );

	src = image_create( 600, 400 );
	
	//draw cone
	for(i=1;i<=40;i++){
		point_set2D( &p, 200, 500-i*5 );
		ellipse_set( &e, p, 2+2*i, 1+1*i );
		ellipse_drawquad( &e, src, White, 1, 2 );
	}
	point_set2D( &p, 200, 500-40*5 );
	ellipse_set( &e, p, 2+2*40, 1+1*40 );
	ellipse_drawquad( &e, src, White, 1, 4 );
	
	// draw flower
	flower(src, White, 100, 200, 150, 300);
	flower(src, White, 200, 150, 200, 300);
	flower(src, White, 300, 200, 250, 300);
	
	image_write( src, "threed.ppm" );

	image_free( src );

	return(0);
}
