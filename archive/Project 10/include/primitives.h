#ifndef PRIMITIVES_H

#define PRIMITIVES_H

typedef struct {
	double val[4]; // four element vector of doubles
} Point;

typedef Point Vector;

typedef struct {
	int zBuffer; // whether to use the z-buffer, should default to true (1)
	Point a; // starting point
	Point b; // ending point
} Line;

typedef struct {
	double r; // radius,
	Point c; // center
} Circle;

typedef struct {
	double ra; // major axis radius
	double rb; // minor axis radius
	Point c; // center
	double a; // (optional) angle of major axis relative to the X-axis
} Ellipse;

typedef struct {
	int zBuffer; // whether to use the z-buffer; should default to true (1)
	int numVertex; // Number of vertices
	Point *vertex; // vertex information
} Polyline;

typedef struct {
	int oneSided; // whether to consider the polygon one-sided (1) or two-sided (0) for shading
	int zBuffer; // whether to use the z-buffer; should default to true (1)
	int nVertex; // Number of vertices
	Point *vertex; // vertex information
	Color *color; // color information for each vertex.
	Vector *normal; // surface normal information for each vertex
} Polygon;

// Point functions

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

/** Print the point to the stream designated by FILE pointer **/
void point_print(Point *p, FILE *fp);

/** Normalize the point. Do not modify the homogeneous coordinate. **/
void point_normalize(Point *p);

/** average p1 and p2 x, y, z values and put results in dest, set homogeneous to 1 **/
void point_avg(Point *dest, Point *p1, Point *p2);

// Line functions

/** Initialize a 2D line. **/
void line_set2D(Line *l, double x0, double y0, double x1, double y1);

/** Initialze a line to ta and tb. **/
void line_set(Line *l, Point ta, Point tb);

/** Set the z-buffer flag to the given value. **/
void line_zBuffer(Line *l, int flag);

int line_normalize(Line *l);

/** Copy the line data structure. **/
void line_copy(Line *to, Line *from);

/** Draw the line into src using Color c. **/
void line_draw(Line *l, Image *src, Color c);

/** Print the line to the stream designated by FILE pointer **/
void line_print(Line *p, FILE *fp);

// Circle functions

/** Initialize to center tc and radius tr. **/
void circle_set(Circle *c, Point tc, double tr);

/** Draw the circle into src using color c. **/
void circle_draw(Circle *circ, Image *src, Color c);

/** Draw a filled circled into src using color c. **/
void circle_drawFill(Circle *circ, Image *src, Color c);

/** Draw the specified octant range of a circle into src using color c. **/
void circle_drawoct(Circle *circ, Image *src, Color c, int startOct, int endOct);


// Elipse functions

/** Initialize an ellipse to location tc and radii ta and tb. **/
void ellipse_set(Ellipse *e, Point tc, double ta, double tb);

/** Draw into src using color c. **/
void ellipse_draw(Ellipse *e, Image *src, Color c);

/** Draw a filled ellipse into src using color c. **/
void ellipse_drawFill(Ellipse *e, Image *src, Color c);

/** Draw the specified octant range of a circle into src using color c. **/
void ellipse_drawquad(Ellipse *e, Image *src, Color c, int startQuad, int endQuad);

// Polyline functions

/* Returns an allocated Polyline pointer initialized so that 
* numVertex is 0 and vertex is NULL. */
Polyline *polyline_create(void);

/* Returns an allocated Polyline pointer with the vertex list initialized 
* to the points in vlist. */
Polyline *polyline_createp(int numV, Point *vlist);

/* Frees the internal data and the Polyline pointer. */
void polyline_free(Polyline *p);

/* Initializes the pre-existing Polyline to an empty Polyline. */
void polyline_init(Polyline *p);

/* Initializes the vertex list to the points in vlist. De-allocates/allocates
* the vertex list for p, as necessary. */
void polyline_set(Polyline *p, int numV, Point *vlist);

/* Frees the internal data for a Polyline, if necessary, and sets numVertex
* to 0 and vertex to NULL. */
void polyline_clear(Polyline *p);

