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
	Module *beetle;
	Point start;
	Vector velocity, tempVelocity;
	Swarm *beetleSwarm;
	View3D view;
	Matrix vtm, gtm;
	DrawState *ds;
	int i, frame;
	char buffer[256];
	float leaderSpeed = 2.0;
	int zoom, numFrames = 720;
	srand(time(NULL));

	// set up color palette
	Color Ambient = {{0.1, 0.1, 0.1}};
	Color White = {{1.0, 1.0, 1.0}};
	Color Black = {{0.0, 0.0, 0.0}};
	Color Blue = {{0.2, 0.2, 0.6}};
	Color yellow = {{253/255.0, 127/255.0, 25/255.0}};

	// create drawstate, lighting and image
	ds = drawstate_create();
	light = lighting_create();
	ds->shade = ShadeGouraud;
	src = image_create( rows, cols );

	// set up the view
	vector_set( &(view.vup), 0, 1, 0 );
	view.d = 6;
	view.du = 6;
	view.f = 1;
	view.b = 2000;
	view.screenx = cols;
	view.screeny = rows;
	matrix_identity( &gtm );

	// create the beetle
	beetle = module_create();
	module_bodyColor(beetle, &yellow);
	module_scale(beetle, 1, 4, 4);
	module_cube(beetle, 1);
	module_bodyColor(beetle, &Black);
	module_translate(beetle, 1, 0, 0);
	module_cube(beetle, 1);
	module_bodyColor(beetle, &yellow);
	module_translate(beetle, 1, 0, 0);
	module_cube(beetle, 1);
	module_bodyColor(beetle, &Black);
	module_translate(beetle, 1, 0, 0);
	module_cube(beetle, 1);

	// create the swarm
	point_set3D(&start, -80, 0, 0);
	vector_set(&velocity, leaderSpeed, 0, 0);
	beetleSwarm = swarm_create(&start, &velocity, beetle, 10, 10, 20);
	for(i=0; i<beetleSwarm->numActors; i++){
		beetleSwarm->actors[i].minDist = 7;
		beetleSwarm->actors[i].thresholdDist = 15;
	}

	// animate the scene
	zoom = 1;
	for (frame=0; frame<numFrames; frame++){
		if(((frame+1) % (numFrames/8)) == 0){
			for(i=0; i<beetleSwarm->numLeaders; i++){
				//vector_cross(&(beetleSwarm->leaders[i].velocity), &(view.vup), &tempVelocity);
				//vector_copy(&(beetleSwarm->leaders[i].velocity), &tempVelocity);
				beetleSwarm->leaders[i].velocity.val[0] *= -1;
				beetleSwarm->leaders[i].velocity.val[1] *= -1;
				beetleSwarm->leaders[i].velocity.val[2] *= -1;
			}
			zoom *= -1;
		}
		point_set3D( &(view.vrp), 0, 0, -120);
		vector_set( &(view.vpn), -view.vrp.val[0], -view.vrp.val[1], -view.vrp.val[2] );
		lighting_init(light);
		lighting_add( light, LightAmbient, &Ambient, NULL, NULL, 0, 0 );
		lighting_add( light, LightPoint, &White, NULL, &(view.vrp), 0, 0 );
		point_copy(&(ds->viewer), &(view.vrp));
		matrix_setView3D( &vtm, &view );
		image_fillColor(src, Blue);
		
		// draw swarm
		swarm_update( beetleSwarm );
		swarm_draw( beetleSwarm, &vtm, &gtm, ds, light, src );

		// write out image
		sprintf(buffer, "beetle-frame%03d.ppm", frame);
		image_write(src, buffer);
		
		// reset image
		image_reset(src);
	}

	// convert to gif
	printf("converting to gif...\n");
	system("convert -delay 3 -loop 0 beetle-frame*.ppm beetle-invasion.gif");
	printf("converted gif\n");
	// remove ppm files
	system("rm beetle-frame*.ppm");
	printf("animating gif...\n");
	// animate gif
	system("animate beetle-invasion.gif");

	// free drawstate, lighting, image, modules
	free(ds);
	free(light);
	image_free(src);
	swarm_free(beetleSwarm);

	return(0);
}


