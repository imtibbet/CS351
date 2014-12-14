/*
 * author: Astrid Moore
 * Fall 2014
 *
 * Swarm behavior for a beetle invasion of Egypt.
 */

#include "graphics.h"
#include <time.h>
#include <stdlib.h>

/* declare methods here for testing flexibility */
/* declare methods here for testing flexibility */
static Module* city(int x, int y, int z);
static Module* city(int x, int y, int z){
  Module *b;
  Module *city;
  srand(time(NULL));

  Color Grey = {{0.5, 0.5, 0.5}};
  Color ltGrey = {{0.7, 0.7, 0.7}};
  city = module_create();

  // buildings
  b = module_create();
  module_scale( b, 4, 20, 4);
  module_translate( b, x-60, y+8, z+15);
  module_bodyColor(b, &Grey);
  module_surfaceColor(b, &ltGrey);
  module_cube(b, 1);
  module_module(city, b);
  b = module_create();
  module_scale( b, 7, 2, 3);
  module_translate( b, x-60, y, z-5);
  module_bodyColor(b, &Grey);
  module_surfaceColor(b, &ltGrey);
  module_cube(b, 1);
  module_module(city, b);
  b = module_create();
  module_scale( b, 5, 15, 5);
  module_translate( b, x-60, y+5, z+30);
  module_bodyColor(b, &Grey);
  module_surfaceColor(b, &ltGrey);
  module_cube( b, 1 );
  module_module(city, b);

  b = module_create();
  module_scale( b, 7, 10, 5);
  module_translate( b, x-40, y+3, z+5);
  module_bodyColor(b, &Grey);
  module_surfaceColor(b, &ltGrey);
  module_cube(b, 1);
  module_module(city, b);
  b = module_create();
  module_scale( b, 5, 20, 7);
  module_translate( b, x-40, y+8, z+30);
  module_bodyColor(b, &Grey);
  module_surfaceColor(b, &ltGrey);
  module_cube(b, 1);
  module_module(city, b);

  b = module_create();
  module_scale( b, 5, 25, 7);
  module_translate( b, x-20, y+12, z+15);
  module_bodyColor(b, &Grey);
  module_surfaceColor(b, &ltGrey);
  module_cube(b, 1); 
  module_module(city, b);
  b = module_create();
  module_scale( b, 5, 20, 7);
  module_translate( b, x-20, y+8, z-5);
  module_bodyColor(b, &Grey);
  module_surfaceColor(b, &ltGrey);
  module_cube(b, 1);
  module_module(city, b);
  b = module_create();
  module_scale( b, 5, 30, 7);
  module_translate( b, x-20, y+15, z+30);
  module_bodyColor(b, &Grey);
  module_surfaceColor(b, &ltGrey);
  module_cube(b, 1);
  module_module(city, b);

  b = module_create();
  module_scale( b, 5, 30, 7);
  module_translate( b, x, y+15, z+15);
  module_bodyColor(b, &Grey);
  module_surfaceColor(b, &ltGrey);
  module_cube(b, 1);
  module_module(city, b);
  b = module_create();
  module_scale( b, 2, 3, 2);
  module_translate( b, x, y, z-7.5);
  module_bodyColor(b, &Grey);
  module_surfaceColor(b, &ltGrey);
  module_cube(b, 1);
  module_module(city, b);
  b = module_create();
  module_scale( b, 2, 3, 2);
  module_translate( b, x, y, z);
  module_bodyColor(b, &Grey);
  module_surfaceColor(b, &ltGrey);
  module_cube(b, 1);
  module_module(city, b);
  b = module_create();
  module_scale( b, 4, 20, 4);
  module_translate( b, x, y+12, z+30);
  module_bodyColor(b, &Grey);
  module_surfaceColor(b, &ltGrey);
  module_cube(b, 1);
  module_module(city, b);

  b = module_create();
  module_scale( b, 5, 15, 6);
  module_translate( b, x+20, y+7, z+30);
  module_bodyColor(b, &Grey);
  module_surfaceColor(b, &ltGrey);
  module_cube(b, 1);
  module_module(city, b);
  b = module_create();
  module_scale( b, 5, 15, 5);
  module_translate( b, x+20, y+7, z+15);
  module_bodyColor(b, &Grey);
  module_surfaceColor(b, &ltGrey);
  module_cube( b, 1);
  module_module(city, b);
  b = module_create();
  module_scale( b, 7, 2, 3);
  module_translate( b, x+20, y, z);
  module_bodyColor(b, &Grey);
  module_surfaceColor(b, &ltGrey);
  module_cube(b, 1);
  module_module(city, b);

  b = module_create();
  module_scale( b, 7, 2, 3);
  module_translate( b, x+40, y, z);
  module_bodyColor(b, &Grey);
  module_surfaceColor(b, &ltGrey);
  module_cube(b, 1);
  module_module(city, b);
  b = module_create();
  module_scale( b, 4, 5, 6);
  module_translate( b, x+40, y+2, z+15);
  module_bodyColor(b, &Grey);
  module_surfaceColor(b, &ltGrey);
  module_cube(b, 1);
  module_module(city, b);
  b = module_create();
  module_scale( b, 7, 10, 5);
  module_translate( b, x+40, y+5, z+30);
  module_bodyColor(b, &Grey);
  module_surfaceColor(b, &ltGrey);
  module_cube(b, 1);
  module_module(city, b);

  b = module_create();
  module_scale( b, 2, 5, 2);
  module_translate( b, x+60, y+2, z+30);
  module_bodyColor(b, &Grey);
  module_surfaceColor(b, &ltGrey);
  module_cube(b, 1);
  module_module(city, b);
  b = module_create();
  module_scale( b, 8, 4, 3);
  module_translate( b, x+60, y+2, z+10);
  module_bodyColor(b, &Grey);
  module_surfaceColor(b, &ltGrey);
  module_cube(b, 1);
  module_module(city, b);

  b = module_create();
  module_scale( b, 7, 2, 3);
  module_translate( b, x+70, y, z);
  module_bodyColor(b, &Grey);
  module_surfaceColor(b, &ltGrey);
  module_cube(b, 1);
  module_module(city, b);
  b = module_create();
  module_scale( b, 7, 10, 5);
  module_translate( b, x+70, y+5, z+20);
  module_bodyColor(b, &Grey);
  module_surfaceColor(b, &ltGrey);
  module_cube(b, 1);
  module_module(city, b);

  return((Module*)city);
}

