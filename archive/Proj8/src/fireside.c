/*
Astrid Moore (Bruce Maxwell)
Fall 2014

Example of a 3D scene model

draws a fire
 */

#include "graphics.h"
#include <time.h>
#include <stdlib.h>

/* declare methods here for testing flexibility */

/* Creates wood using cylinders, color for the is chosen randomly from 
 * one of 4 colors of brown. Fill specifies how the shape should be filled:
 * 0 = outline
 * 1 = filled
 * other = both outlined and filled
 */
static Module * genWood(float x, float y, float z, int fill);
static Module * genWood(float x, float y, float z, int fill){
	// set up fields
	Module *wood, *outline, *woodpile;
	Color brown0, brown1, dkBrown0, dkBrown1, final, outlineC;
	int thickness, gen;
	// set up different brown colors for wood
	color_set(&brown0, (float)(123/255.0), (float)(63/255.0), 
		0.0);
	color_set(&brown1, (float)(112/255.0), (float)(66/255.0), 
		(float)(20/255.0));
	color_set(&dkBrown0, (float)(101/255.0), (float)(67/255.0), 
		(float)(33/255.0));
	color_set(&dkBrown1, (float)(72/255.0), (float)(60/255.0), 
		(float)(50/255.0));
	color_set(&final, 0, 0, 0);

	// randomly generate a number between 0 and 4 inclusive
	gen = (int)(rand() % 4);
	// select outline color and fill color depending on gen
	if (gen == 0){
		color_copy(&final, &brown0);
		color_copy(&outlineC, &dkBrown0);
	}
	if (gen == 1){
		color_copy(&final, &brown1);
		color_copy(&outlineC, &dkBrown1);
	}
	if (gen == 2){
		color_copy(&final, &dkBrown0);
		color_copy(&outlineC, &brown0);
	}
	else{
		color_copy(&final, &dkBrown1);
		color_copy(&outlineC, &brown1);
	}

	// create modules
	wood = module_create();
	woodpile = module_create();
	outline = module_create();

	// set cylinder thickness
	thickness = 6;

	// if 0, only outline drawn
	if( fill == 0 ){
		module_scale(outline, 1, 3, 1);
		module_rotateX(outline, 0, 1);
		module_translate(outline, x, y, z);
		module_color(outline, &outlineC);
		module_cylinder(outline, 15, 0, thickness, 0, 0, 0);
		module_module(woodpile, outline);
	}
	// if 1, only filled
	else if( fill == 1){
		module_scale(wood, 1, 3, 1);
		module_rotateX(wood, 0, 1);
		module_translate(wood, x, y, z);
		module_color(wood, &final);
		module_cylinder(wood, 15, 1, thickness, 0, 0, 0);
		module_module(woodpile, wood);
	}
	// both filled and then overlain with an outline
	else{
		module_scale(wood, 1, 3, 1);
		module_rotateX(wood, 0, 1);
		module_translate(wood, x, y, z);
		module_color(wood, &final);
		module_cylinder(wood, 15, 1, thickness, 0, 0, 0);
		module_module(woodpile, wood);

		module_scale(outline, 1, 3, 1);
		module_rotateX(outline, 0, 1);
		module_translate(outline, x, y, z);
		module_color(outline, &outlineC);
		module_cylinder(outline, 15, 0, thickness, 0, 0, 0);
		module_module(woodpile, outline);
	}

	// printf("added wood\n");

	return((Module*)woodpile);
}

/* Generates a flickering woodpile using wood. Fill style for wood can 
 * be specified through the 'fill' parameter (see genWood()).
 * The woodpile flickers as a collective whole, not individually.
 */
static Module* genWoodPile(float x, float y, float z, int fill);
static Module* genWoodPile(float x, float y, float z, int fill){

	// define fields + create output module, woodpile
	Module *wood, *woodpile;
	woodpile = module_create();

	// bottom layer of wood
	wood = module_create();
 	wood = genWood(x-3, y, z-2, fill);
 	module_module(woodpile, wood);
	wood = module_create();
 	wood = genWood(x-1, y, z-2, fill);
 	module_module(woodpile, wood);
 	wood = module_create();
 	wood = genWood(x+1, y, z-2, fill);
 	module_module(woodpile, wood);
 	wood = module_create();
 	wood = genWood(x+3, y, z-2, fill);
 	module_module(woodpile, wood);

 	// middle layer of wood
 	wood = module_create();
 	wood = genWood(x-2, y+1.5, z-2, fill);
 	module_module(woodpile, wood);
 	wood = module_create();
 	wood = genWood(x, y+1.5, z-2, fill);
 	module_module(woodpile, wood);
 	wood = module_create();
 	wood = genWood(x+2, y+1.5, z-2, fill);
 	module_module(woodpile, wood);

 	// top layer of wood
 	wood = module_create();
 	wood = genWood(x-1, y+3, z-2, fill);
 	module_module(woodpile, wood);
 	wood = module_create();
 	wood = genWood(x+1, y+3, z-2, fill);
 	module_module(woodpile, wood);

 	return((Module*)woodpile);
}


