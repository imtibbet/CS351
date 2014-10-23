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
	Element *e;
	Point pt[4];
	Point v[8];
	Polygon p;
	Line l; 

	// initialize polygon
	polygon_init( &p );

	// corners of a cube, centered at (0, 0, 0)
	point_set3D( &v[0], -1, -1, -1 );
	point_set3D( &v[1],  1, -1, -1 );
	point_set3D( &v[2],  1,  1.5, -1 );
	point_set3D( &v[3], -1,  1.5, -1);
	point_set3D( &v[4], -1, -1,  1 );
	point_set3D( &v[5],  1, -1,  1 );
	point_set3D( &v[6],  1,  1,  1 );
	point_set3D( &v[7], -1,  1,  1 );

	// front side
	polygon_set( &p, 4, &(v[0]) );
	e = element_init(ObjPolygon, &p);
	module_insert(mod, e);

	// back side
	polygon_set( &p, 4, &(v[4]) );
	e = element_init(ObjPolygon, &p);
	module_insert(mod, e);

	// top side
	point_copy( &pt[0], &v[2] );
	point_copy( &pt[1], &v[3] );
	point_copy( &pt[2], &v[7] );
	point_copy( &pt[3], &v[6] );

	polygon_set( &p, 4, pt );
	e = element_init(ObjPolygon, &p);
	module_insert(mod, e);

	// bottom side
	point_copy( &pt[0], &v[0] );
	point_copy( &pt[1], &v[1] );
	point_copy( &pt[2], &v[5] );
	point_copy( &pt[3], &v[4] );

	polygon_set( &p, 4, pt );
	e = element_init(ObjPolygon, &p);
	module_insert(mod, e);

	// left side
	point_copy( &pt[0], &v[0] );
	point_copy( &pt[1], &v[3] );
	point_copy( &pt[2], &v[7] );
	point_copy( &pt[3], &v[4] );

	polygon_set( &p, 4, pt );
	e = element_init(ObjPolygon, &p);
	module_insert(mod, e);

	// right side
	point_copy( &pt[0], &v[1] );
	point_copy( &pt[1], &v[2] );
	point_copy( &pt[2], &v[6] );
	point_copy( &pt[3], &v[5] );

	polygon_set( &p, 4, pt );
	e = element_init(ObjPolygon, &p);
	module_insert(mod, e);
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
	view.d = 10;
	view.du = 1.6;
	view.dv = 0.9;
	view.f = 1;
	view.b = 50;
	view.screenx = 500;
	view.screeny = 500;

	printf("set up view\n");

	matrix_septiew3D( &vtm, &view );
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
	module_draw( b1, &vtm, &gtm, ds, 1, src );
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