static Module* sandscape();
static Module* sandscape(){
  Module *b, *terrain;
  terrain = module_create();

  // set up color palette
  Color brown =  {{72/255.0, 57/255.0, 42/255.0}};
  Color blueGrey = {{29/255.0, 30/255.0, 25/255.0}};
  Color wBrown = {{50/255.0, 31/255.0, 12/255.0}};
  Color sandyBrown = {{87/255.0, 68/255.0, 44/255.0}};
  Color ltBrown = {{147/255.0, 106/255.0, 57/255.0}};
  Color sandy = {{0.68, 0.52, 0.28}};

  b = module_create();
  module_scale(b, 170, 1, 60);
  module_translate(b, 0, -2, 78);
  module_bodyColor(b, &blueGrey);
  module_cube(b, 1);
  module_module(terrain, b);
  b = module_create();
  module_scale(b, 170, 1, 180);
  module_translate(b, 0, -2.5, 13);
  module_bodyColor(b, &ltBrown);
  module_cube(b, 1);
  module_module(terrain, b);
  b = module_create();
  module_scale(b, 170, 1.5, 180);
  module_translate(b, 0, -6, 13);
  module_bodyColor(b, &brown);
  module_cube(b, 1);
  module_module(terrain, b);
  b = module_create();
  module_scale(b, 170, 2, 180);
  module_translate(b, 0, -10, 13);
  module_bodyColor(b, &wBrown);
  module_cube(b, 1);
  module_module(terrain, b);
  b = module_create();
  module_scale(b, 170, 0.5, 180);
  module_translate(b, 0, -13, 13);
  module_bodyColor(b, &brown);
  module_cube(b, 1);
  module_module(terrain, b);
  b = module_create();
  module_scale(b, 170, 1, 180);
  module_translate(b, 0, -15, 13);
  module_bodyColor(b, &sandyBrown);
  module_cube(b, 1);
  module_module(terrain, b);

  return((Module*)terrain);
}

