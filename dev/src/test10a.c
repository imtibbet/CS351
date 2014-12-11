/*
 * author: Astrid Moore + Ian Tibbetts 
 * date: 12/11/12
 *
 * Test of the swarm's behaviors.
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
	Module *b, *terrain, *cube;
	Point start;
	Vector velocity;
	Swarm *cubeSwarm;
	View3D view;
	Matrix vtm, gtm;
	DrawState *ds;
	int frame;
	char command[256];
	srand(time(NULL));

	// set up color palette
	Color Grey = {{0.5, 0.5, 0.5}};
	Color ltGrey = {{0.7, 0.7, 0.7}};
	Color blueGrey = {{29/255.0, 30/255.0, 25/255.0}};
	Color brown =  {{72/255.0, 57/255.0, 42/255.0}};
	Color wBrown = {{50/255.0, 31/255.0, 12/255.0}};
	Color sandyBrown = {{87/255.0, 68/255.0, 44/255.0}};
	Color ltBrown = {{147/255.0, 106/255.0, 57/255.0}};
	Color yellow = {{253/255.0, 127/255.0, 25/255.0}};

	terrain = module_create();
	cube = module_create();

	point_set3D(&start, 200, 0, 0);
	vector_set(&velocity, 0.5, 0, 0);

	// create drawstate + image
	ds = drawstate_create();
	ds->shade = ShadeGouraud;
	src = image_create( rows, cols );

	// set up the view
	point_set3D( &(view.vrp), 0, 42, -100);
	vector_set( &(view.vpn), -view.vrp.val[0], -view.vrp.val[1], -view.vrp.val[2] );
	vector_set( &(view.vup), 0, 1, 0 );
	view.d = 6;
	view.du = 6;
	view.f = 1;
	view.b = 200;
	view.screenx = cols;
	view.screeny = rows;

	matrix_setView3D( &vtm, &view );
	matrix_identity( &gtm );

	module_bodyColor(cube, &yellow);
	module_scale(cube, 2, 2, 2);
	module_cube(cube, 1);

	cubeSwarm = swarm_create(&start, &velocity, cube, 4, 5, 10);

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
		light->light[0].color.c[1] = 1;
		light->light[0].color.c[2] = 1;
		light->light[1].color.c[0] = 1;
		light->light[1].color.c[1] = 1;
		light->light[1].color.c[2] = 1;
		light->nLights = 2;
		
		char buffer[256];
		// matrix_rotateY(&gtm, cos(M_PI/30.0), sin(M_PI/30.0) );
		// draw terrain
		module_draw( terrain, &vtm, &gtm, ds, light, src );
		swarm_update( cubeSwarm );
		swarm_draw( cubeSwarm, &vtm, &gtm, ds, light, src );

		// write out image
		sprintf(buffer, "test10a-frame%03d.ppm", frame);
		image_write(src, buffer);
		sprintf(command, "convert -scale %03dx%03d test10a-frame%03d.ppm test10a-frame%03d.ppm", 
		cols/2, rows/2, frame, frame);
		system(command);
		// reset image
		image_reset(src);
	}

	// convert to gif
	printf("converting to gif...\n");
	system("convert -delay 3 -loop 0 test10a-frame*.ppm test10a.gif");
	printf("converted gif\n");
	// remove ppm files
	system("rm test10a-frame*.ppm");
	printf("animating gif...\n");
	// animate gif
	system("animate test10a.gif");

	// free drawstate, image, modules
	free(ds);
	image_free(src);
	module_delete(b);
	module_delete(terrain);
	swarm_free(cubeSwarm);

	return(0);
}


