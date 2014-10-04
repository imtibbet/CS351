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
	Color Orange;
	Point p;
	Point points[21];
	Polygon poly;
	Ellipse e;
	
	color_set( &Grey, 0.662745, 0.662745, 0.662745 );
	color_set( &Brown, 0.647059, 0.164706, 0.164706 );
	color_set( &Orange, 1, 0.647059, 0 );
	color_set( &Green, 0.2, 0.6, 0.2 );
	color_set( &Black, 0.0, 0.0, 0.0 );
	color_set( &Blue, 0.529412, 0.807843, 0.980392 );
	color_set( &Red, 0.9, 0.05, 0.05 );

	image_init( &src );
	image_alloc( &src, 400, 600 );
	image_fillColor( &src, Blue );

	polygon_init(&poly);
	point_set2D( &(points[0]), 0, 260 );
	point_set2D( &(points[1]), 599, 260 );
	point_set2D( &(points[2]), 599, 399 );
	point_set2D( &(points[3]), 0, 399 );
	polygon_set(&poly, 4, &(points[0]));
	polygon_drawFill(&poly, &src, Brown);
	
	//draw left pumpkin
	point_set2D( &p, 150, 200 );
	ellipse_set( &e, p, 100, 90 );
	ellipse_drawFill( &e, &src, Orange );
	ellipse_draw( &e, &src, Black );
	ellipse_set( &e, p, 60, 90 );
	ellipse_drawquad( &e, &src, Black, 1, 1 );
	ellipse_drawquad( &e, &src, Black, 4, 4 );
	ellipse_set( &e, p, 60, 90 );
	ellipse_drawquad( &e, &src, Black, 2, 3 );
	ellipse_set( &e, p, 20, 90 );
	ellipse_drawquad( &e, &src, Black, 1, 1 );
	ellipse_drawquad( &e, &src, Black, 4, 4 );
	ellipse_set( &e, p, 20, 90 );
	ellipse_drawquad( &e, &src, Black, 2, 3 );

	// draw right pumpkin
	point_set2D( &p, 450, 200 );
	ellipse_set( &e, p, 100, 90 );
	ellipse_drawFill( &e, &src, Orange );
	ellipse_draw( &e, &src, Black );
	ellipse_set( &e, p, 60, 90 );
	ellipse_drawquad( &e, &src, Black, 1, 1 );
	ellipse_drawquad( &e, &src, Black, 4, 4 );
	ellipse_set( &e, p, 60, 90 );
	ellipse_drawquad( &e, &src, Black, 2, 3 );
	ellipse_set( &e, p, 20, 90 );
	ellipse_drawquad( &e, &src, Black, 1, 1 );
	ellipse_drawquad( &e, &src, Black, 4, 4 );
	ellipse_set( &e, p, 20, 90 );
	ellipse_drawquad( &e, &src, Black, 2, 3 );

	// left mouth
	defineBatSymbol(&(points[0]), 150, 230, 10.0);
	polygon_set(&poly, 21, &(points[0]));
	polygon_drawFill(&poly, &src, Black);

	// left stem
	point_set2D( &(points[0]), 150, 110 );
	point_set2D( &(points[1]), 160, 90 );
	point_set2D( &(points[2]), 130, 80 );
	polygon_set(&poly, 3, &(points[0]));
	polygon_drawFillB(&poly, &src, Green);

	// left nose
	point_set2D( &(points[0]), 150, 200 );
	point_set2D( &(points[1]), 130, 180 );
	point_set2D( &(points[2]), 170, 180 );
	polygon_set(&poly, 3, &(points[0]));
	polygon_drawFillB(&poly, &src, Black);

	// left eyes
	point_set2D( &(points[0]), 100, 150 );
	point_set2D( &(points[1]), 80, 170 );
	point_set2D( &(points[2]), 120, 170 );
	polygon_set(&poly, 3, &(points[0]));
	polygon_drawFillB(&poly, &src, Black);
	point_set2D( &(points[0]), 200, 150 );
	point_set2D( &(points[1]), 180, 170 );
	point_set2D( &(points[2]), 220, 170 );
	polygon_set(&poly, 3, &(points[0]));
	polygon_drawFillB(&poly, &src, Black);

	// right mouth
	defineBatSymbol(&(points[0]), 450, 240, -10.0);
	polygon_set(&poly, 21, &(points[0]));
	polygon_drawFill(&poly, &src, Black);

	// right stem
	point_set2D( &(points[0]), 450, 110 );
	point_set2D( &(points[1]), 440, 90 );
	point_set2D( &(points[2]), 470, 80 );
	polygon_set(&poly, 3, &(points[0]));
	polygon_drawFillB(&poly, &src, Green);

	// right nose
	point_set2D( &(points[0]), 450, 210 );
	point_set2D( &(points[1]), 430, 190 );
	point_set2D( &(points[2]), 470, 190 );
	polygon_set(&poly, 3, &(points[0]));
	polygon_drawFillB(&poly, &src, Black);

	// right eyes
	point_set2D( &(points[0]), 400, 150 );
	point_set2D( &(points[1]), 380, 170 );
	point_set2D( &(points[2]), 420, 170 );
	polygon_set(&poly, 3, &(points[0]));
	polygon_drawFillB(&poly, &src, Black);
	point_set2D( &(points[0]), 500, 150 );
	point_set2D( &(points[1]), 480, 170 );
	point_set2D( &(points[2]), 520, 170 );
	polygon_set(&poly, 3, &(points[0]));
	polygon_drawFillB(&poly, &src, Black);

	polygon_clear(&poly);
	image_write( &src, "jackolantern.ppm" );
	image_dealloc( &src );
	return(0);
}
