/*
  Bruce Maxwell
  Fall 2014

  2D View test function
*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "graphics.h"

static Polygon *defineBatSymbol( float x, float y, float scale );
static Polygon *defineBatSymbol( float x, float y, float scale ){

	Point symPoints[21];
	
    point_set2D( &(symPoints[0]), x+0*scale, y-2.5*scale );
    point_set2D( &(symPoints[1]), x+1*scale, y-1.5*scale );
    point_set2D( &(symPoints[2]), x+2*scale, y-2.3*scale );
    point_set2D( &(symPoints[3]), x+3*scale, y-1.3*scale );
    point_set2D( &(symPoints[4]), x+4*scale, y-2.4*scale );
    point_set2D( &(symPoints[5]), x+7*scale, y-0*scale );
    point_set2D( &(symPoints[6]), x+3*scale, y+2.6*scale );
    point_set2D( &(symPoints[7]), x+2*scale, y+1*scale );
    point_set2D( &(symPoints[8]), x+1*scale, y+1*scale );
    point_set2D( &(symPoints[9]), x+0.8*scale, y+3*scale );
    point_set2D( &(symPoints[10]), x+0.6*scale, y+2.2*scale );

    point_set2D( &(symPoints[20]), x-1*scale, y-1.5*scale );
    point_set2D( &(symPoints[19]), x-2*scale, y-2.3*scale );
    point_set2D( &(symPoints[18]), x-3*scale, y-1.3*scale );
    point_set2D( &(symPoints[17]), x-4*scale, y-2.4*scale );
    point_set2D( &(symPoints[16]), x-7*scale, y-0*scale );
    point_set2D( &(symPoints[15]), x-3*scale, y+2.6*scale );
    point_set2D( &(symPoints[14]), x-2*scale, y+1*scale );
    point_set2D( &(symPoints[13]), x-1*scale, y+1*scale );
    point_set2D( &(symPoints[12]), x-0.8*scale, y+3*scale );
    point_set2D( &(symPoints[11]), x-0.6*scale, y+2.2*scale );
    
    return(polygon_createp(21,symPoints));
}

int main(int argc, char *argv[]) {
	const int rows = 600;
	const int cols = 800;
	const int Resolution = 50;
	Color Grey;
	Color dkGrey;
	Color Red;
	Color Blue;
	Color Black;
	Color Yellow;
	Point unitCircle[Resolution];
	Point fullEllipse[Resolution];
	Point halfEllipse[2*(Resolution/2)+2];
	Point unitSquare[4];
	Polygon *mount;
	Point lightCone[3];
	View2D view;
	Matrix vtm, ltm;
	int i, j, batIndex = 0;
	float vrpx = 0.0; 
	float vrpy = 0.0;
	float vdx = 10.0;
	float vxx = 1.0;
	float vxy = 0.0;
	float vxz = 0.0;
	Image *src;
	Color White;
	color_set(&White, 1.0, 1.0, 1.0);
 	Polygon *batCall[50];
 	Color batCallColor[50];

	color_set(&Grey, 180/255.0, 180/255.0, 183/255.0);
	color_set(&dkGrey, 140/255.0, 140/255.0, 143/255.0);
	color_set(&Red, 250/255.0, 40/255.0, 40/255.0);
	color_set(&Blue, 0.0980392, 0.0980392, 0.439216);
	color_set( &Black, 0.0, 0.0, 0.0 );
	color_set( &Yellow, 0.9, 0.9, 0.4 );

	src = image_create( rows, cols );
	
	// grab command line argument to determine viewpoint
	// and set up the view structure
	if( argc == 2 ) {
		vrpx = vrpy = atof( argv[1] );
	} else {
		if( argc > 2 ) {
			vrpx = atof( argv[1] );
			vrpy = atof( argv[2] );
		} 
		if( argc > 3 ) {
			vdx = atof( argv[3] );
			if(vdx <= 0.0){
				vdx = 50.0;
			}
		}
		if( argc > 4 ) {
			vxx = cos( atof( argv[4] ) * M_PI/180.0);
			vxy = sin( atof( argv[4] ) * M_PI/180.0);
		}
	}
	
	point_set2D( &(view.vrp), vrpx, vrpy );
	view.dx = vdx;
	vector_set( &(view.x), vxx, vxy, vxz );
	view.screenx = cols;
	view.screeny = rows;

	matrix_setView2D( &vtm, &view );
	printf("vtm:\n");
	matrix_print(&vtm, stdout);

	// make a list of points that form the unit circle
	for(i=0;i<Resolution;i++) {
		point_set2D(&(unitCircle[i]), 
		sin( i * 2.0 * M_PI / (float)Resolution), 
		cos( i * 2.0 * M_PI / (float)Resolution));
	}
	// set up the unit square
	point_set2D(&(unitSquare[0]), 0-0.5, 0-0.5);
	point_set2D(&(unitSquare[1]), 1-0.5, 0-0.5);
	point_set2D(&(unitSquare[2]), 1-0.5, 1-0.5);
	point_set2D(&(unitSquare[3]), 0-0.5, 1-0.5);
	
	// sky projection
	point_set2D(&(lightCone[0]), 0, 0);
	point_set2D(&(lightCone[1]), -15, 3);
	point_set2D(&(lightCone[2]), -15, -3);
	batCall[batIndex] = polygon_createp(3, lightCone);
	batCallColor[batIndex++] = Yellow;
	batCall[batIndex] = polygon_createp(Resolution, unitCircle);
	// move it 5 to the left along the X-axis
	matrix_identity(&ltm);
	matrix_scale2D(&ltm, 3, 3);
	matrix_translate2D(&ltm, -15, 0);
	// transform the polygon points using LTM
	matrix_xformPolygon(&ltm, batCall[batIndex]);
	batCallColor[batIndex++] = Yellow;
	batCall[batIndex] = defineBatSymbol( -15, 0, 0.3 );
	batCallColor[batIndex++] = Black;
	
    // back of projector
	matrix_identity(&ltm);
	// stretch to form ellipse
	matrix_scale2D(&ltm, 1, 2);
	// move it 3 to the right along the X-axis
	matrix_translate2D(&ltm, 2, 0);
	// transform the circle points using LTM
	for(i=0;i<=Resolution/2;i++) {
		matrix_xformPoint(&ltm, &(unitCircle[i]), &(halfEllipse[i]));
	}
	j=i;
	// continue part of the way up the projector
	matrix_identity(&ltm);
	// move it 2 to the right along the X-axis
	matrix_translate2D(&ltm, 1, 0);
	matrix_xformPoint(&ltm, &(halfEllipse[i-1]), &(halfEllipse[i]));
	// stretch to form ellipse
	matrix_scale2D(&ltm, 1, 2);
	while(j>=0) {
		matrix_xformPoint(&ltm, &(unitCircle[j--]), &(halfEllipse[i++]));
	}
	// add the back of projector
	batCall[batIndex] = polygon_createp(2*(Resolution/2)+2, halfEllipse);
	batCallColor[batIndex++] = dkGrey;
	
	//body of projector
	for(i=0;i<2;i++){
		// gap of projector
		batCall[batIndex] = polygon_create();
		polygon_copy(batCall[batIndex], batCall[batIndex-1]);
		// move it 1 to the left along the X-axis
		matrix_identity(&ltm);
		matrix_translate2D(&ltm, -1, 0);
		// transform the polygon points using LTM
		matrix_xformPolygon(&ltm, batCall[batIndex]);
		// add the back of projector
		batCallColor[batIndex++] = Yellow;
	
		// bar of projector
		batCall[batIndex] = polygon_create();
		polygon_copy(batCall[batIndex], batCall[batIndex-1]);
		// move it 1 to the left along the X-axis
		matrix_identity(&ltm);
		matrix_translate2D(&ltm, -1, 0);
		// transform the polygon points using LTM
		matrix_xformPolygon(&ltm, batCall[batIndex]);
		// add the back of projector
		batCallColor[batIndex++] = dkGrey;
	}
	
	// front of projector
	matrix_identity(&ltm);
	// stretch to form ellipse
	matrix_scale2D(&ltm, 1, 2);
	for(i=0;i<Resolution;i++) {
		matrix_xformPoint(&ltm, &(unitCircle[i]), &(fullEllipse[i]));
	}
	batCall[batIndex] = polygon_createp(Resolution, fullEllipse);
	// move it 2 to the left along the X-axis
	matrix_identity(&ltm);
	matrix_translate2D(&ltm, -3, 0);
	// transform the polygon points using LTM
	matrix_xformPolygon(&ltm, batCall[batIndex]);
	batCallColor[batIndex++] = Yellow;
	
	// bat symbol
	batCall[batIndex] = defineBatSymbol( 0, 0, 0.2 );
	// move it 2 to the left along the X-axis
	matrix_identity(&ltm);
	matrix_scale2D(&ltm, 0.7, 1);
	matrix_translate2D(&ltm, -3, 0);
	// transform the polygon points using LTM
	matrix_xformPolygon(&ltm, batCall[batIndex]);
	batCallColor[batIndex++] = Black;
	
	// rotate the whole scene to point at the sky
	matrix_identity(&ltm);
	matrix_rotateZ(&ltm, cos(-M_PI/6.0), sin(-M_PI/6.0));
	for(i=0;i<batIndex;i++) {
		matrix_xformPolygon(&ltm, batCall[i]);
	}

	// mount
	mount = polygon_createp(4, unitSquare);
	matrix_identity(&ltm);
	matrix_scale2D(&ltm, 1, 4);
	matrix_translate2D(&ltm, 0, -2);
	// transform the polygon points using LTM
	matrix_xformPolygon(&ltm, mount);
	
	image_fillColor( src, Blue );
	
	// draw projection
	for(i=0;i<batIndex;i++) {

		// multiply the polygon by the view transformation matrix
		matrix_xformPolygon(&vtm, batCall[i]);

		// draw the polygon
		polygon_drawFill(batCall[i], src, batCallColor[i]);
	}
		
	// multiply the mount by the view transformation matrix
	matrix_xformPolygon(&vtm, mount);
	// draw the polygon
	polygon_drawFill(mount, src, Black);
	
	printf("writing file\n");
	image_write( src, "twodpan.ppm" );

	// cleanup
	image_free( src );

	return(0);
}
