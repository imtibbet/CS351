/*
Astrid Moore (Bruce Maxwell)
Fall 2014

Example of a 3D scene model

Draws Egypt with Cairo + the pyramids of Giza
 */

#include "graphics.h"
#include <time.h>
#include <stdlib.h>

static Module* city();
static Module* city(){
	Module *b[40];
	Module *city;
	srand(time(NULL));
	int i;
	float x[21];
	Color c[21];

	Color Black = {{0.0, 0.0, 0.0}};

	for( i = 0; i < 22; i++){
		x[i] = ((float)rand()/(float)(RAND_MAX));
		printf("x=%f\n", (float)x[i]);
		color_set(&c[i], (float)x[i], (float)x[i], (float)x[i]);
	}

	city = module_create();

	 	// buildings
 	b[0] = module_create();
 	module_scale( b[0], 4, 4, 20);
 	module_rotateX( b[0], 0, 1);
 	module_translate( b[0], -40, 2.5, 0);
 	module_color(b[0], &c[0]);
 	module_cube(b[0], 1);
 	b[1] = module_create();
 	module_scale( b[1], 7, 3, 2);
 	module_rotateX( b[1], 0, 1);
 	module_translate( b[1], -40, -6.5, 10);
 	module_color(b[1], &c[1]);
 	module_cube(b[1], 1);

  	b[2] = module_create();
 	module_scale( b[2], 5, 5, 15);
 	module_rotateX( b[2], 0, 1);
 	module_translate( b[2], -30, 0, 0);
 	module_color( b[2], &c[2]);
 	module_cube( b[2], 1 );
 	b[3] = module_create();
 	module_scale( b[3], 7, 5, 10);
 	module_rotateX( b[3], 0, 1);
 	module_translate( b[3], -30, -2.5, 10);
 	module_color(b[3], &c[3]);
 	module_cube(b[3], 1);
 	b[4] = module_create();
 	module_scale( b[4], 5, 7, 20);
 	module_rotateX( b[4], 0, 1);
 	module_translate( b[4], -30, 2.5, 20);
 	module_color(b[4], &c[4]);
 	module_cube(b[4], 1);

 	b[5] = module_create();
 	module_scale( b[5], 5, 7, 27);
 	module_rotateX( b[5], 0, 1);
 	module_translate( b[5], -20, 6, 0);
 	module_color(b[5], &c[5]);
 	module_cube(b[5], 1); 
 	b[6] = module_create();
 	module_scale( b[6], 5, 7, 20);
 	module_rotateX( b[6], 0, 1);
 	module_translate( b[6], -20, 2.5, 10);
 	module_color(b[6], &c[6]);
 	module_cube(b[6], 1);
 	b[7] = module_create();
 	module_scale( b[7], 5, 7, 30);
 	module_rotateX( b[7], 0, 1);
 	module_translate( b[7], -20, 7.5, 20);
 	module_color(b[7], &c[7]);
 	module_cube(b[7], 1);

  	b[8] = module_create();
 	module_scale( b[8], 5, 7, 30);
 	module_rotateX( b[8], 0, 1);
 	module_translate( b[8], -10, 7.5, 0);
 	module_color(b[8], &c[8]);
 	module_cube(b[8], 1);
 	b[9] = module_create();
 	module_scale( b[9], 2, 2, 3);
 	module_rotateX( b[9], 0, 1);
 	module_translate( b[9], -10, -6, 10);
 	module_color(b[9], &c[9]);
 	module_cube(b[9], 1);
 	b[10] = module_create();
 	module_scale( b[10], 2, 2, 3);
 	module_rotateX( b[10], 0, 1);
 	module_translate( b[10], -10, -6, 15);
 	module_color(b[10], &c[10]);
 	module_cube(b[10], 1);
 	b[11] = module_create();
 	module_scale( b[11], 4, 4, 20);
 	module_rotateX( b[11], 0, 1);
 	module_translate( b[11], -10, 2.5, 20);
 	module_color(b[11], &c[11]);
 	module_cube(b[11], 1);

 	b[12] = module_create();
 	module_scale( b[12], 5, 5, 15);
 	module_rotateX( b[12], 0, 1);
 	module_translate( b[12], 0, 0, 0);
 	module_color( b[12], &c[12]);
 	module_cube( b[12], 1);
 	b[13] = module_create();
 	module_scale( b[13], 5, 6, 15);
 	module_rotateX( b[13], 0, 1);
 	module_translate( b[13], 0, 0, 12.5);
 	module_color(b[13], &c[13]);
 	module_cube(b[13], 1);
  	b[14] = module_create();
 	module_scale( b[14], 7, 3, 2);
 	module_rotateX( b[14], 0, 1);
 	module_translate( b[14], 0, -6.5, 20);
 	module_color(b[14], &c[14]);
 	module_cube(b[14], 1);

 	b[15] = module_create();
 	module_scale( b[15], 7, 3, 2);
 	module_rotateX( b[15], 0, 1);
 	module_translate( b[15], 10, -6.5, 0);
 	module_color(b[15], &c[15]);
 	module_cube(b[15], 1);
 	b[16] = module_create();
 	module_scale( b[16], 4, 6, 3);
 	module_rotateX( b[16], 0, 1);
 	module_translate( b[16], 10, -6, 10);
 	module_color(b[16], &c[16]);
 	module_cube(b[16], 1);
 	b[17] = module_create();
 	module_scale( b[17], 7, 5, 10);
 	module_rotateX( b[17], 0, 1);
 	module_translate( b[17], 10, -2.5, 20);
 	module_color(b[17], &c[17]);
 	module_cube(b[17], 1);

  	b[18] = module_create();
 	module_scale( b[18], 2, 2, 5);
 	module_rotateX( b[18], 0, 1);
 	module_translate( b[18], 20, -5, 0);
 	module_color(b[18], &c[18]);
 	module_cube(b[18], 1);
 	b[19] = module_create();
 	module_scale( b[19], 8, 3, 4);
 	module_rotateX( b[19], 0, 1);
 	module_translate( b[19], 20, -5.5, 10);
 	module_color(b[19], &c[19]);
 	module_cube(b[19], 1);

 	b[20] = module_create();
 	module_scale( b[20], 7, 3, 2);
 	module_rotateX( b[20], 0, 1);
 	module_translate( b[20], 30, -6.5, 0);
 	module_color(b[20], &c[20]);
 	module_cube(b[20], 1);
 	b[21] = module_create();
 	module_scale( b[21], 7, 5, 10);
 	module_rotateX( b[21], 0, 1);
 	module_translate( b[21], 30, -2.5, 10);
 	module_color(b[21], &Black);
 	module_cube(b[21], 1);

	for ( i = 0; i < 22; i++){
		module_module((Module*)city, (Module*)b[i]);
	}

	return((Module*)city);
}

