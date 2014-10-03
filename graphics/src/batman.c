/*
  Ian Tibbetts (Bruce A. Maxwell)
  Fall 2014

  Creative required 3D image
 */

#include "graphics.h"

static Polygon *defineBatSymbol( Polygon *symPoints, int x, int y, float scale );
static int defineBatSymbol( Polygon *symPoints, int x, int y, float scale ){
	point_set2D( &(symPts[0]), x+0, y+2.5*scale );
}

// draw bat symbol
int main(int argc, char *argv[]) {
	Image src;
	Color Grey;
	Color Brown;
	Color Red;
	Color Green;
	Color Blue;
	Color Black;
	Color Yellow;
	Point p;
	Point symPoints[20];
	Ellipse e;
	int i;
	
	color_set( &Grey, 0.662745, 0.662745, 0.662745 );
	color_set( &Brown, 0.647059, 0.164706, 0.164706 );
	color_set( &Yellow, 0.9, 0.9, 0.4 );
	color_set( &Green, 0.2, 0.6, 0.2 );
	color_set( &Black, 0.0, 0.0, 0.0 );
	color_set( &Blue, 0.05, 0.05, 0.9 );
	color_set( &Red, 0.9, 0.05, 0.05 );

	image_init( &src );
	image_alloc( &src, 400, 600 );
	image_fillColor( &src, Grey );
	
	//draw frame
	point_set2D( &p, 300, 200 );
	ellipse_set( &e, p, 100, 50 );
	ellipse_drawFill( &e, &src, Yellow );
	ellipse_draw( &e, &src, Black );
	
	// define symbol vetrices
	
	
	for(i=-1
	image_write( &src, "batman.ppm" );
	image_dealloc( &src );
	return(0);
}
