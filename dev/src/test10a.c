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
	Module *b;
	View3D view;
	Matrix vtm, gtm;
	DrawState *ds;
	Color blue, green, dkGrey;
	int frame;
	char command[256];
	color_set(&blue, 0, 0, 1);
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
	point_set3D( &(view.vrp), 0, 42, -120);
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

		point_copy(&(ds->viewer), &(view.vrp));
		light = lighting_create();
		light->light[0].type = LightPoint;
		light->light[1].type = LightAmbient;
		light->light[0].position.val[0] = 0;
		light->light[0].position.val[1] = 25;
		light->light[0].position.val[2] = 0;
		light->light[1].position.val[0] = 0;
		light->light[1].position.val[1] = 26;
		light->light[1].position.val[2] = 0;
		light->light[0].color.c[0] = 1;
		light->light[0].color.c[1] = 241/255.0;
		light->light[0].color.c[2] = 224/255.0;
		light->light[1].color.c[0] = 1;
		light->light[1].color.c[1] = 241/255.0;
		light->light[1].color.c[2] = 224/255.0;
		light->nLights = 2;
		
		

		char buffer[256];
		matrix_rotateY(&gtm, cos(M_PI/30.0), sin(M_PI/30.0) );
		// draw tower and flames
		module_draw( flames[frame], &vtm, &gtm, ds, light, src);


		// write out image
		sprintf(buffer, "tower-frame%03d.ppm", frame);
		image_write(src, buffer);
		sprintf(command, "convert -scale %03dx%03d tower-frame%03d.ppm tower-frame%03d.ppm", 
		cols/2, rows/2, frame, frame);
		system(command);
		// reset image
		image_reset(src);
	}

	// convert to gif
	printf("converting to gif...\n");
	system("convert -delay 5 -loop 0 tower-frame*.ppm tower.gif");
	printf("converted gif\n");
	// remove ppm files
	system("rm tower-frame*.ppm");
	printf("animating gif...\n");
	// animate gif
	system("animate tower.gif");

	// free drawstate, image, modules
	free(ds);
	image_free(src);
	module_delete(tower0);
	module_delete(tower1);
	module_delete(tower2);
	module_delete(tower3);
	module_delete(wall);

	for (frame = 0; frame < 60; frame++){
		module_delete(flames[frame]);
	}

	return(0);
}


