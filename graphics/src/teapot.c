/*
Astrid Moore (Bruce Maxwell)
Fall 2014

Example of a 3D scene model

draws a castle
 */

#include "graphics.h"
#include <time.h>
#include <stdlib.h>

/* declare methods here for testing flexibility */
int main(int argc, char *argv[]) {
	// initialize fields
	const int rows = 500*2;
	const int cols = 560*2;
	Image *src;
	Lighting *light;
	Module *teapot;
	View3D view;
	Matrix vtm, gtm;
	DrawState *ds;
	Color blue, green, dkGrey;
	int frame;
	char command[256];
	color_set(&blue, 0, 0, .5);
	color_set(&green, 0, 1, 0);
	color_set(&dkGrey, (float)(98/255.0), (float)(106/255.0), 
		(float)(101/255.0));
	srand(time(NULL));

	// create drawstate + image
	ds = drawstate_create();
	ds->shade = ShadeGouraud;
	ds->surfaceCoeff = 5;
	src = image_create( rows, cols );

	// set up the view
	point_set3D( &(view.vrp), 0, 30, -40);
	vector_set( &(view.vpn), -view.vrp.val[0], -view.vrp.val[1], -view.vrp.val[2] );
	vector_set( &(view.vup), 0, 1, 0 );
	view.d = 8;
	view.du = 6;
	view.f = 1;
	view.b = 200;
	view.screenx = cols;
	view.screeny = rows;

	matrix_setView3D( &vtm, &view );
	matrix_identity( &gtm );

	for (frame=0; frame<60; frame++){
		teapot = module_create();
		module_scale(teapot, 2, 2, 2);
		module_bodyColor(teapot, &blue);
		module_teapot(teapot, 6, 1);
		module_module(set, teapot);

		point_copy(&(ds->viewer), &(view.vrp));
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

		char buffer[256];
		matrix_rotateY(&gtm, cos(M_PI/30.0), sin(M_PI/30.0) );
		module_draw(set, &vtm, &gtm, ds, light, src);

		// write out image
		sprintf(buffer, "teapot-frame%03d.ppm", frame);
		image_write(src, buffer);
		sprintf(command, "convert -scale %03dx%03d teapot-frame%03d.ppm teapot-frame%03d.ppm", 
		cols/2, rows/2, frame, frame);
		system(command);
		// reset image
		image_reset(src);
	}

	// convert to gif
	printf("converting to gif...\n");
	system("convert -delay 4 -loop 0 teapot-frame*.ppm teapot.gif");
	printf("converted gif\n");
	// remove ppm files
	system("rm teapot-frame*.ppm");
	printf("animating gif...\n");
	// animate gif
	system("animate teapot.gif");

	// free drawstate, image, modules
	free(ds);
	image_free(src);
	module_delete(teapot);

	return(0);
}


