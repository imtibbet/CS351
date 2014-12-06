/*
Astrid Moore (Bruce Maxwell)
Fall 2014

Example of a 3D scene model

Draws a city with 3 different kinds of buildings
 */

#include "graphics.h"
#include <time.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
	// initialize fields
	const int rows = 500*2;
	const int cols = 550*2;
	Lighting *light;
	Image *src;
	int i;
	int numBuildings;
	Module *b[numBuildings];
	Module *city;
	Polygon p;
	View3D view;
	Matrix vtm, gtm;
	DrawState *ds;
	srand(time(NULL));
	char command[256];
	float alpha;

	Color Grey = {{0.5, 0.5, 0.5}};
	city = module_create();
// grab command line argument to determine viewpoint
    // and set up the view structure
    if( argc > 1 ) {
        alpha = atof( argv[1] );
        if( alpha < 0.0 || alpha > 1.0 )
            alpha = 0.0;
        point_set3D( &(view.vrp), 120*alpha, 80*alpha, -80*alpha - (1.0-cos(alpha)*80) );
    } else {
		point_set3D( &(view.vrp), 40, 0, -100 );
    }
	// set up the view
	vector_set( &(view.vpn), -view.vrp.val[0], -view.vrp.val[1], 
		-view.vrp.val[2] );
	vector_set( &(view.vup), 0, 1, 0 );
	view.d = 5;
	view.du = 6;
	view.f = 1;
	view.b = 200;
	view.screenx = cols;
	view.screeny = rows;

	printf("set up view\n");

	matrix_setView3D( &vtm, &view );
 	matrix_identity( &gtm );

 	numBuildings = 22;

 	// buildings
 	b[0] = module_create();
 	module_scale( b[0], 4, 20, 4);
 	module_translate( b[0], -60, 18, 20);
 	module_color(b[0], &Grey);
 	module_cube(b[0], 1);
 	b[1] = module_create();
 	module_scale( b[1], 7, 2, 3);
 	module_translate( b[1], -60, 0, -5);
 	module_color(b[1], &Grey);
 	module_cube(b[1], 1);
  	b[2] = module_create();
 	module_scale( b[2], 5, 15, 5);
 	module_translate( b[2], -60, 12.5, 20);
 	module_color( b[2], &Grey);
 	module_cube( b[2], 1 );

 	b[3] = module_create();
 	module_scale( b[3], 7, 10, 5);
 	module_translate( b[3], -40, 7.5, 5);
 	module_color(b[3], &Grey);
 	module_cube(b[3], 1);
 	b[4] = module_create();
 	module_scale( b[4], 5, 20, 7);
 	module_translate( b[4], -40, 16.5, 30);
 	module_color(b[4], &Grey);
 	module_cube(b[4], 1);

 	b[5] = module_create();
 	module_scale( b[5], 5, 25, 7);
 	module_translate( b[5], -20, 21, 15);
 	module_color(b[5], &Grey);
 	module_cube(b[5], 1); 
 	b[6] = module_create();
 	module_scale( b[6], 5, 20, 7);
 	module_translate( b[6], -20, 16, -5);
 	module_color(b[6], &Grey);
 	module_cube(b[6], 1);
 	b[7] = module_create();
 	module_scale( b[7], 5, 30, 7);
 	module_translate( b[7], -20, 26.5, 30);
 	module_color(b[7], &Grey);
 	module_cube(b[7], 1);

  	b[8] = module_create();
 	module_scale( b[8], 5, 30, 7);
 	module_translate( b[8], 0, 26.5, 15);
 	module_color(b[8], &Grey);
 	module_cube(b[8], 1);
 	b[9] = module_create();
 	module_scale( b[9], 2, 3, 2);
 	module_translate( b[9], 0, 0, -5);
 	module_color(b[9], &Grey);
 	module_cube(b[9], 1);
 	b[10] = module_create();
 	module_scale( b[10], 2, 3, 2);
 	module_translate( b[10], 0, 0, 0);
 	module_color(b[10], &Grey);
 	module_cube(b[10], 1);
 	b[11] = module_create();
 	module_scale( b[11], 4, 20, 4);
 	module_translate( b[11], 0, 18, 30);
 	module_color(b[11], &Grey);
 	module_cube(b[11], 1);

 	b[12] = module_create();
 	module_scale( b[12], 5, 15, 6);
 	module_translate( b[12], 20, 12, 30);
 	module_color(b[12], &Grey);
 	module_cube(b[12], 1);
 	b[13] = module_create();
 	module_scale( b[13], 5, 15, 5);
 	module_translate( b[13], 20, 12.5, 20);
 	module_color( b[13], &Grey);
 	module_cube( b[13], 1);
  	b[14] = module_create();
 	module_scale( b[14], 7, 2, 3);
 	module_translate( b[14], 20, 0, 10);
 	module_color(b[14], &Grey);
 	module_cube(b[14], 1);

 	b[15] = module_create();
 	module_scale( b[15], 7, 2, 3);
 	module_translate( b[15], 40, 0, 0);
 	module_color(b[15], &Grey);
 	module_cube(b[15], 1);
 	b[16] = module_create();
 	module_scale( b[16], 4, 5, 6);
 	module_translate( b[16], 40, 2, 10);
 	module_color(b[16], &Grey);
 	module_cube(b[16], 1);
 	b[17] = module_create();
 	module_scale( b[17], 7, 10, 5);
 	module_translate( b[17], 40, 7.5, 25);
 	module_color(b[17], &Grey);
 	module_cube(b[17], 1);

  	b[18] = module_create();
 	module_scale( b[18], 2, 5, 2);
 	module_translate( b[18], 60, 4, 30);
 	module_color(b[18], &Grey);
 	module_cube(b[18], 1);
 	b[19] = module_create();
 	module_scale( b[19], 8, 4, 3);
 	module_translate( b[19], 60, 2.5, 15);
 	module_color(b[19], &Grey);
 	module_cube(b[19], 1);

 	b[20] = module_create();
 	module_scale( b[20], 7, 2, 3);
 	module_translate( b[20], 70, 0, 0);
 	module_color(b[20], &Grey);
 	module_cube(b[20], 1);
 	b[21] = module_create();
 	module_scale( b[21], 7, 10, 5);
 	module_translate( b[21], 70, 7.5, 20);
 	module_color(b[21], &Grey);
 	module_cube(b[21], 1);

 	// organize into a city
 	for ( i = 0; i < numBuildings; i++){
 		module_module(city, b[i]);
	}

	// create the image and drawstate
	src = image_create( rows, cols );
	ds = drawstate_create();
	printf("created the image and drawstate\n");

	point_copy(&(ds->viewer), &(view.vrp));
	ds->shade = ShadeGouraud;

	light = lighting_create();
	light->light[0].type = LightPoint;
	light->light[0].position.val[0] = view.vrp.val[0];
	light->light[0].position.val[1] = view.vrp.val[1];
	light->light[0].position.val[2] = view.vrp.val[2];
	light->light[0].color.c[0] = 1;
	light->light[0].color.c[1] = 1;
	light->light[0].color.c[2] = 1;
	light->nLights = 1;

	// draw scene
	module_draw(city, &vtm, &gtm, ds, light, src );

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
	module_delete( city );
	printf("module freed\n");

	// free drawstate
	free(ds);
	printf("drawstate freed\n");

	// free image
	image_free( src );
	printf("image freed\n");

	return(0);
}