/* Creates a flame using a bezier surface (source: Bruce Maxwell). 
 * A set of 20 individual flames are generated and then added to
 * a module, fire. Fire module is then copied 4 different directions
 * to give further 3D complexity to the flames. The degree of 
 * subdivisions is moderated by the parameter, divisions. Drawstate
 * is passed through so that each flame can have a varied color 
 * (by half). Scale increases the upper bound for the random range of 
 * of the fire to generate larger, broader flames. */
static Module* genFire(float x, float y, float z, int divisions, 
	DrawState *ds, int scale);
static Module* genFire(float x, float y, float z, int divisions, 
	DrawState *ds, int scale){
	// define fields
	Module *f[20];
	Module *fire;
	BezierSurface bc;
	int gen, i;
	Color ltOrange, orange, dkOrange, red, yellow, amber, final;
	Point p[16];
	// set fire colors
	color_set(&ltOrange, 1, (float)(167/255.0), 0.0);
	color_set(&orange, 1, (float)(127/255.0), 0.0);
	color_set(&dkOrange, 1, (float)(103/255.0), 0.0);
	color_set(&red, 1, 0, 0);
	color_set(&yellow, 1, (float)(233/255.0), 0.0);
	color_set(&amber, 1, (float)(191/255.0), 0.0);
	color_set(&final, 0, 0, 0);

	// init bezier surface
	bezierSurface_init(&bc);

	// create fire module + set default drawstate
	fire = module_create();
	drawstate_setSurface(ds, final);

	// points to form a curved surface (Bruce Maxwell)
	point_set3D(&p[0], 0.0, 0.0, 0.0); // first row, constant x, even spacing in z
	point_set3D(&p[1], 0.0, 0.2, 0.33);
	point_set3D(&p[2], 0.0, 0.5, 0.66);
	point_set3D(&p[3], 0.0, 0.1, 1.0);
	point_set3D(&p[4], 0.33, 0.8, 0.0); // second row
	point_set3D(&p[5], 0.33, -0.1, 0.33);
	point_set3D(&p[6], 0.33, 0.0, 0.66);
	point_set3D(&p[7], 0.33, 0.3, 1.0);
	point_set3D(&p[8], 0.66, 0.3, 0.0); // third row
	point_set3D(&p[9], 0.66, 0.8, 0.33);
	point_set3D(&p[10], 0.66, 0.9, 0.66);
	point_set3D(&p[11], 0.66, 0.5, 1.0);
	point_set3D(&p[12], 1.0, 0.4, 0.0); // fourth row
	point_set3D(&p[13], 1.0, 0.2, 0.33);
	point_set3D(&p[14], 1.0, 0.5, 0.66);
	point_set3D(&p[15], 1.0, 1.0, 1.0);
	// set bezier surface
	bezierSurface_set(&bc, p);

	// iterate through all 20 flames, copying + rotating around to fill 
	// all the quandrants with fire
	for (i = 0; i < 20; i++){
		// generate a random number between 0 and 6
		gen = (int)(rand() % 6);
		// printf("gen %d\n", gen);

		// set color based on gen
		if (gen == 0){
			drawstate_setSurface(ds, ltOrange);
			printf("ltOrange flame\n");
		}
		else if (gen == 1){
			drawstate_setSurface(ds, orange);
			printf("orange flame\n");
		}
		else if (gen == 2){
			drawstate_setSurface(ds, dkOrange);
			printf("dkOrange flame\n");
		}
		else if (gen == 3){
			drawstate_setSurface(ds, red);
			printf("red flame\n");
		}
		else if (gen == 4){
			drawstate_setSurface(ds, yellow);	
			printf("yellow flame\n");
		}
		else if (gen == 5){
			drawstate_setSurface(ds, amber);
			printf("amber flame\n");
		}

		// flame set 1
		f[i] = module_create();
		module_scale((Module*)f[i], (float)((rand()%(10*scale))+5), 
			(float)((rand()%(30*scale))+5), (float)((rand()%(20*scale))+1));
		// printf("module scaled\n");
		module_translate((Module*)f[i], x-2.0, y, z-2);
		// printf("module translated\n");
		module_color((Module*)f[i], &(ds->surface));
		// printf("ds->surface->c[1] %f\n", ds->surface.c[1]);
		module_bezierSurface((Module*)f[i], &bc, divisions, 1);
		// printf("surface set\n");
		module_module((Module*)fire, (Module*)f[i]);
		// printf("module added to fire\n");

		// flame set 2
		f[i] = module_create();
		module_scale((Module*)f[i], (float)((rand()%(10*scale))+5), 
			(float)((rand()%(30*scale))+5), (float)((rand()%(20*scale))+1));
		module_translate((Module*)f[i], x-2.0, y, z-2);
		module_rotateY((Module*)f[i], 0, 1.3);
		module_color((Module*)f[i], &(ds->surface));
		module_bezierSurface((Module*)f[i], &bc, divisions, 1);
		module_module((Module*)fire, (Module*)f[i]);

		// generate a fresh random number between 0 and 6 inclusive
		gen = (int)(rand() % 6);
		// printf("gen %d\n", gen);

		// set color based on gen
		if (gen == 0){
			drawstate_setSurface(ds, ltOrange);
			// printf("ltOrange flame\n");
		}
		else if (gen == 1){
			drawstate_setSurface(ds, orange);
			// printf("orange flame\n");
		}
		else if (gen == 2){
			drawstate_setSurface(ds, dkOrange);
			// printf("dkOrange flame\n");
		}
		else if (gen == 3){
			drawstate_setSurface(ds, red);
			// printf("red flame\n");
		}
		else if (gen == 4){
			drawstate_setSurface(ds, yellow);	
			// printf("yellow flame\n");
		}
		else if (gen == 5){
			drawstate_setSurface(ds, amber);
			// printf("amber flame\n");
		}

		// flame set 3
		f[i] = module_create();
		module_scale((Module*)f[i], (float)((rand()%(10*scale))+5), 
			(float)((rand()%(30*scale))+5), (float)((rand()%(20*scale))+1));
		module_translate((Module*)f[i], x-2.0, y, z-2);
		module_rotateY((Module*)f[i], 0, 1);
		module_rotateY((Module*)f[i], 0, 1.3);
		module_color((Module*)f[i], &(ds->surface));
		module_bezierSurface((Module*)f[i], &bc, divisions, 1);
		module_module((Module*)fire, (Module*)f[i]);

		// flame set 4
		f[i] = module_create();
		module_scale((Module*)f[i], (float)((rand()%(10*scale))+5), 
			(float)((rand()%(30*scale))+5), (float)((rand()%(20*scale))+1));
		module_translate((Module*)f[i], x-2.0, y, z-2);
		module_rotateY((Module*)f[i], 0, 1);
		module_rotateY((Module*)f[i], 0, 1);
		module_rotateY((Module*)f[i], 0, 1.3);
		module_color((Module*)f[i], &(ds->surface));
		module_bezierSurface((Module*)f[i], &bc, divisions, 1);
		module_module((Module*)fire, (Module*)f[i]);
	}

	// printf("Creating flames with %d subdivisions\n", divisions);

	return((Module*)fire);
}

