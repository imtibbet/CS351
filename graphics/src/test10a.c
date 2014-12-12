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
	const int rows = 500;
	const int cols = 560;
	Image *src;
	Lighting *light;
	Module *cube;
	Point start;
	Vector velocity;
	Swarm *cubeSwarm;
	View3D view;
	Matrix vtm, gtm;
	DrawState *ds;
	int frame;
	char command[256];
	char buffer[256];
	srand(time(NULL));

	// set up color palette
	Color Ambient = {{0.1, 0.1, 0.1}};
	Color White = {{1.0, 1.0, 1.0}};
	Color yellow = {{253/255.0, 127/255.0, 25/255.0}};

	cube = module_create();


	// create drawstate + image
	ds = drawstate_create();
	  light = lighting_create();
	ds->shade = ShadeGouraud;
	src = image_create( rows, cols );

	// set up the view
	point_set3D( &(view.vrp), 0, 42, -100);
	  lighting_add( light, LightAmbient, &Ambient, NULL, NULL, 0, 0 );
	  lighting_add( light, LightPoint, &White, NULL, &(view.vrp), 0, 0 );
		point_copy(&(ds->viewer), &(view.vrp));
	vector_set( &(view.vpn), -view.vrp.val[0], -view.vrp.val[1], -view.vrp.val[2] );
	vector_set( &(view.vup), 0, 1, 0 );
	view.d = 4;
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

	point_set3D(&start, -10, 0, 0);
	vector_set(&velocity, 0.5, 0, 0);
	cubeSwarm = swarm_create(&start, &velocity, cube, 2, 10, 10);

	for (frame=0; frame<60; frame++){
		
		// matrix_rotateY(&gtm, cos(M_PI/30.0), sin(M_PI/30.0) );
		// draw terrain
		swarm_update( cubeSwarm );
		swarm_draw( cubeSwarm, &vtm, &gtm, ds, light, src );

		// write out image
		sprintf(buffer, "test10a-frame%03d.ppm", frame);
		image_write(src, buffer);
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
	swarm_free(cubeSwarm);

	return(0);
}


