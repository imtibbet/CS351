/*
  Astrid Moore (Bruce Maxwell, Ian Tibbetts)
  Fall 2014

  Test function for 3D image
 */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "graphics.h"


int main(int argc, char *argv[]) {
    const int rows = 500*2;
    const int cols = 500*2;
    Image *src;
    View3D view;
    Matrix vtm;
    Polygon side[5];
    Polygon tpoly;
    Point  tv[4];
    Point  v[8];
    Color  color[5], Black;
    int i;
    char command[256];
    color_set(&color[0], 0.7, 0.04, 0.05);
    color_set(&color[1], 1.0, 0.84, 0.35);
    color_set(&color[2], 0.1, 0.2, 0.5);
    color_set(&color[3], 0.43, 0.04, 0.004);
    color_set(&color[4], 0.33, 0.54, 0.21);
    color_set(&Black, 0.0, 0.0, 0.0);

    src = image_create( rows, cols );

    // color the background
    image_fillColor( src, color[1]);

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

    // grab command line argument to determine viewpoint
    // and set up the view structure
    if( argc > 1 ) {
        float alpha = atof( argv[1] );
        if( alpha < 0.0 || alpha > 1.0 )
            alpha = 0.0;
        point_set3D( &(view.vrp), 3*alpha, 2*alpha, -2*alpha - (1.0-alpha)*3 );
    } else {
        point_set3D( &(view.vrp), 3, 2, -2 );
    }
    vector_set( &(view.vpn), -view.vrp.val[0], -view.vrp.val[1], -view.vrp.val[2] );

    vector_set( &(view.vup), 0, 1, 0 );
    view.d = 1;  // focal length
    view.du = 2;
    view.dv = view.du * (float)rows / cols;
    view.f = 0; // front clip plane
    view.b = 4; // back clip plane
    view.screenx = cols;
    view.screeny = rows;

    matrix_setView3D( &vtm, &view );

    // create image
    src = image_create( rows, cols );

    // use a temporary polygon to transform stuff
    polygon_init( &tpoly );

    printf("Drawing Polygons\n");
    for(i=0;i<5;i++) {
        polygon_copy( &tpoly, &side[i] );
        matrix_xformPolygon( &vtm, &tpoly );

        // normalize by homogeneous coordinate before drawing
        polygon_normalize( &tpoly );
        polygon_draw( &tpoly, src, Black);
        polygon_drawFillB( &tpoly, src, color[i] );
    }

    printf("Writing image\n");
    image_write( src, "pyramid.ppm" );
    sprintf(command,"convert -scale %03dx%03d pyramid.ppm pyramid.ppm",cols/2,rows/2);
    system(command);
    
    image_free(src);

    return(0);
}
