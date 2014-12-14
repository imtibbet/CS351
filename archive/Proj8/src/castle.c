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

/* Creates bricks using cube modules, color for the is chosen randomly from 
 * one of 4 colors of grey and brown. 
 */
static Module * genTower(float x, float y, float z);
static Module * genTower(float x, float y, float z){
	// set up fields
	Module *tower, *t, *sup, *stone, *roof;
	Color grey, dkGrey, brown, dkBrown;
	color_set(&grey, (float)(108/255.0), (float)(116/255.0), 
		(float)(111/255.0));
	color_set(&dkGrey, (float)(98/255.0), (float)(106/255.0), 
		(float)(101/255.0));
	color_set(&brown, (float)(113/255.0), (float)(83/255.0), 
		(float)(46/255.0));
	color_set(&dkBrown, (float)(58/255.0), (float)(18/255.0), 
		(float)(11/255.0));

	// create modules
	tower = module_create();
	t = module_create();
	sup = module_create();
	stone = module_create();
	roof = module_create();

	// basic tower cylinder
	module_scale(t, 1, 3, 1);
	module_color(t, &grey);
	module_cylinder(t, 20, 1, 8, x, y, z);
	module_module(tower, t);

	// smaller cylinder placed inside for staircase (flickering) effect
	t = module_create();
	module_scale(t, .8, 3, .8);
	module_color(t, &dkGrey);
	module_cylinder(t, 20, 1, 8, x, y, z);
	module_module(tower, t);

	// wooden posts to support the roof of the tower
	module_scale(sup, 1, 5.5, 1);
	module_translate(sup, x-4, y+25, z-4);
	module_color(sup, &brown);
	module_cube(sup, 1);
	module_module(tower, sup);
	sup = module_create();
	module_scale(sup, 1, 5.5, 1);
	module_translate(sup, x+4, y+25, z-4);
	module_color(sup, &brown);
	module_cube(sup, 1);
	module_module(tower, sup);
	sup = module_create();
	module_scale(sup, 1, 5.5, 1);
	module_translate(sup, x-4, y+25, z+4);
	module_color(sup, &brown);
	module_cube(sup, 1);
	module_module(tower, sup);
	sup = module_create();
	module_scale(sup, 1, 5.5, 1);
	module_translate(sup, x+4, y+25, z+4);
	module_color(sup, &brown);
	module_cube(sup, 1);
	module_module(tower, sup);

	// decorative stonework 1
	module_scale(stone, 2, 3, 2);
	module_translate(stone, x-7, y+24, z);
	module_color(stone, &dkGrey);
	module_cube(stone, 1);
	module_module(tower, stone);
	stone = module_create();
	module_scale(stone, 2, 3, 2);
	module_translate(stone, x+7, y+24, z);
	module_color(stone, &dkGrey);
	module_cube(stone, 1);
	module_module(tower, stone);
	stone = module_create();
	module_scale(stone, 2, 3, 2);
	module_translate(stone, x, y+24, z-7);
	module_color(stone, &dkGrey);
	module_cube(stone, 1);
	module_module(tower, stone);
	stone = module_create();
	module_scale(stone, 2, 3, 2);
	module_translate(stone, x, y+24, z+7);
	module_color(stone, &dkGrey);
	module_cube(stone, 1);
	module_module(tower, stone);
	// offset decorative stonework 2
	stone = module_create();
	module_scale(stone, 2, 3, 2);
	module_translate(stone, x-5, y+23, z-5);
	module_color(stone, &dkGrey);
	module_cube(stone, 1);
	module_module(tower, stone);
	stone = module_create();
	module_scale(stone, 2, 3, 2);
	module_translate(stone, x+5, y+23, z-5);
	module_color(stone, &dkGrey);
	module_cube(stone, 1);
	module_module(tower, stone);
	stone = module_create();
	module_scale(stone, 2, 3, 2);
	module_translate(stone, x-5, y+23, z+5);
	module_color(stone, &dkGrey);
	module_cube(stone, 1);
	module_module(tower, stone);
	stone = module_create();
	module_scale(stone, 2, 3, 2);
	module_translate(stone, x+5, y+23, z+5);
	module_color(stone, &dkGrey);
	module_cube(stone, 1);
	module_module(tower, stone);
	
	// roof of the tower
	module_color(roof, &dkBrown);
	module_cone(roof, 8, 1, 8, x, y+28, z);
	module_module(tower, roof);

	// printf("added tower\n");
	return((Module*)tower);
}

