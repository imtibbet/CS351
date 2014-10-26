/*
Astrid Moore (Bruce Maxwell)
Fall 2014

Example of a 3D scene model

Draws a city with 3 different kinds of buildings
 */

#include "graphics.h"
#include <time.h>
#include <stdlib.h>

/*
Adds to the module a unit rectangle, aligned about the y-axis.
Takes in parameters for width, height, depth when creating rectangle.
Code based off of Bruce's cube function in test6b.c
*/
void building( Module *mod );
void building( Module *mod ){
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
	const int rows = 500*2;
	const int cols = 550*2;
	Image *src;
	int i;
	Module *b[20];
	Module *city;
	Polygon p;
	Point pt[4];
	View3D view;
	Matrix vtm, gtm;
	DrawState *ds;
	Color Flame = { { 1.0, 0.7, 0.2 } };
	Color Red =  { { 1.0, 0.2, 0.1 } };
	Color Blue = { { 0.0, 0.0, 1.0 } };
	Color Green = {{0.0, 1.0, 0.0}};
	float bodyWidth = 2.0;
	srand(time(NULL));
	char command[256];
	float alpha;


// grab command line argument to determine viewpoint
    // and set up the view structure
    if( argc > 1 ) {
        alpha = atof( argv[1] );
        if( alpha < 0.0 || alpha > 1.0 )
            alpha = 0.0;
        point_set3D( &(view.vrp), 15*alpha, 30*alpha, 100*alpha - (1.0-alpha)*3 );
    } else {
		point_set3D( &(view.vrp), 0, 0, 100 );
    }
	// set up the view
	vector_set( &(view.vpn), -view.vrp.val[0], -view.vrp.val[1], 
		-view.vrp.val[2] );
	vector_set( &(view.vup), 0, 1, 0 );
	view.d = 1;
	view.du = 1.6;
	view.dv = view.du * (float)rows/cols;
	view.f = 1;
	view.b = 50;
	view.screenx = cols;
	view.screeny = rows;
	int r;

	printf("set up view\n");

	matrix_setView3D( &vtm, &view );
 	matrix_identity( &gtm );

 	// buildings
 	b[0] = module_create();
 	module_scale( b[0], 5, 5, 15);
 	module_rotateX( b[0], 0, 1);
 	module_translate( b[0], 0, 0, 0);
 	module_color( b[0], &Flame);
 	building( b[0] );
 	b[1] = module_create();
 	module_scale( b[1], 5, 7, 20);
 	module_rotateX( b[1], 0, 1);
 	module_translate( b[1], -12, 0, 0);
 	module_color(b[1], &Red);
 	building(b[1]);
 	b[2] = module_create();
 	module_scale( b[2], 8, 3, 4);
 	module_rotateX( b[2], 0, 1);
 	module_translate( b[2], 15, 10, 53);
 	module_color(b[2], &Blue);
 	building(b[2]);
 	b[3] = module_create();
 	module_scale( b[3], 2, 2, 3);
 	module_rotateX( b[3], 0, 1);
 	module_translate( b[3], -5, 0, 40);
 	module_color(b[3], &Green);
 	building(b[3]);
 	b[4] = module_create();
 	module_scale( b[4], 2, 2, 3);
 	module_rotateX( b[4], 0, 1);
 	module_translate( b[4], -5, 0, 27);
 	module_color(b[4], &Green);
 	building(b[4]);
 	b[5] = module_create();
 	module_scale( b[5], 5, 7, 30);
 	module_rotateX( b[5], 0, 1);
 	module_translate( b[5], -10, 0, 0);
 	module_color(b[5], &Flame);
 	building(b[5]);
 	b[6] = module_create();
 	module_scale( b[6], 4, 4, 20);
 	module_rotateX( b[6], 0, 1);
 	module_translate( b[6], -40, 0, 0);
 	module_color(b[6], &Flame);
 	building(b[6]);
 	b[7] = module_create();
 	module_scale( b[7], 7, 3, 2);
 	module_rotateX( b[7], 0, 1);
 	module_translate( b[7], -40, 0, 40);
 	module_color(b[7], &Green);
 	building(b[7]);
 	b[8] = module_create();
 	module_scale( b[8], 5, 7, 27);
 	module_rotateX( b[8], 0, 1);
 	module_translate( b[8], -30, 0, -20);
 	module_color(b[8], &Blue);
 	building(b[8]);
 	b[9] = module_create();
 	module_scale( b[9], 7, 5, 10);
 	module_rotateX( b[9], 0, 1);
 	module_translate( b[9], -25, 0, 30);
 	module_color(b[9], &Red);
 	building(b[9]);
 	b[10] = module_create();
 	module_scale( b[10], 4, 6, 3);
 	module_rotateX( b[10], 0, 1);
 	module_translate( b[10], 10, 0, 50);
 	module_color(b[10], &Red);
 	building(b[10]);
	b[11] = module_create();
 	module_scale( b[11], 5, 7, 20);
 	module_rotateX( b[11], 0, 1);
 	module_translate( b[11], -20, 0, 50);
 	module_color(b[11], &Blue);
 	building(b[11]);
 	b[12] = module_create();
 	module_scale( b[12], 7, 3, 2);
 	module_rotateX( b[12], 0, 1);
 	module_translate( b[12], 22, 0, 50);
 	module_color(b[12], &Green);
 	building(b[12]);
 	b[13] = module_create();
 	module_scale( b[13], 7, 3, 2);
 	module_rotateX( b[13], 0, 1);
 	module_translate( b[13], 5, 0, 70);
 	module_color(b[13], &Green);
 	building(b[13]);
 	b[14] = module_create();
 	module_scale( b[14], 7, 5, 10);
 	module_rotateX( b[14], 0, 1);
 	module_translate( b[14], 22, 0, 50);
 	module_color(b[14], &Red);
 	building(b[14]);
 	b[15] = module_create();
 	module_scale( b[15], 5, 5, 15);
 	module_rotateX( b[15], 0, 1);
 	module_translate( b[15], -27.5, 0, 35);
 	module_color( b[15], &Flame);
 	building( b[15] );
 	b[16] = module_create();
 	module_scale( b[16], 5, 6, 15);
 	module_rotateX( b[16], 0, 1);
 	module_translate( b[16], -5, 0, 37.5);
 	module_color(b[16], &Green);
 	building(b[16]);
 	b[17] = module_create();
 	module_scale( b[17], 2, 2, 5);
 	module_rotateX( b[17], 0, 1);
 	module_translate( b[17], 12.5, 0, 55);
 	module_color(b[17], &Flame);
 	building(b[17]);
 	b[18] = module_create();
 	module_scale( b[18], 5, 7, 30);
 	module_rotateX( b[18], 0, 1);
 	module_translate( b[18], -10, 0, 0);
 	module_color(b[18], &Blue);
 	building(b[18]);

	// create the image and drawstate
	src = image_create( rows, cols );
	ds = drawstate_create();
	ds->shade = ShadeFrame;
	printf("created the image and drawstate\n");

	// draw scene
	for ( i = 0; i < 19; i++){
		module_draw( b[i], &vtm, &gtm, ds, NULL, src );
	}
	printf("drew the scene\n");

	// write out the scene
	printf("Writing image\n");
	image_write( src, "city.ppm" );
	sprintf(command, "convert -scale %03dx%03d city.ppm city.ppm", cols/2, rows/2);
	system(command);

	// free the polygon data
	polygon_clear( &p );
	printf("polygon freed\n");

	// free the modules
	for ( i = 0; i < 19; i++){
		module_delete( b[i] );
	}

	printf("module freed\n");

	// free drawstate
	free(ds);
	printf("drawstate freed\n");

	// free image
	image_free( src );
	printf("image freed\n");

	return(0);
}


