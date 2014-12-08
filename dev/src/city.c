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
	Module *b;
	Module *city, *terrain;
	View3D view;
	Matrix vtm, gtm;
	DrawState *ds;
	srand(time(NULL));
	char command[256];
	float alpha;

	// set up color palette
	Color Grey = {{0.5, 0.5, 0.5}};
	Color ltGrey = {{0.7, 0.7, 0.7}};
	Color blueGrey = {{29/255.0, 30/255.0, 25/255.0}};
	Color brown =  {{72/255.0, 57/255.0, 42/255.0}};
	Color wBrown = {{50/255.0, 31/255.0, 12/255.0}};
	Color sandyBrown = {{87/255.0, 68/255.0, 44/255.0}};
	Color ltBrown = {{147/255.0, 106/255.0, 57/255.0}};

	city = module_create();
	terrain = module_create();

	// grab command line argument to determine viewpoint
    // and set up the view structure
    if( argc > 1 ) {
        alpha = atof( argv[1] );
        if( alpha < 0.0 || alpha > 1.0 )
            alpha = 0.0;
        point_set3D( &(view.vrp), 120*alpha, 80*alpha, -80*alpha - (1.0-cos(alpha)*80) );
    } else {
		point_set3D( &(view.vrp), 40, 0, -110 );
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

 	// buildings
 	b = module_create();
 	module_scale( b, 4, 20, 4);
 	module_translate( b, -60, 18, 15);
 	module_bodyColor(b, &Grey);
 	module_surfaceColor(b, &ltGrey);
 	module_cube(b, 1);
 	module_module(city, b);
 	b = module_create();
 	module_scale( b, 7, 2, 3);
 	module_translate( b, -60, 0, -5);
 	module_bodyColor(b, &Grey);
 	module_surfaceColor(b, &ltGrey);
 	module_cube(b, 1);
 	module_module(city, b);
  	b = module_create();
 	module_scale( b, 5, 15, 5);
 	module_translate( b, -60, 12.5, 30);
 	module_bodyColor(b, &Grey);
 	module_surfaceColor(b, &ltGrey);
 	module_cube( b, 1 );
 	module_module(city, b);

 	b = module_create();
 	module_scale( b, 7, 10, 5);
 	module_translate( b, -40, 7.5, 5);
 	module_bodyColor(b, &Grey);
 	module_surfaceColor(b, &ltGrey);
 	module_cube(b, 1);
 	module_module(city, b);
 	b = module_create();
 	module_scale( b, 5, 20, 7);
 	module_translate( b, -40, 16.5, 30);
 	module_bodyColor(b, &Grey);
 	module_surfaceColor(b, &ltGrey);
 	module_cube(b, 1);
 	module_module(city, b);

 	b = module_create();
 	module_scale( b, 5, 25, 7);
 	module_translate( b, -20, 21, 15);
 	module_bodyColor(b, &Grey);
 	module_surfaceColor(b, &ltGrey);
 	module_cube(b, 1); 
 	module_module(city, b);
 	b = module_create();
 	module_scale( b, 5, 20, 7);
 	module_translate( b, -20, 16, -5);
 	module_bodyColor(b, &Grey);
 	module_surfaceColor(b, &ltGrey);
 	module_cube(b, 1);
 	module_module(city, b);
 	b = module_create();
 	module_scale( b, 5, 30, 7);
 	module_translate( b, -20, 26.5, 30);
 	module_bodyColor(b, &Grey);
 	module_surfaceColor(b, &ltGrey);
 	module_cube(b, 1);
 	module_module(city, b);

  	b = module_create();
 	module_scale( b, 5, 30, 7);
 	module_translate( b, 0, 26.5, 15);
 	module_bodyColor(b, &Grey);
 	module_surfaceColor(b, &ltGrey);
 	module_cube(b, 1);
 	module_module(city, b);
 	b = module_create();
 	module_scale( b, 2, 3, 2);
 	module_translate( b, 0, 0, -7.5);
 	module_bodyColor(b, &Grey);
 	module_surfaceColor(b, &ltGrey);
 	module_cube(b, 1);
 	module_module(city, b);
 	b = module_create();
 	module_scale( b, 2, 3, 2);
 	module_translate( b, 0, 0, 0);
 	module_bodyColor(b, &Grey);
 	module_surfaceColor(b, &ltGrey);
 	module_cube(b, 1);
 	module_module(city, b);
 	b = module_create();
 	module_scale( b, 4, 20, 4);
 	module_translate( b, 0, 18, 30);
 	module_bodyColor(b, &Grey);
 	module_surfaceColor(b, &ltGrey);
 	module_cube(b, 1);
 	module_module(city, b);

 	b = module_create();
 	module_scale( b, 5, 15, 6);
 	module_translate( b, 20, 12, 30);
 	module_bodyColor(b, &Grey);
 	module_surfaceColor(b, &ltGrey);
 	module_cube(b, 1);
 	module_module(city, b);
 	b = module_create();
 	module_scale( b, 5, 15, 5);
 	module_translate( b, 20, 12.5, 15);
 	module_bodyColor(b, &Grey);
 	module_surfaceColor(b, &ltGrey);
 	module_cube( b, 1);
 	module_module(city, b);
  	b = module_create();
 	module_scale( b, 7, 2, 3);
 	module_translate( b, 20, 0, 0);
 	module_bodyColor(b, &Grey);
 	module_surfaceColor(b, &ltGrey);
 	module_cube(b, 1);
 	module_module(city, b);

 	b = module_create();
 	module_scale( b, 7, 2, 3);
 	module_translate( b, 40, 0, 0);
 	module_bodyColor(b, &Grey);
 	module_surfaceColor(b, &ltGrey);
 	module_cube(b, 1);
 	module_module(city, b);
 	b = module_create();
 	module_scale( b, 4, 5, 6);
 	module_translate( b, 40, 2, 15);
 	module_bodyColor(b, &Grey);
 	module_surfaceColor(b, &ltGrey);
 	module_cube(b, 1);
 	module_module(city, b);
 	b = module_create();
 	module_scale( b, 7, 10, 5);
 	module_translate( b, 40, 7.5, 30);
 	module_bodyColor(b, &Grey);
 	module_surfaceColor(b, &ltGrey);
 	module_cube(b, 1);
 	module_module(city, b);

  	b = module_create();
 	module_scale( b, 2, 5, 2);
 	module_translate( b, 60, 4, 30);
 	module_bodyColor(b, &Grey);
 	module_surfaceColor(b, &ltGrey);
 	module_cube(b, 1);
 	module_module(city, b);
 	b = module_create();
 	module_scale( b, 8, 4, 3);
 	module_translate( b, 60, 2.5, 10);
 	module_bodyColor(b, &Grey);
 	module_surfaceColor(b, &ltGrey);
 	module_cube(b, 1);
 	module_module(city, b);

 	b = module_create();
 	module_scale( b, 7, 2, 3);
 	module_translate( b, 70, 0, 0);
 	module_bodyColor(b, &Grey);
 	module_surfaceColor(b, &ltGrey);
 	module_cube(b, 1);
 	module_module(city, b);
 	b = module_create();
 	module_scale( b, 7, 10, 5);
 	module_translate( b, 70, 7.5, 20);
 	module_bodyColor(b, &Grey);
 	module_surfaceColor(b, &ltGrey);
 	module_cube(b, 1);
 	module_module(city, b);

 	// so our city isn't floating in space...
 	// keep ground matt for contrast by withholding surface color
 	b = module_create();
 	module_scale(b, 77, 1, 26);
 	module_translate(b, 0, -2.5, 13);
 	module_bodyColor(b, &blueGrey);
 	module_cube(b, 1);
 	module_module(terrain, b);
 	b = module_create();
 	module_scale(b, 77, 1.5, 26);
 	module_translate(b, 0, -6, 13);
 	module_bodyColor(b, &brown);
 	module_cube(b, 1);
 	module_module(terrain, b);
 	b = module_create();
 	module_scale(b, 77, 2, 26);
 	module_translate(b, 0, -10, 13);
 	module_bodyColor(b, &wBrown);
 	module_cube(b, 1);
 	module_module(terrain, b);
 	b = module_create();
 	module_scale(b, 77, 0.5, 26);
 	module_translate(b, 0, -13, 13);
 	module_bodyColor(b, &ltBrown);
 	module_cube(b, 1);
 	module_module(terrain, b);
 	b = module_create();
 	module_scale(b, 77, 1, 26);
 	module_translate(b, 0, -15, 13);
 	module_bodyColor(b, &sandyBrown);
 	module_cube(b, 1);
 	module_module(terrain, b);

	// create the image and drawstate
	src = image_create( rows, cols );
	ds = drawstate_create();
	printf("created the image and drawstate\n");

	// make sure the light source is the same as the viewer
	point_copy(&(ds->viewer), &(view.vrp));
	ds->shade = ShadeGouraud;

	// make two lights: point for contrast, ambient for general brightness
	light = lighting_create();
	light->light[0].type = LightPoint;
	light->light[1].type = LightAmbient;
	light->light[0].position.val[0] = view.vrp.val[0];
	light->light[0].position.val[1] = view.vrp.val[1];
	light->light[0].position.val[2] = view.vrp.val[2];
	light->light[1].position.val[0] = view.vrp.val[0];
	light->light[1].position.val[1] = view.vrp.val[1];
	light->light[1].position.val[2] = view.vrp.val[2];
	light->light[0].color.c[0] = 1;
	light->light[0].color.c[1] = 1;
	light->light[0].color.c[2] = 1;
	light->light[1].color.c[0] = 1;
	light->light[1].color.c[1] = 1;
	light->light[1].color.c[2] = 1;
	light->nLights = 2;

	// draw scene
	module_draw(terrain, &vtm, &gtm, ds, light, src);
	module_draw(city, &vtm, &gtm, ds, light, src );

	printf("drew the scene\n");

	// write out the scene
	printf("Writing image\n");
	image_write( src, "city.ppm" );
	sprintf(command, "convert -scale %03dx%03d city.ppm city.ppm", cols/2, rows/2);
	system(command);

	// free the modules
	module_delete( city );
	module_delete( terrain );
	printf("modules freed\n");

	// free drawstate
	free(ds);
	printf("drawstate freed\n");

	// free image
	image_free( src );
	printf("image freed\n");

	return(0);
}


