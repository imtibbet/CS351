/*
 * Author: Ian Tibbetts and Astrid Moore
 * Date: 9/22/14
 *
 * The color function implementations
 */


/* 
 * Sets the first two values of the vector to x and y. 
 * Sets the third value to 0.0 and the fourth value to 1.0 
 */
void point_set2D(Point *p, double x, double y){
	p->val[0] = x;
	p->val[1] = y;
	p->val[2] = 0.0;
	p->val[3] = 1.0;
}

/*
 * Set the point's values to x and y and z. 
 * Sets the homogeneous coordinate to 1.0 
 */
void point_set3D(Point *p, double x, double y, double z){
	p->val[0] = x;
	p->val[1] = y;
	p->val[2] = z;
	p->val[3] = 1.0;
}

/*
 * Set the four values of the vector to x, y, z, and h, respectively. 
 */
void point_set(Point *p, double x, double y, double z, double h){
	p->val[0] = x;
	p->val[1] = y;
	p->val[2] = z;
	p->val[3] = h;
}

/** Copy the point data structure. **/
void point_copy(Point *to, Point *from){
	to->val[0] = from->val[0];
	to->val[1] = from->val[1];
	to->val[2] = from->val[2];
	to->val[3] = from->val[3];
}

/** Draw the point into src using Color c. **/
void point_draw(Point *p, Image *src, Color c){
	image_setColor( src, p->val[0], p->val[1], c );
}

/** Draw the p into src using FPixel c. **/
void point_drawf(Point *p, Image *src, FPixel c){
	image_setf(src, p->val[0], p->val[1], c);
}

