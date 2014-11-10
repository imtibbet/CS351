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

/* Creates a flame using a bezier surface*/
static Module* genFire(float x, float y, float z, int divisions, DrawState *ds);
static Module* genFire(float x, float y, float z, int divisions, DrawState *ds){
	Module *f[20];
	Module *fire;
	BezierSurface bc;
	int gen, i;
	Color ltOrange, orange, dkOrange, red, yellow, amber, final;
	Point p[16];
	color_set(&ltOrange, 1, (float)(167/255.0), 0.0);
	color_set(&orange, 1, (float)(127/255.0), 0.0);
	color_set(&dkOrange, 1, (float)(103/255.0), 0.0);
	color_set(&red, 1, 0, 0);
	color_set(&yellow, 1, (float)(233/255.0), 0.0);
	color_set(&amber, 1, (float)(191/255.0), 0.0);
	color_set(&final, 0, 0, 0);

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

		f[i] = module_create();

		if (!f[i]){
			printf("absent module\n");
		}

		module_scale((Module*)f[i], (float)((rand()%10)+5), (float)((rand()%30)+5), (float)((rand()%20)+1));
		// printf("module scaled\n");
		module_translate((Module*)f[i], (float)(x+40), y, z);
		// printf("module translated\n");
		module_color((Module*)f[i], &(ds->surface));
		// printf("ds->surface->c[1] %f\n", ds->surface.c[1]);
		module_bezierSurface((Module*)f[i], &bc, divisions, 1);
		// printf("surface set\n");
		module_module((Module*)fire, (Module*)f[i]);
		// printf("module added to fire\n");
	}

	// printf("Creating flames with %d subdivisions\n", divisions);

	return((Module*)fire);
}

int main(int argc, char *argv[]) {
	// initialize fields
	const int rows = 600*2;
	const int cols = 660*2;
	Image *src;
	Module *flames[60];
	View3D view;
	Matrix vtm, gtm;
	DrawState *ds;
	float alpha;
	Color blue, green;
	int frame;
	color_set(&blue, 0, 0, 1);
	color_set(&green, 0, 1, 0);
	srand(time(NULL));

	ds = drawstate_create();
	src = image_create( rows, cols );

    point_set3D( &(view.vrp), 0, 0, -100);

	// set up the view
	vector_set( &(view.vpn), -view.vrp.val[0], -view.vrp.val[1], -view.vrp.val[2] );
	vector_set( &(view.vup), 0, 1, 0 );
	view.d = 10;
	view.du = 6;
	view.f = 1;
	view.b = 50;
	view.screenx = cols;
	view.screeny = rows;

	matrix_setView3D( &vtm, &view );
	matrix_identity( &gtm );

 	// create the animation by adjusting the gtm
	for(frame=0;frame<60;frame++) {
		// create the image and drawstate
		char buffer[256];
		flames[frame] = module_create();
		flames[frame] = genFire(0, 0, 0, 4, ds);

		matrix_rotateY(&gtm, cos(M_PI/30.0), sin(M_PI/30.0) );
		module_draw( flames[frame], &vtm, &gtm, ds, NULL, src );

		sprintf(buffer, "fire-frame%03d.ppm", frame);
		image_write(src, buffer);
		image_reset(src);
	}

	printf("converting to gif...\n");
	system("convert -delay 4 -loop 0 fire-frame*.ppm fire.gif");
	printf("converted gif\n");
	system("rm fire-frame*.ppm");
	printf("animating gif...\n");
	system("animate fire.gif");

	image_free(src);

	for(frame=0;frame<60;frame++){
		module_delete(flames[frame]);
	}

	return(0);
}


