/*
  Ian Tibbetts (Bruce A. Maxwell)
  Fall 2014

  Creative required 3D image
 */

#include "graphics.h"

static void defineBatSymbol( Point *symPoints, int x, int y, float scale );
static void defineBatSymbol( Point *symPoints, int x, int y, float scale ){
	point_set2D( &(symPoints[0]), x+0*scale, y+2.5*scale );
	point_set2D( &(symPoints[1]), x+1*scale, y+1.5*scale );
	point_set2D( &(symPoints[2]), x+2*scale, y+2.3*scale );
	point_set2D( &(symPoints[3]), x+3*scale, y+1.3*scale );
	point_set2D( &(symPoints[4]), x+4*scale, y+2.4*scale );
	point_set2D( &(symPoints[5]), x+7*scale, y+0*scale );
	point_set2D( &(symPoints[6]), x+3*scale, y-2.6*scale );
	point_set2D( &(symPoints[7]), x+2*scale, y-1*scale );
	point_set2D( &(symPoints[8]), x+1*scale, y-1*scale );
	point_set2D( &(symPoints[9]), x+0.8*scale, y-3*scale );
	point_set2D( &(symPoints[10]), x+0.6*scale, y-2.2*scale );

	point_set2D( &(symPoints[20]), x-1*scale, y+1.5*scale );
	point_set2D( &(symPoints[19]), x-2*scale, y+2.3*scale );
	point_set2D( &(symPoints[18]), x-3*scale, y+1.3*scale );
	point_set2D( &(symPoints[17]), x-4*scale, y+2.4*scale );
	point_set2D( &(symPoints[16]), x-7*scale, y+0*scale );
	point_set2D( &(symPoints[15]), x-3*scale, y-2.6*scale );
	point_set2D( &(symPoints[14]), x-2*scale, y-1*scale );
	point_set2D( &(symPoints[13]), x-1*scale, y-1*scale );
	point_set2D( &(symPoints[12]), x-0.8*scale, y-3*scale );
	point_set2D( &(symPoints[11]), x-0.6*scale, y-2.2*scale );
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
	Point symPoints[21];
	Polygon batSymbol;
	Ellipse e;
	
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
	ellipse_set( &e, p, 200, 100 );
	ellipse_drawFill( &e, &src, Yellow );
	ellipse_draw( &e, &src, Black );
	
	// define symbol vetrices
	defineBatSymbol(&(symPoints[0]), 300, 200, 20.0);
	polygon_init(&batSymbol);
	polygon_set(&batSymbol, 21, &(symPoints[0]));
	polygon_drawFill(&batSymbol, &src, Black);
	polygon_clear(&batSymbol);
	image_write( &src, "batman.ppm" );
	image_dealloc( &src );
	return(0);
}