int main(int argc, char *argv[]) {
	// initialize fields
	const int rows = 500*2;
	const int cols = 560*2;
	Image *src;
	Module *flames[60], *woodpile;
	View3D view;
	Matrix vtm, gtm;
	DrawState *ds;
	Color blue, green;
	int frame;
	char command[256];
	color_set(&blue, 0, 0, 1);
	color_set(&green, 0, 1, 0);
	srand(time(NULL));

	// create drawstate + image
	ds = drawstate_create();
	src = image_create( rows, cols );

	// set up the view
	point_set3D( &(view.vrp), 0, 50, -80);
	vector_set( &(view.vpn), -view.vrp.val[0], -view.vrp.val[1], -view.vrp.val[2] );
	vector_set( &(view.vup), 0, 1, 0 );
	view.d = 5;
	view.du = 6;
	view.f = 1;
	view.b = 50;
	view.screenx = cols;
	view.screeny = rows;

	matrix_setView3D( &vtm, &view );
	matrix_identity( &gtm );

 	// create the animation by adjusting the gtm
	for(frame=0;frame<60;frame++) {
		char buffer[256];
		// create each fire as an item in an array of fire modules
		flames[frame] = module_create();
		// generate fire, inputing drawstate
		flames[frame] = genFire(0, -6, 0, 6, ds, 1);

		// create filled woodpile module 
		woodpile = module_create();
		woodpile = genWoodPile(0, 0, 0, 1);
		matrix_rotateY(&gtm, cos(M_PI/30.0), sin(M_PI/30.0) );
		// draw woodpile
		module_draw( woodpile, &vtm, &gtm, ds, NULL, src );
		// draw flames
		module_draw( flames[frame], &vtm, &gtm, ds, NULL, src );

		// create outlined woodpile module to overlay + boost 3D visual effect
		woodpile = module_create();
		woodpile = genWoodPile(0, 0, 0, 0);
		// draw woodpile
		module_draw( woodpile, &vtm, &gtm, ds, NULL, src );

		// write out image
		sprintf(buffer, "fireside-frame%03d.ppm", frame);
		image_write(src, buffer);
		sprintf(command, "convert -scale %03dx%03d fireside-frame%03d.ppm fireside-frame%03d.ppm", 
		cols/2, rows/2, frame, frame);
		system(command);
		// reset image
		image_reset(src);
	}

	// convert to gif
	printf("converting to gif...\n");
	system("convert -delay 2 -loop 0 fireside-frame*.ppm fireside.gif");
	printf("converted gif\n");
	// remove ppm files
	system("rm fireside-frame*.ppm");
	printf("animating gif...\n");
	// animate gif
	system("animate fireside.gif");

	// free drawstate, image, modules
	free(ds);
	image_free(src);
	for(frame=0;frame<60;frame++){
		module_delete(flames[frame]);
	}
	module_delete(woodpile);

	return(0);
}


