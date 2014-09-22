#ifndef COLOR_H

#define COLOR_H

typedef struct {
	double val[4];
} Point;

/** Sets the first two values of the vector to x and y. Sets the third value to 0.0 and the fourth value to 1.0 **/
void point_set2D(Point *p, double x, double y);

/** Set the point's values to x and y and z. Sets the homogeneous coordinate to 1.0 **/
void point_set3D(Point *p, double x, double y, double z);

/** Set the four values of the vector to x, y, z, and h, respectively. **/
void point_set(Point *p, double x, double y, double z, double h);

/** Copy the point data structure. **/
void point_copy(Point *to, Point *from);

/** Draw the point into src using Color c. **/
void point_draw(Point *p, Image *src, Color c);

/** Draw the p into src using FPixel c. **/
void point_drawf(Point *p, Image *src, FPixel c);


typedef struct {
	int zBuffer;
	Point a;
	Point b;
} Line;


typedef struct {
	double r;
	Point c;
} Circle;


typedef struct {
	double ra;
	double rb;
	Point c;
	double a;
} Ellipse;


typedef struct {
	int zBuffer;
	int numVertex;
	Point *vertex;
} Polyline;

#endif