static Module* sandscape(){
	Module *sand;
	Color sandy = {{0.68, 0.52, 0.28}};

	sand = module_create();
	module_scale(sand, 100, 2, 100);
	module_translate(sand, 0, -6, 40);
	module_color(sand, &sandy);
	module_cube(sand, 1);

	return((Module*)sand);
}

static Module* pyramid(){
	Color dark_sand = {{0.65, 0.47, 0.22}};
	Polygon side[5];
	Polygon tpoly;
	Point tv[4];
    Point v[8];
   	Module *pyra;
    int i;

	// initialize polygons
    for(i=0;i<5;i++) {
        polygon_init( &side[i] );
    }

    // corners of a pyramid, centered at (0, 0, 0)
    point_set3D(&v[0], -1, -1, -1 );
    point_set3D(&v[1],  1, -1, -1 );
    point_set3D(&v[2],  1,  -1, 1 );
    point_set3D(&v[3], -1,  -1, 1 );
    point_set3D(&v[4], 0, 0, 0);

    // front side
    point_copy(&tv[0], &v[0]);
    point_copy(&tv[1], &v[1]);
    point_copy(&tv[2], &v[4]);
    polygon_set(&side[0], 3, tv);

    // back side
    point_copy(&tv[0], &v[3]);
    point_copy(&tv[1], &v[2]);
    point_copy(&tv[2], &v[4]);
    polygon_set(&side[1], 3, tv);

    // bottom side
    polygon_set(&side[2], 4, &(v[0]));

    // left side
    point_copy(&tv[0], &v[0]);
    point_copy(&tv[1], &v[3]);
    point_copy(&tv[2], &v[4]);
    polygon_set(&side[3], 3, tv);

    // right side
    point_copy(&tv[0], &v[1]);
    point_copy(&tv[1], &v[2]);
    point_copy(&tv[2], &v[4]);
    polygon_set(&side[4], 3, tv); 

    pyra = module_create();
    module_scale(pyra, 20, 20, 20);

    for( i = 0; i<5; i++){
    	polygon_copy(&tpoly, &side[i]);
    	module_polygon(pyra, &tpoly);
    }

    return(pyra);
}

