/*
  Ian Tibbetts (Bruce A. Maxwell)
  Fall 2014

  Creative required 3D image
 */

#include "graphics.h"

/* draw a box
static int box( Image *src, Color color, int x, int y, int dx, int dy );
static int box( Image *src, Color color, int x, int y, int dx, int dy ) {
  Line l;
  
  line_set2D( &l, x, y, x, y+dy );
  line_draw( &l, src, color );

  line_set2D( &l, x, y+dy, x + dx, y+dy );
  line_draw( &l, src, color );

  line_set2D( &l, x+dx, y+dy, x+dx, y );
  line_draw( &l, src, color );

  line_set2D( &l, x+dx, y, x, y );
  line_draw( &l, src, color );
  printf("box drawn\n");
  return(0);
}*/

// draw a 3D object
int main(int argc, char *argv[]) {
	Image *src;
	Color White;
	Color Red;
	Point p;
	Ellipse e;
	Line line;

	color_set( &White, 1.0, 1.0, 1.0 );
	color_set( &Red, 0.9, 0.05, 0.05 );

	src = image_create( 400, 600 );

	// draw cylinder
	point_set2D( &p, 300, 100 );
	ellipse_set( &e, p, 60, 30 );
	ellipse_draw( &e, src, White );
	point_set2D( &p, 300, 300 );
	ellipse_set( &e, p, 60, 30 );
	ellipse_draw( &e, src, White );
	line_set2D( &line, 240, 100, 240, 300);
	line_draw( &line, src, White );
	line_set2D( &line, 360, 100, 360, 300);
	line_draw( &line, src, White );

	// draw snake wrapping around
	
	
	image_write( src, "threed.ppm" );

	image_free( src );

	return(0);
}