static Module* pyramid(int size, float x, float y, float z);
static Module* pyramid(int size, float x, float y, float z){
  Module *pyra;
  Color dark_sand = {{0.65, 0.42, 0.33}};
  
  pyra = module_create();
  module_bodyColor(pyra, &dark_sand);
  module_pyramid(pyra, 1, size, x, y, z);

  return((Module*)pyra);
}

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
	Module *cairo, *sand, *giza, *khuf, *khaf, *menk;
	View3D view;
	Matrix vtm, gtm;
	DrawState *ds;
	int i, frame;
	char buffer[256];
	float leaderSpeed = 2.0;
	int zoom, numFrames = 720;
	srand(time(NULL));

	// set up color palette
  Color navy = {{0, 0, 112/255.0}};
	Color Ambient = {{0.1, 0.1, 0.1}};
	Color White = {{1.0, 1.0, 1.0}};
	Color Black = {{0.0, 0.0, 0.0}};
	Color Blue = {{0.2, 0.2, 0.6}};
	Color yellow = {{253/255.0, 127/255.0, 25/255.0}};
	Color bottleGreen = {{33/255.0, 78/255.0, 25/255.0}};
	Color dkbottleGreen = {{27/255.0, 72/255.0, 19/255.0}};

	// set up modules
	cairo = module_create();
	sand = module_create();
	giza = module_create();
	khuf = module_create();
	khaf = module_create();
	menk = module_create();

	// create drawstate, lighting and image
	ds = drawstate_create();
	light = lighting_create();
	ds->shade = ShadeGouraud;
	src = image_create( rows, cols );

	// set up the view
	vector_set( &(view.vup), 0, 1, 0 );
	view.d = 5;
	view.du = 6;
	view.f = 1;
	view.b = 2000;
	view.screenx = cols;
	view.screeny = rows;
	matrix_identity( &gtm );

	// create the beetle
	beetle = module_create();
	module_bodyColor(beetle, &bottleGreen);
	module_scale(beetle, 1, 1, 1);
	module_cube(beetle, 1);
	module_scale(beetle, .75, .75, .75);
	module_bodyColor(beetle, &dkbottleGreen);
	module_translate(beetle, .5, 0, 0);
	module_cube(beetle, .5);
	module_bodyColor(beetle, &bottleGreen);
	module_translate(beetle, .25, 0, 0);
	module_cube(beetle, 1);

	// create the swarm
	point_set3D(&start, -80, 0, 0);
	vector_set(&velocity, leaderSpeed, 0, 0);
	beetleSwarm = swarm_create(&start, &velocity, beetle, 10, 20, 10);
	for(i=0; i<beetleSwarm->numActors; i++){
		beetleSwarm->actors[i].minDist = 7;
		beetleSwarm->actors[i].thresholdDist = 15;
	}

	// animate the scene
	for (frame=0; frame<numFrames; frame++){
		if(((frame+1) % (numFrames/8)) == 0){
			for(i=0; i<beetleSwarm->numLeaders; i++){
				beetleSwarm->leaders[i].velocity.val[0] *= -1;
				beetleSwarm->leaders[i].velocity.val[1] *= -1;
				beetleSwarm->leaders[i].velocity.val[2] *= -1;
			}
		}

		// set up egypt for the swarm, draw egypt
		sand = (Module*)sandscape();
		cairo = (Module*)city(0, 1, 65);
		khuf = pyramid(18, -40, 15, -50);
		khaf = pyramid(14, -5, 10, -10);
		menk = pyramid(10, 25, 5, 5);

		module_module(giza, khuf);
		module_module(giza, khaf);
		module_module(giza, menk);

		point_set3D( &(view.vrp), 40, 50, 100);
		vector_set( &(view.vpn), -view.vrp.val[0], -view.vrp.val[1], -view.vrp.val[2] );
		lighting_init(light);
		lighting_add( light, LightAmbient, &White, NULL, NULL, 0, 0 );
		lighting_add( light, LightPoint, &White, NULL, &(view.vrp), 0, 0 );
		point_copy(&(ds->viewer), &(view.vrp));
		matrix_setView3D( &vtm, &view );
		image_fillColor(src, navy);
		matrix_rotateY(&gtm, cos(M_PI/30.0), sin(M_PI/30.0) );

		// draw egypt
		module_draw(sand, &vtm, &gtm, ds, light, src );
		module_draw(giza, &vtm, &gtm, ds, light, src); 
		module_draw(cairo, &vtm, &gtm, ds, light, src);
		
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
  system("convert -delay 6 -loop 0 beetle-frame*.ppm beetle-invasion.gif");
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
  module_delete(beetle);
  module_delete(sand);
  module_delete(menk);
  module_delete(khaf);
  module_delete(khuf);
  module_delete(giza);
  module_delete(cairo);
  printf("modules freed\n");

  return(0);
}