static Module* giza(){
	Module *giza, *p1, *p2, *p3;

	p1 = pyramid();
	p2 = pyramid();
	p3 = pyramid();

	module_module(giza, p1);
	module_module(giza, p2);
	module_module(giza, p3);

	return(giza);
}

int main(int argc, char *argv[]) {
	// initialize fields
	const int rows = 600*2;
	const int cols = 660*2;
	Image *src;
	int i;
	Module *cairo, *sand, *pyramids;
	Polygon p;
	Point pt[4];
	View3D view;
	Matrix vtm, gtm;
	DrawState *ds;
	float bodyWidth = 2.0;
	char command[256];
	float alpha;
	Color Blue = {{0.0, 0.0, 1.0}};

// grab command line argument to determine viewpoint
    // and set up the view structure
    if( argc > 1 ) {
        alpha = atof( argv[1] );
        if( alpha < 0.0 || alpha > 1.0 )
            alpha = 0.0;
        point_set3D( &(view.vrp), 120*alpha, 80*alpha, -80*alpha - (1.0-cos(alpha)*80) );
    } else {
		point_set3D( &(view.vrp), 300, 80, -80 );
    }
	// set up the view
	vector_set( &(view.vpn), -view.vrp.val[0], -view.vrp.val[1], 
		-view.vrp.val[2] );
	vector_set( &(view.vup), 0, 1, 0 );
	view.d = 10;
	view.du = 6;
	view.f = 1;
	view.b = 50;
	view.screenx = cols;
	view.screeny = rows;
	int r;

	printf("set up view\n");

	matrix_setView3D( &vtm, &view );
 	matrix_identity( &gtm );

 	sand = (Module*)sandscape();
 	pyramids = (Module*)giza();
 	cairo = (Module*)city();

	// create the image and drawstate
	src = image_create( rows, cols );
	image_fillColor(src, Blue);
	ds = drawstate_create();
	ds->shade = ShadeConstant;
	printf("created the image and drawstate\n");

	// draw scene
	module_draw(sand, &vtm, &gtm, ds, NULL, src );
	module_draw(pyramids, &vtm, &gtm, ds, NULL, src);
	module_draw(cairo, &vtm, &gtm, ds, NULL, src);
	
	printf("drew the scene\n");

	// write out the scene
	printf("Writing image\n");
	image_write( src, "egypt.ppm" );
	sprintf(command, "convert -scale %03dx%03d egypt.ppm egypt.ppm", cols/2, rows/2);
	system(command);

	// free the polygon data
	polygon_clear( &p );
	printf("polygon freed\n");

	// free the modules
	module_delete(sand);
	module_delete(pyramids);
	module_delete(cairo);

	printf("module freed\n");

	// free drawstate
	free(ds);
	printf("drawstate freed\n");

	// free image
	image_free( src );
	printf("image freed\n");

	return(0);
}