/* Sets the z-buffer flag to the given value. */
void polyline_zBuffer(Polyline *p, int flag);

/* De-allocates/allocates space as necessary in the destination Polyline data
* structure and copies the vertex data from the source polyline (from) to the 
* destination (to). */
void polyline_copy (Polyline *to, Polyline *from);

/* Prints Polyline data to the stream designated by the FILE pointer. */
void polyline_print(Polyline *p, FILE *fp);

/* Draw the Polyline using color c. */
void polyline_draw(Polyline *p, Image *src, Color c);

/*
 * normalize the x and y values of each vertex by the homogeneous coord
 */
void polyline_normalize( Polyline *p);

// Polygon

/*
 * returns an allocated Polygon pointer initialized so that
 * numVertex is 0 and vertex is NULL.
 */
Polygon *polygon_create(void);

/*
 * returns an allocated Polygon pointer with the vertex list
 * initialized to a copy of the points in vlist.
 */
Polygon *polygon_createp(int numV, Point *vlist);

/*
 * frees the internal data for a Polygon and the Polygon pointer.
 * The functions polygon init, polygon set, and polygon
 * clear work on a pre-existing Polygon data structure
 * and manage only the memory required for the vertex list.
 */
void polygon_free(Polygon *p);

/*
 * initializes the existing Polygon to an empty Polygon.
 */
void polygon_init(Polygon *p);

/*
 * initializes the vertex array to the points in vlist.
 */
void polygon_set(Polygon *p, int numV, Point *vlist);

/*
 * frees the internal data and resets the fields.
 */
void polygon_clear(Polygon *p);

/*
 * sets the oneSided field to the value
 */
void polygon_setSided(Polygon *p, int oneSided);

/*
 * initializes the color array to the colors in clist
 */
void polygon_setColors(Polygon *p, int numV, Color *clist);

/*
 * initializes the normal array to the vectors in nlist.
 */
void polygon_setNormals(Polygon *p, int numV, Vector *nlist);

/*
 * initializes the vertex list to the points in vlist, the colors to the colors
 * in clist, the normals to the vectors in nlist, and the zBuffer and oneSided
 * flags to their respectively values.
 */
void polygon_setAll(Polygon *p, int numV, Point *vlist, Color *clist, 
	Vector *nlist, int zBuffer, int oneSided);
	
/*
 * sets the z-buffer flag to the given value.
 */
void polygon_zBuffer(Polygon *p, int flag);

/*
 * De-allocates/allocates space and copies the vertex and 
 * color data from one polygon to the other.
 */
void polygon_copy(Polygon *to, Polygon *from);

/*
 * prints polygon data to the stream designated by the FILE pointer.
 */
void polygon_print(Polygon *p, FILE *fp);

/*
 * normalize the x and y values of each vertex by the homogeneous coord
 */
int polygon_normalize( Polygon *p);

/*
 * draw the outline of the polygon using color c.
 */
void polygon_draw(Polygon *p, Image *src, Color c);

/*
 * draw the filled polygon using color c with the scanline rendering algorithm.
 */
void polygon_drawFill(Polygon *p, Image *src, void *drawstate);

/*
 * draw the filled polygon using color c with the Barycentric coordinates algorithm.
 */
void polygon_drawFillB(Polygon *p, Image *src, Color c);

/*
 * draw the filled polygon using the given DrawState. 
 * The shade field of the DrawState determines how the polygon should be rendered. 
 * The Lighting parameter should be NULL unless you are doing Phong shading
 */
void polygon_drawShade(Polygon *p, Image *src, void *drawstate, void *lighting);

/*
 * For the Shade-Flat and ShadeGouraud cases of the shade field of DrawState, 
 * calculate colors at each vertex and create and fill out the color array of 
 * the Polygon data structure. For ShadeFlat, use the average surface normal and
 * average polygon location to calculate one color and set the color at each 
 * vertex to the calculated value. 
 * For ShadeGouraud use the surface normals and locations of each vertex
 */
void polygon_shade(Polygon *p, void *lighting, void *drawstate);


#endif
