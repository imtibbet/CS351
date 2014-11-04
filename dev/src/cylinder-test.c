/*
Astrid Moore (Bruce Maxwell)
Fall 2014

Unit pyramid test.
 */

#include "graphics.h"
#include <time.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
	// initialize fields
	const int rows = 600*2;
	const int cols = 660*2;
	Image *src;
	Module *test;
	Polygon p;
	View3D view;
	Matrix vtm, gtm;
	DrawState *ds;
	char command[256];
	float alpha;
	Color blue, green, white, black;
	color_set(&blue, 0, 0, 1);
	color_set(&green, 0, 1, 0);
	color_set(&white, 1, 1, 1);
	color_set(&black, 0, 0, 0);

	test = module_create();

	// grab command line argument to determine viewpoint
    // and set up the view structure
    if( argc > 1 ) {
        alpha = atof( argv[1] );
        if( alpha < 0.0 || alpha > 1.0 )
            alpha = 0.0;
        point_set3D( &(view.vrp), 40*alpha, 40*alpha, -20*alpha - (alpha*20-cos(alpha)*20) );
    } else {
		point_set3D( &(view.vrp), -80, 60, -40);
    }

	// set up the view
	vector_set( &(view.vpn), -view.vrp.val[0], -view.vrp.val[1], -view.vrp.val[2] );
	vector_set( &(view.vup), 0, 1, 0 );
	view.d = 8;
	view.du = 6;
	view.f = 1;
	view.b = 50;
	view.screenx = cols;
	view.screeny = rows;

	printf("set up view\n");

	matrix_setView3D( &vtm, &view );
 	matrix_identity( &gtm );

	module_cylinder(test, 10, 6, 0, 0, 0, blue);


	// create the image and drawstate
	src = image_create( rows, cols );
	image_fillColor(src, black);
	ds = drawstate_create();
	ds->shade = ShadeConstant;
	printf("created the image and drawstate\n");

	// draw scene
	module_draw(test, &vtm, &gtm, ds, NULL, src);

	printf("drew the scene\n");

	// write out the scene
	printf("Writing image\n");
	image_write( src, "cylinder.ppm" );
	sprintf(command, "convert -scale %03dx%03d cylinder.ppm cylinder.ppm", cols/2, rows/2);
	system(command);

	// free the polygon data
	polygon_clear( &p );
	printf("polygon freed\n");

	// free the modules
	module_delete(test);

	printf("module freed\n");

	// free drawstate
	free(ds);
	printf("drawstate freed\n");

	// free image
	image_free( src );
	printf("image freed\n");

	return(0);
}