/* Creates a flame using a bezier surface*/
static Module* genFire(float x, float y, float z, int divisions, DrawState *ds);
static Module* genFire(float x, float y, float z, int divisions, DrawState *ds){
	Module *f[20];
	Module *fire;
	BezierSurface bc;
	int gen, i, scale;
	Color ltOrange, orange, dkOrange, red, yellow, amber, final;
	Point p[16];
	color_set(&ltOrange, 1, (float)(167/255.0), 0.0);
	color_set(&orange, 1, (float)(127/255.0), 0.0);
	color_set(&dkOrange, 1, (float)(103/255.0), 0.0);
	color_set(&red, 1, 0, 0);
	color_set(&yellow, 1, (float)(233/255.0), 0.0);
	color_set(&amber, 1, (float)(191/255.0), 0.0);
	color_set(&final, 0, 0, 0);

	scale = 10;

	bezierSurface_init(&bc);

	fire = module_create();
	drawstate_setSurface(ds, final);

	// create a curved surface sitting above the plane
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
	bezierSurface_set(&bc, p);

	for (i = 0; i < 20; i++){
		gen = (int)(rand() % 6);
		// printf("gen %d\n", gen);

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

		f[i] = module_create();

		module_scale((Module*)f[i], (float)((rand()%10)+5)/scale, (float)((rand()%30)+5)/scale, (float)((rand()%20)+1)/scale);
		// printf("module scaled\n");
		module_translate((Module*)f[i], x+3.0, y, z);
		// printf("module translated\n");
		module_color((Module*)f[i], &(ds->surface));
		// printf("ds->surface->c[1] %f\n", ds->surface.c[1]);
		module_bezierSurface((Module*)f[i], &bc, divisions, 1);
		// printf("surface set\n");
		module_module((Module*)fire, (Module*)f[i]);
		// printf("module added to fire\n");

		f[i] = module_create();

		module_scale((Module*)f[i], (float)((rand()%10)+5)/scale, (float)((rand()%30)+5)/scale, (float)((rand()%20)+1)/scale);
		module_translate((Module*)f[i], x+2.0, y, z);
		module_rotateY((Module*)f[i], 0, 1.3);
		module_color((Module*)f[i], &(ds->surface));
		module_bezierSurface((Module*)f[i], &bc, divisions, 1);
		module_module((Module*)fire, (Module*)f[i]);

		f[i] = module_create();

		module_scale((Module*)f[i], (float)((rand()%10)+5)/scale, (float)((rand()%30)+5)/scale, (float)((rand()%20)+1)/scale);
		module_translate((Module*)f[i], x+2.0, y, z);
		module_rotateY((Module*)f[i], 0, 1);
		module_rotateY((Module*)f[i], 0, 1.3);
		module_color((Module*)f[i], &(ds->surface));
		module_bezierSurface((Module*)f[i], &bc, divisions, 1);
		module_module((Module*)fire, (Module*)f[i]);

		f[i] = module_create();

		module_scale((Module*)f[i], (float)((rand()%10)+5)/scale, (float)((rand()%30)+5)/scale, (float)((rand()%20)+1)/scale);
		module_translate((Module*)f[i], x+2.0, y, z);
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
	Module *tower0, *tower1, *tower2, *tower3;
	Module *flames[60], *wall;
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
	ds->shade=ShadeDepth;
	src = image_create( rows, cols );

	// set up the view
	point_set3D( &(view.vrp), 0, 45, -70);
	vector_set( &(view.vpn), -view.vrp.val[0], -view.vrp.val[1], -view.vrp.val[2] );
	vector_set( &(view.vup), 0, 1, 0 );
	view.d = 5;
	view.du = 6;
	view.f = 1;
	view.b = 150;
	view.screenx = cols;
	view.screeny = rows;

	matrix_setView3D( &vtm, &view );
	matrix_identity( &gtm );

	for (frame=0; frame<60; frame++){
		tower0 = module_create();
		tower0 = genTower(-50, 0, 0);
		tower1 = module_create();
		tower1 = genTower(0, 0, 0);
		tower2 = module_create();
		tower2 = genTower(0, 0, -50);
		tower3 = module_create();
		tower3 = genTower(-50, 0, -50);
		flames[frame] = module_create();
		flames[frame] = genFire(0, 25, 0, 4, ds);
		wall = module_create();
		module_scale(wall, 50, 23, 1);
		module_translate(wall, 25, 10, 0);
		module_rotateY((Module*)wall, 0, 1);
		module_color((Module*)wall, &dkGrey);
		module_cube(wall, 1);
		module_draw(wall, &vtm, &gtm, ds, NULL, src);
		wall = module_create();
		module_scale(wall, 50, 23, 1);
		module_translate(wall, -25, 10, 0);
		module_color((Module*)wall, &dkGrey);
		module_cube(wall, 1);
		module_draw(wall, &vtm, &gtm, ds, NULL, src);
		wall = module_create();
		module_scale(wall, 50, 23, 1);
		module_translate(wall, 25, 10, -50);
		module_rotateY((Module*)wall, 0, 1);
		module_color((Module*)wall, &dkGrey);
		module_cube(wall, 1);
		module_draw(wall, &vtm, &gtm, ds, NULL, src);
		wall = module_create();
		module_scale(wall, 50, 23, 1);
		module_translate(wall, -25, 10, -50);
		module_color((Module*)wall, &dkGrey);
		module_cube(wall, 1);
		module_draw(wall, &vtm, &gtm, ds, NULL, src);

		char buffer[256];
		matrix_rotateY(&gtm, cos(M_PI/30.0), sin(M_PI/30.0) );
		// draw tower and flames
		module_draw( flames[frame], &vtm, &gtm, ds, NULL, src);
		module_draw( tower0, &vtm, &gtm, ds, NULL, src );
		module_draw( tower1, &vtm, &gtm, ds, NULL, src );
		module_draw( tower2, &vtm, &gtm, ds, NULL, src );
		module_draw( tower3, &vtm, &gtm, ds, NULL, src );

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


