/*
 * Author: Ian Tibbetts and Astrid Moore
 * Date: 9/19/14
 *
 * The bezier curve and surfaces
 */

#include "graphics.h"

/*
 * sets the zbuffer flag to 1 and the curve points to the X-axis between 0 and 1.
 */
void bezierCurve_init(BezierCurve *b){
	if(!b){
		printf("Null passed to bezierCurve_init\n");
		return;
	}
	b->zBuffer = 1;
	point_set2D(&(b->c[0]), 0, 0);
	point_set2D(&(b->c[1]), 0.3, 0);
	point_set2D(&(b->c[2]), 0.6, 0);
	point_set2D(&(b->c[3]), 1, 0);
}

/*
 * sets the zbuffer flag to 1 and the surface to the 
 * X-Z plane between (0, 0) and (1, 1).
 */
void bezierSurface_init(BezierSurface *b){
	if(!b){
		printf("Null passed to bezierSurface_init\n");
		return;
	}
	b->zBuffer = 1; 
	
	point_set2D(&(b->c[0][0]), 0, 	0);
	point_set2D(&(b->c[1][0]), 0.3, 0);
	point_set2D(&(b->c[2][0]), 0.6, 0);
	point_set2D(&(b->c[3][0]), 1, 	0);
	
	point_set2D(&(b->c[0][1]), 0, 	0.3);
	point_set2D(&(b->c[1][1]), 0.3, 0.3);
	point_set2D(&(b->c[2][1]), 0.6, 0.3);
	point_set2D(&(b->c[3][1]), 1, 	0.3);
	
	point_set2D(&(b->c[0][2]), 0, 	0.6);
	point_set2D(&(b->c[1][2]), 0.3, 0.6);
	point_set2D(&(b->c[2][2]), 0.6, 0.6);
	point_set2D(&(b->c[3][2]), 1, 	0.6);
	
	point_set2D(&(b->c[0][3]), 0, 	1);
	point_set2D(&(b->c[1][3]), 0.3, 1);
	point_set2D(&(b->c[2][3]), 0.6, 1);
	point_set2D(&(b->c[3][3]), 1, 	1);
}

/*
 * prints the BezierCurve
 */
void bezierCurve_print(BezierCurve *b){
	if(!b){
		printf("Null passed to bezierCurve_print\n");
		return;
	}
	int i;
	printf("bezier curve:\n");
	for(i=0;i<4;i++){
		point_print(&(b->c[i]), stdout);
	}
}

/*
 * prints the BezierSurface
 */
void bezierSurface_print(BezierSurface *b){
	if(!b){
		printf("Null passed to bezierSurface_print\n");
		return;
	}
	int i, j;
	printf("bezier surface:\n");
	for(i=0;i<4;i++){
		for(j=0;j<4;j++){
			point_print(&(b->c[i][j]), stdout);
		}
	}
}

/*
 * sets the control points of the BezierCurve to the four points in the vlist array.
 */
void bezierCurve_set(BezierCurve *b, Point *vlist){
	if(!b || !vlist){
		printf("Null passed to bezierCurve_set\n");
		return;
	}
	b->c[0] = vlist[0];
	b->c[1] = vlist[1];
	b->c[2] = vlist[2];
	b->c[3] = vlist[3];
}

/*
 * sets the control points of the BezierSurface to the 16 points in the vlist array.
 */
void bezierSurface_set(BezierSurface *b, Point *vlist){
	if(!b || !vlist){
		printf("Null passed to bezierSurface_set\n");
		return;
	}
	b->c[0][0] = vlist[0];
	b->c[1][0] = vlist[1];
	b->c[2][0] = vlist[2];
	b->c[3][0] = vlist[3];
	
	b->c[0][1] = vlist[4];
	b->c[1][1] = vlist[5];
	b->c[2][1] = vlist[6];
	b->c[3][1] = vlist[7];
	
	b->c[0][2] = vlist[8];
	b->c[1][2] = vlist[9];
	b->c[2][2] = vlist[10];
	b->c[3][2] = vlist[11];
	
	b->c[0][3] = vlist[12];
	b->c[1][3] = vlist[13];
	b->c[2][3] = vlist[14];
	b->c[3][3] = vlist[15];
}

/*
 * sets the z-buffer flag to the given value.
 */
void bezierCurve_zBuffer(BezierCurve *p, int flag){
	if(!p){
		printf("Null passed to bezierCurve_zBuffer\n");
		return;
	}
	p->zBuffer = flag;
}

/*
 * sets the z-buffer flag to the given value.
 */
void bezierSurface_zBuffer(BezierCurve *p, int flag){
	if(!p){
		printf("Null passed to bezierSurface_zBuffer\n");
		return;
	}
	p->zBuffer = flag;

}

/*
 * draws the Bezier curve, given in screen coordinates, 
 * into the image using the given color. The function should be adaptive
 * so that it uses an appropriate number of line segments to draw the curve.
 */
void bezierCurve_draw(BezierCurve *b, Image *src, Color c){
	int i, j;
	float threshold = 10*10;
	float curdim, maxdim;
	Line templine;
	Point deCast[4];
	Point order1[3];
	Point order2[2];
	Point order3;
	BezierCurve tempbez;
	
	if(!b || !src){
		printf("Null passed to bezierCurve_draw\n");
		return;
	}
	
	// compute maximum dimension among 4 control points, either dx or dy
	curdim = b->c[0].val[0] - b->c[1].val[0];
	curdim = maxdim = curdim*curdim;
	for(i=0;i<3;i++){
		for(j=i+1;j<4;j++){
			// dx
			curdim = b->c[i].val[0] - b->c[j].val[0];
			curdim = curdim*curdim;
			if(curdim > maxdim)
				maxdim = curdim;
			// dy
			curdim = b->c[i].val[1] - b->c[j].val[1];
			curdim = curdim*curdim;
			if(curdim > maxdim)
				maxdim = curdim;
		}
	}
	
	// if bounding box is less than threshold, draw lines between control points
	if(maxdim < threshold){
		for(i=0;i<3;i++){
			line_set(&templine, b->c[i], b->c[i+1]);
			line_draw(&templine, src, c);
		}
	}
	
	// otherwise, recursively draw both halves using de Casteljau algorithm
	else{
		// compute all avg points for 3 orders, down to just one point 3rd order
		point_avg(&(order1[0]), &(b->c[0]), &(b->c[1]));
		point_avg(&(order1[1]), &(b->c[1]), &(b->c[2]));
		point_avg(&(order1[2]), &(b->c[2]), &(b->c[3]));
		point_avg(&(order2[0]), &(order1[0]), &(order1[1]));
		point_avg(&(order2[1]), &(order1[1]), &(order1[2]));
		point_avg(&order3, &(order2[0]), &(order2[1]));
		
		// left half curve has first point of each order as control points
		deCast[0] = b->c[0];
		deCast[1] = order1[0];
		deCast[2] = order2[0];
		deCast[3] = order3;
		bezierCurve_set(&tempbez, &(deCast[0]));
		bezierCurve_draw(&tempbez, src, c);
		
		// right half curve has last point of each order as control points
		deCast[0] = order3;
		deCast[1] = order2[1];
		deCast[2] = order1[2];
		deCast[3] = b->c[3];
		bezierCurve_set(&tempbez, &(deCast[0]));
		bezierCurve_draw(&tempbez, src, c);
	}
}
