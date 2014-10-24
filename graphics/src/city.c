/*
Astrid Moore (Bruce Maxwell)
Fall 2014

Example of a 3D scene model

Draws a city with 3 different kinds of buildings
 */

#include "graphics.h"

/*
Adds to the module a unit rectangle, aligned about the y-axis.
Takes in parameters for width, height, depth when creating rectangle.
Code based off of Bruce's cube function in test6b.c
*/
void building1( Module *mod );
void building1( Module *mod ){
	Point pt[4];
	Polygon p; 

	polygon_init( &p );
	point_set3D( &pt[0], -1, -1, -1 );
	point_set3D( &pt[1], -1, -1,  1 );
	point_set3D( &pt[2], -1,  1,  1 );
	point_set3D( &pt[3], -1,  1, -1 );
	polygon_set( &p, 4, pt );
	module_polygon( mod, &p );

	point_set3D( &pt[0], 1, -1, -1 );
	point_set3D( &pt[1], 1, -1,  1 );
	point_set3D( &pt[2], 1,  1,  1 );
	point_set3D( &pt[3], 1,  1, -1 );
	polygon_set( &p, 4, pt );
	module_polygon( mod, &p );

	point_set3D( &pt[0], -1, -1, -1 );
	point_set3D( &pt[1], -1, -1,  1 );
	point_set3D( &pt[2],  1, -1,  1 );
	point_set3D( &pt[3],  1, -1, -1 );
	polygon_set( &p, 4, pt );
	module_polygon( mod, &p );

	point_set3D( &pt[0], -1, 1, -1 );
	point_set3D( &pt[1], -1, 1,  1 );
	point_set3D( &pt[2],  1, 1,  1 );
	point_set3D( &pt[3],  1, 1, -1 );
	polygon_set( &p, 4, pt );
	module_polygon( mod, &p );

	point_set3D( &pt[0], -1, -1, -1 );
	point_set3D( &pt[1], -1,  1, -1 );
	point_set3D( &pt[2],  1,  1, -1 );
	point_set3D( &pt[3],  1, -1, -1 );
	polygon_set( &p, 4, pt );
	module_polygon( mod, &p );

	point_set3D( &pt[0], -1, -1, 1 );
	point_set3D( &pt[1], -1,  1, 1 );
	point_set3D( &pt[2],  1,  1, 1 );
	point_set3D( &pt[3],  1, -1, 1 );
	polygon_set( &p, 4, pt );
	module_polygon( mod, &p );
}

int main(int argc, char *argv[]) {
	// initialize fields
	Image *src;
	Module *b1, *b2, *b3;
	Module *city;
	Polygon p;
	Point pt[4];
	View3D view;
	Matrix vtm, gtm;
	DrawState *ds;
	Color Flame = { { 1.0, 0.7, 0.2 } };
	Color Red =  { { 1.0, 0.2, 0.1 } };
	float bodyWidth = 2.0;

	// set up the view
	point_set3D( &(view.vrp), 15, 30, 100 );
	vector_set( &(view.vpn), -20, -30, -100 );
	vector_set( &(view.vup), 0, 1, 0 );
	view.d = 2.2;
	view.du = 1.6;
	view.dv = 0.9;
	view.f = 1;
	view.b = 50;
	view.screenx = 640;
	view.screeny = 360;

	printf("set up view\n");

	matrix_setView3D( &vtm, &view );
 	matrix_identity( &gtm );

 	// building 1
 	b1 = module_create();
 	module_scale( b1, 5, 5, 5);
 	module_rotateX( b1, 0, 1);
 	module_color( b1, &Flame);
 	building1( b1 );
 	printf("made building1\n");

	// create the image and drawstate
	src = image_create( 500, 500 );
	ds = drawstate_create();
	ds->shade = ShadeFrame;
	printf("created the image and drawstate\n");

	// draw into the scene
	module_draw( b1, &vtm, &gtm, ds, NULL, src );
	printf("drew the scene\n");

	// write out the scene
	image_write( src, "city.ppm" );
	printf("wrote out the scene\n");

	// free the polygon data
	polygon_clear( &p );
	printf("polygon freed\n");

	// free the modules
	// module_delete( b1 );
	// printf("module freed\n");

	// free drawstate
	free(ds);
	printf("drawstate freed\n");

	// free image
	image_free( src );
	printf("image freed\n");

	return(0);
}


