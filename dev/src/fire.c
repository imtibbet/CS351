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

/* Creates a pile of logs, limited to a maximum of five logs along
 * the bottom. Returns a module of logs.
 */
static Module * genWood(float x, float y, float z);
static Module * genWood(float x, float y, float z){
	Module *wood, *outline, *woodpile;
	Color brown0, brown1, dkBrown0, dkBrown1, final, outlineC;
	int thickness, gen;
	srand(time(NULL));
	color_set(&brown0, (float)(123/255.0), (float)(63/255.0), 0.0);
	color_set(&brown1, (float)(112/255.0), (float)(66/255.0), (float)(20/255.0));
	color_set(&dkBrown0, (float)(101/255.0), (float)(67/255.0), (float)(33/255.0));
	color_set(&dkBrown1, (float)(72/255.0), (float)(60/255.0), (float)(50/255.0));
	color_set(&final, 0, 0, 0);

	gen = (int)(rand() % 3);
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

	wood = module_create();
	woodpile = module_create();
	outline = module_create();

	thickness = 10;

	module_scale(outline, 1, 4, 1);
	module_rotateX(outline, 0, 1);
	module_translate(outline, x, y, z);
	module_color(outline, &outlineC);
	module_cylinder(outline, 20, 0, thickness, 0, 0, 0);
	module_module(woodpile, outline);

	module_scale(wood, 1, 4, 1);
	module_rotateX(wood, 0, 1);
	module_translate(wood, x, y, z);
	module_color(wood, &final);
	module_cylinder(wood, 20, 1, thickness, 0, 0, 0);
	module_module(woodpile, wood);

	printf("added wood\n");

	return((Module*)woodpile);
}

static Module* genWoodpile(float x, float y, float z);
static Module* genWoodpile(float x, float y, float z){
	Module *wood, *woodpile;
	woodpile = module_create();

	wood = module_create();
 	wood = genWood(x, y, z);
 	module_module(woodpile, wood);
 	wood = module_create();
 	wood = genWood(2+x, y, z);
 	module_module(woodpile, wood);
 	wood = module_create();
 	wood = genWood(4+x, y, z);
 	module_module(woodpile, wood);
 	wood = module_create();
 	wood = genWood(x-2, y, z);
 	module_module(woodpile, wood);
 	wood = module_create();
 	wood = genWood(x-1, y+1.5, z);
 	module_module(woodpile, wood);
 	wood = module_create();
 	wood = genWood(x+1, y+1.5, z);
 	module_module(woodpile, wood);
 	wood = module_create();
 	wood = genWood(x+3, y+1.5, z);
 	module_module(woodpile, wood);
 	wood = module_create();
 	wood = genWood(x+2, y+3, z);
 	module_module(woodpile, wood);
 	wood = module_create();
 	wood = genWood(x, y+3, z);
 	module_module(woodpile, wood);

 	printf("added woodpile\n");

 	return((Module*)woodpile);

}

/* Creates a flame using a bezier surface*/
static Module* genFlame(float x, float y, float z, int divisions);
static Module* genFlame(float x, float y, float z, int divisions){
	Module *flame;
	BezierSurface bc;
	Color red;
	Point p[16];
	color_set(&red, 1, 0, 0);

	flame = module_create();

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

	module_color(flame, &red);
	module_bezierSurface(flame, &bc, divisions, 1);

	return((Module*)flame);
}

int main(int argc, char *argv[]) {
	// initialize fields
	const int rows = 600*2;
	const int cols = 660*2;
	int frame;
	int divisions = 5;
	Image *src;
	Module *woodpile, *fireside, *flame;
	Polygon p;
	View3D view;
	Matrix vtm, gtm;
	DrawState *ds;
	char command[256];
	float alpha;
	Color blue, green;
	color_set(&blue, 0, 0, 1);
	color_set(&green, 0, 1, 0);

	// grab the command line argument, if one exists
	if(argc > 1) {
		int tmp = atoi(argv[1]);
		if( tmp >= 0 && tmp < 10 )
			divisions = tmp;
	}
	printf("Creating Bezier surface with %d subdivisions\n", divisions);

	// scene setup
	woodpile = module_create();
	fireside = module_create();

	woodpile = (Module*)genWoodpile(0, 0, 0);
	module_module(fireside, woodpile);

	// set up the view
	vector_set( &(view.vpn), -view.vrp.val[0], -view.vrp.val[1], -view.vrp.val[2] );
	vector_set( &(view.vup), 0, 1, 0 );
	view.d = 8;
	view.du = 6;
	view.f = 1;
	view.b = 50;
	view.screenx = cols;
	view.screeny = rows;

	printf("set up view\n");

	matrix_setView3D( &vtm, &view );
 	matrix_identity( &gtm );

	color_set(&blue, 0, 0, 1);

	// create the image and drawstate
	src = image_create( rows, cols );
	ds = drawstate_create();
	ds->shade = ShadeConstant;
	printf("created the image and drawstate\n");

	// Create the animation by adjusting the GTM
	for(frame=0;frame<60;frame++) {
		char buffer[256];

		matrix_rotateY(&gtm, cos(M_PI/30.0), sin(M_PI/30.0) );
		module_draw( fireside, &vtm, &gtm, &ds, NULL, src );

		sprintf(buffer, "fire-frame%03d.ppm", frame);
		image_write(src, buffer);
		image_reset(src);
	}

	// write out the scene
	printf("converting to gif...\n");
	system("convert -delay 1.5 -loop 0 fire-frame*.ppm fire.gif");
	system("rm fire-frame*.ppm");

	// free the polygon data
	polygon_clear( &p );
	printf("polygon freed\n");

	// free the modules
	module_delete(woodpile);
	module_delete(fireside);
	printf("module freed\n");

	// free drawstate
	free(ds);
	printf("drawstate freed\n");

	// free image
	image_free( src );
	printf("image freed\n");

	return(0);
}


