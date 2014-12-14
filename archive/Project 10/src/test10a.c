/*
 * author: Astrid Moore + Ian Tibbetts 
 * Fall 2014
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
	Module *bee, *tree;
	Point start;
	Vector velocity, tempVelocity;
	Swarm *beeSwarm;
	BezierCurve antennae;
	Point bezPoints[4];
	View3D view;
	Matrix vtm, gtm;
	DrawState *ds;
	int i, frame;
	char buffer[256];
	float leaderSpeed = 2.0;
	int zoom, numFrames = 360;
	srand(time(NULL));

	// set up color palette
	Color Ambient = {{0.1, 0.1, 0.1}};
	Color White = {{1.0, 1.0, 1.0}};
	Color Black = {{0.0, 0.0, 0.0}};
	Color Brown = {{0.2, 0.2, 0.1}};
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

	// create the antennae
	point_set3D(&(bezPoints[0]), 0.0, 0.0, 0.0); 
	point_set3D(&(bezPoints[1]), 2.0, 0.0, 0.0); 
	point_set3D(&(bezPoints[2]), 4.0, 4.0, 0.0); 
	point_set3D(&(bezPoints[3]), 2.0, 2.0, 0.0);
	bezierCurve_init(&antennae);
	bezierCurve_set(&antennae, bezPoints);

	// create the bee
	bee = module_create();
	module_rotateY(bee, cos(M_PI/2.0), sin(M_PI/2.0));
	module_color(bee, &Black);
	module_translate(bee, 0.5, 0.0, 0.5);
	module_bezierCurve(bee, &antennae, 4);
	module_translate(bee, 0.0, 0.0, -1.0);
	module_bezierCurve(bee, &antennae, 4);
	module_bodyColor(bee, &yellow);
	module_scale(bee, 1, 4, 4);
	module_cube(bee, 1);
	module_bodyColor(bee, &Black);
	module_translate(bee, -1, 0, 0);
	module_cube(bee, 1);
	module_bodyColor(bee, &yellow);
	module_translate(bee, -1, 0, 0);
	module_cube(bee, 1);
	module_bodyColor(bee, &Black);
	module_translate(bee, -1, 0, 0);
	module_cube(bee, 1);
//	module_identity(bee);
//	module_scale(bee, 1, 4, 1);
//	module_rotateZ(bee, cos(M_PI/2.0), sin(M_PI/2.0));
//	module_translate(bee, -2, 0, 0);
//	module_cone(bee, 10, 1, 1, 0, 0, 0);

	// create the tree
	tree = module_create();
	module_bodyColor(tree, &Brown);
	module_scale(tree, 1, 40, 1);
	module_cylinder(tree, 10, 1, 5, 0, -50, 100);

	// create the swarm
	point_set3D(&start, -80, 0, 0);
	//point_set3D(&start, 0, 0, 0);
	vector_set(&velocity, leaderSpeed, 0, 0);
	beeSwarm = swarm_create(&start, &velocity, bee, 10, 10, 20);
	for(i=0; i<beeSwarm->numActors; i++){
		beeSwarm->actors[i].minDist = 7;
		beeSwarm->actors[i].thresholdDist = 15;
	}

	// animate the scene
	zoom = 1;
	for (frame=0; frame<numFrames; frame++){
		if(((frame+1) % (numFrames/4)) == 0){
			for(i=0; i<beeSwarm->numLeaders; i++){
				vector_cross(&(beeSwarm->leaders[i].velocity), &(view.vup), &tempVelocity);
				vector_copy(&(beeSwarm->leaders[i].velocity), &tempVelocity);
				//beeSwarm->leaders[i].velocity.val[0] *= -1;
				//beeSwarm->leaders[i].velocity.val[1] *= -1;
				//beeSwarm->leaders[i].velocity.val[2] *= -1;
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
		swarm_update( beeSwarm );
		swarm_draw( beeSwarm, &vtm, &gtm, ds, light, src );
		module_draw( tree, &vtm, &gtm, ds, light, src );

		// write out image
		sprintf(buffer, "test10a-frame%03d.ppm", frame);
		image_write(src, buffer);
		
		// reset image
		image_reset(src);
	}

	// convert to gif
	printf("converting to gif...\n");
	system("convert -delay 3 -loop 0 test10a-frame*.ppm test10a.gif");
	// remove ppm files
	printf("removing frames\n");
	system("rm test10a-frame*.ppm");
	
	// free drawstate, lighting, image, modules
	free(ds);
	free(light);
	image_free(src);
	swarm_free(beeSwarm);
	module_delete(tree);

	return(0);
}


