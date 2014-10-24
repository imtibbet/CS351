/*
  Ian Tibbetts and Astrid Moore (Bruce Maxwell)
  Fall 2014
 */
#include <stdio.h>
#include <stdlib.h>
#include "graphics.h"

int main(int argc, char *argv[]) {
  View3D view;
  Matrix vtm;
  Matrix gtm;
  Module *cube;
  DrawState *ds;
  Image *src;
  Color Blue;
  
  color_set(&Blue, 0.0, 0.0, 1.0);

  // setup gtm
  matrix_identity( &gtm );

  // setup vtm
  point_set3D( &(view.vrp), 5, 5, 5 );
  vector_set( &(view.vpn), -5, -5, -5 );
  vector_set( &(view.vup), 0, 1, 0 );
  view.d = 1;
  view.du = 2;
  view.screenx = 640;
  view.screeny = 360;
  matrix_setView3D( &vtm, &view );
  printf("set up vtm\n");
	
	// cube module
	cube = module_create();
	module_color(cube, &Blue);
	module_rotateX(cube, cos(M_PI/6), sin(M_PI/6));
	module_rotateZ(cube, cos(M_PI/6), sin(M_PI/6));
	module_cube(cube, 0);
	

	// create the image and draw the module
  src = image_create( view.screeny, view.screenx );
  ds = drawstate_create(); // default color is white
  module_draw( cube, &vtm, &gtm, ds, NULL, src );
  printf("created the image and drew the module\n");

	// write out the image
  image_write( src, "cube.ppm" );
  printf("wrote out the image\n");

	// free drawstate
  free( ds );

	// free image
  image_free( src );

  return(0);
}
