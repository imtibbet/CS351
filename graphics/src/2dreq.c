/*
 Astrid Moore (Bruce Maxwell, Ian Tibbetts)
 Fall 2014
 
 2D View - Fish
 */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "graphics.h"

static Polygon *defineFish( int e, float x, float y, Image *src, float scale, Color c, Color fins );
static Polygon *defineFish( int e, float x, float y, Image *src, float scale, Color c, Color fins ){
    const int nPoints = 500;
    Point pt[nPoints];
    float i;
    Circle body, eye;
    Polygon fin, tooth;

    Color White, Black;
    color_set(&White, 1.0, 1.0, 1.0);
    color_set(&Black, 0.0, 0.0, 0.0);

    // create lateral fins
    point_set2D(&(pt[0]), x - scale*1.5, y - scale/5);
    point_set2D(&(pt[1]), x - scale*1.5, y + scale/5);
    point_set2D(&(pt[2]), x - scale/2, y);
    polygon_set(&fin, 3, &(pt[0]));
    polygon_drawFillB(&fin, src, fins);
    point_set2D(&(pt[3]), x + scale*1.5, y + scale/5);
    point_set2D(&(pt[4]), x + scale*1.5, y - scale/5);
    point_set2D(&(pt[5]), x + scale/2, y);
    polygon_set(&fin, 3, &(pt[3]));
    polygon_drawFillB(&fin, src, fins);

    // create body - circle
    point_set2D(&(pt[6]), x, y );
    circle_set(&body, pt[6], scale);
    circle_drawFill(&body, src, c);
    
    // create fins - triangles
    point_set2D(&(pt[7]), x, y - scale/2);
    point_set2D(&(pt[8]), x - scale/8, y - scale*1.8);
    point_set2D(&(pt[9]), x + scale/8, y - scale*1.8);
    polygon_set(&fin, 3, &(pt[7]));
    polygon_drawFillB(&fin, src, fins);

    // create eyes w/ interactive pupils - circles 
    point_set2D(&(pt[10]), x - scale/5*2, y);
    circle_set(&eye, pt[10], scale/5);
    circle_drawFill(&eye, src, White);
    point_set2D(&(pt[11]), x - scale/5*2, 250);
    if ( e == 1 ){
        circle_set(&eye, pt[11], scale/12);
        circle_drawFill(&eye, src, Black);
    }
    else {
        circle_set(&eye, pt[11], scale/6.2);
        circle_drawFill(&eye, src, Black);
    }
    point_set2D(&(pt[12]), x + scale/5*2, y);
    circle_set(&eye, pt[12], scale/5);
    circle_drawFill(&eye, src, White);        
    point_set2D(&(pt[13]), x + scale/5*2, y);
    if ( e == 1 ){
        circle_set(&eye, pt[13], scale/12);
        circle_drawFill(&eye, src, Black);
    }
    else {
        circle_set(&eye, pt[13], scale/6.2);
        circle_drawFill(&eye, src, Black);
    }

    // create mouth
    for ( i = x - scale/5*3; i < x + scale/5*1.5; i = i + 10 ){
        point_set2D(&(pt[14]), i, y + scale/5*3.5);
        point_set2D(&(pt[15]), i + scale/5, y + scale/5*2.3);
        point_set2D(&(pt[16]), i + scale/5*2, y + scale/5*3.5);
        polygon_set(&tooth, 3, &(pt[14]));
        polygon_drawFillB(&tooth, src, White);
    }
    return(0);
}

int main(int argc, char *argv[]) {
    const int nFrames = 120;
    const int rows = 500;
    const int cols = 500;
    Image *src;
    View2D view;
    Matrix vtm;
    char filename[256];
    int i;
    Color Grey, dkGrey, dkBlue, ltGreen, dkGreen;
    color_set(&Grey, 180.0/255.0, 180.0/255.0, 183.0/255.0);
    color_set(&dkBlue, 0.1, 0.2, 0.3);
    color_set(&dkGreen, 0.28, 0.4, 0.16);
    color_set(&ltGreen, 0.44, 0.65, 0.02);
    color_set(&dkGrey, 0.3, 0.3, 0.3);

    src = image_create( rows, cols );

    // color the background
    image_fillColor( src, dkBlue );

        // set up a view centered on (1.5, 1.5) with x pointing right
    point_set2D( &(view.vrp), 1.5, 1.5 );
    view.dx = 1.0;
    vector_set( &(view.x), 1.0, 0.0, 0.0 );
    view.screenx = cols;
    view.screeny = rows;

    matrix_setView2D( &vtm, &view );
    printf("vtm:\n");
    matrix_print(&vtm, stdout);

    // draw fish
    for ( i = 0; i < nFrames; i++){
        color_set(&ltGreen, 0.44/(nFrames-i),  0.65/(nFrames-i), 0.02/(nFrames-i));
        color_set(&dkGreen, 0.28/(nFrames-i), 0.4/(nFrames-i), 0.16/(nFrames-i));
        defineFish(0, 250, 250, src, 50 + i, dkGreen, ltGreen);
        if (i > 80){
            defineFish(1, 250, 250, src, 50, Grey, dkGrey);
        }
        else {
            defineFish(0, 250, 250, src, 50, Grey, dkGrey);
        }
        sprintf(filename, "frame-%04d.ppm", i );
        image_write( src, filename );
    }

    printf("wrote image file\n");
    
    // cleanup
    image_free( src );

    printf("converting to gif...\n");
    system("convert -delay 10 -loop 0 frame-*.ppm 2dreq.gif");
    system("rm frame-*.ppm");
    system("animate 2dreq.gif");
    
    return(0);
}
