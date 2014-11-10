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
static Module* genFire(float x, float y, float z, int divisions);
static Module* genFire(float x, float y, float z, int divisions){
	Module *f[20];
	Module *fire;
	BezierSurface bc;
	int gen, i;
	Color ltOrange, orange, dkOrange, red, yellow, amber, final;
	Point p[16];
	srand(time(NULL));
	color_set(&ltOrange, 1, (float)(167/255), 0);
	color_set(&orange, 1, (float)(127/255), 0);
	color_set(&dkOrange, 1, (float)(103/255), 0);
	color_set(&red, 1, 0, 0);
	color_set(&yellow, 1, (float)(233/255), 0);
	color_set(&amber, 1, (float)(191/255), 0);
	color_set(&final, 0, 0, 0);

	bezierSurface_init(&bc);

	fire = module_create();

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

		if (gen == 0){
			color_copy(&final, &ltOrange);
		}
		if (gen == 1){
			color_copy(&final, &orange);
		}
		if (gen == 2){
			color_copy(&final, &dkOrange);
		}
		if (gen == 3){
			color_copy(&final, &red);
		}
		if (gen == 4){
			color_copy(&final, &yellow);
		}
		else{
			color_copy(&final, &amber);
		}

		f[i] = module_create();
		module_scale((Module*)f[i], (float)((rand()%10)+5), (float)((rand()%30)+5), (float)((rand()%20)+1));
		module_translate((Module*)f[i], (float)(x+20), y, z);
		module_color((Module*)f[i], &(final));
		module_bezierSurface((Module*)f[i], &bc, divisions, 1);
		module_module((Module*)fire, (Module*)f[i]);
	}

	// printf("Creating flames with %d subdivisions\n", divisions);

	return((Module*)fire);
}

int main(int argc, char *argv[]) {
	// initialize fields
	const int rows = 600*2;
	const int cols = 660*2;
	Image *src;
	Module *flame;
	View3D view;
	Matrix vtm, gtm;
	DrawState ds;
	float alpha;
	Color blue, green;
	int frame;
	color_set(&blue, 0, 0, 1);
	color_set(&green, 0, 1, 0);

	drawstate_setColor(&ds, blue);
	ds.shade = ShadeConstant;
	src = image_create( rows, cols );

	// grab command line argument to determine viewpoint
    // and set up the view structure
    if( argc > 1 ) {
        alpha = atof( argv[1] );
        if( alpha < 0.0 || alpha > 1.0 )
            alpha = 0.0;
        point_set3D( &(view.vrp), 20*alpha, alpha, -50*alpha - (alpha*170-cos(alpha)*170) );
    } else {
		point_set3D( &(view.vrp), 0, 0, -100);
    }

	// set up the view
	vector_set( &(view.vpn), -view.vrp.val[0], -view.vrp.val[1], -view.vrp.val[2] );
	vector_set( &(view.vup), 0, 1, 0 );
	view.d = 8;
	view.du = 6;
	view.f = 1;
	view.b = 50;
	view.screenx = cols;
	view.screeny = rows;

	matrix_setView3D( &vtm, &view );
	matrix_identity( &gtm );
	flame = module_create();

 	// create the animation by adjusting the gtm
	for(frame=0;frame<60;frame++) {
		// create the image and drawstate
		char buffer[256];
		flame = genFire(0, 0, 0, 4);

		matrix_rotateY(&gtm, cos(M_PI/30.0), sin(M_PI/30.0) );
		module_draw( flame, &vtm, &gtm, &ds, NULL, src );

		sprintf(buffer, "fire-frame%03d.ppm", frame);
		image_write(src, buffer);
		image_reset(src);
	}

	printf("converting to gif...\n");
	system("convert -delay 1.5 -loop 0 fire-frame*.ppm fire.gif");
	printf("converted gif\n");
	system("rm fire-frame*.ppm");
	printf("animating gif...\n");
	system("animate fire.gif");

	image_free(src);
	module_delete(flame);

	return(0);
}


