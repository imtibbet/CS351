#ifndef TRANSFORM_H

#define TRANSFORM_H

typedef struct {
	float m[4][4];
} Matrix;

typedef Point Vector;

typedef struct {

	// 2-D point indicating the center of the view rectangle in world coordinates
	Point vrp;
	
	// orientation angle up from +x in degrees
	Vector x;
	
	// width of the view
	double dx;
	
	// Size of the desired image in pixels
	int screenx;
	int screeny;
} View2D;

typedef struct {

	// 3-D point indicating the origin of the view reference coordinates
	Point vrp; 
	
	//// 3-D vector indicating the direction in which the viewer is looking
	Vector vpn;
	 
	// 3-D vector indicating the UP direction on the view plane. 
	//The only restriction is that it cannot be parallel to the view plane normal.
	Vector vup;  
	
	// distance in the negative VPN direction at which 
	// the center of projection is located
	double d;
	
	// extent of view plane around the VRP, 
	// expressed in world coordinate distances
	double du;
	double dv; // compute this to ensure ratio with screen x and y correct
	
	// front and back clip planes expressed as distances along the positive VPN
	// F>=0 and F<B
	double f;
	double b;
	
	// Size of the desired image in pixels
	int screenx;
	int screeny;
} View3D;

// vector

/*
 * Set the Vector to (x, y, z, 0.0)
 */
void vector_set(Vector *v, double x, double y, double z);

/*
 * Print out the Vector to stream fp in a pretty form
 */
void vector_print(Vector *v, FILE *fp);

/*
 * Returns the Euclidean length of the vector, assuming the homogeneous coordinate is 1.0
 */
double vector_length(Vector *v);

/*
 * Normalize the Vector to unit length. Do not modify the homogeneous coordinate.
 */
void vector_normalize(Vector *v);

/*
 * Returns the scalar product of a and b
 */
double vector_dot(Vector *a, Vector *b);

/*
 * Calculates the the cross product (vector product) of a and b
 * and puts the result in c
 */
void vector_cross(Vector *a, Vector *b, Vector *c); 

// 2D matrix

/*
 * Print out the matrix in a nice 4x4 arrangement with a blank line below.
 */
void matrix_print(Matrix *m, FILE *fp);

/*
 * Set the matrix to all zeros.
 */
void matrix_clear(Matrix *m);

/*
 * Set the matrix to the identity matrix
 */
void matrix_identity(Matrix *m);
 
/*
 * Return the element of the matrix at row r, column c. 
 */
double matrix_get(Matrix *m, int r, int c);

/*
 * Set the element of the matrix at row r, column c to v.
 */
void matrix_set(Matrix *m, int r, int c, double v);

/*
 * Copy the src matrix into the dest matrix.
 */
void matrix_copy(Matrix *dest, Matrix *src);

/*
 * Transpose the matrix m in place.
 */
void matrix_transpose(Matrix *m);

/*
 * Multiply left and right and put the result in m
 * Make sure that the function is written so that the result matrix 
 * can also be the left or right matrix
 */
void matrix_multiply(Matrix *left, Matrix *right, Matrix *m);

/*
 * Transform the point p by the matrix m and put the result in q. 
 * For this function, p and q need to be different variables.
 */
void matrix_xformPoint(Matrix *m, Point *p, Point *q);

/*
 * Transform the vector p by the matrix m and put the result in q. 
 * For this function, p and q need to be different variables.
 */
void matrix_xformVector(Matrix *m, Vector *p, Vector *q);

/*
 * Transform the points and surface normals (if they exist) 
 * in the Polygon p by the matrix m.
 */
void matrix_xformPolygon(Matrix *m, Polygon *p);

/*
 * Transform the points in the Polyline p by the matrix m.
 */
void matrix_xformPolyline(Matrix *m, Polyline *p);

/*
 * Transform the points in line by the matrix m.
 */
void matrix_xformLine(Matrix *m, Line *line);

/*
 * Premultiply the matrix by a scale matrix parameterized by sx and sy
 */
void matrix_scale2D(Matrix *m, double sx, double sy);

/*
 * Premultiply the matrix by a Z-axis rotation matrix parameterized by
 * cos(t) and sin(t), where t is the angle of rotation about the Z-axis
 */
void matrix_rotateZ(Matrix *m, double cth, double sth);

/*
 * Premultiply the matrix by a 2D translation matrix parameterized by tx, ty
 */
void matrix_translate2D(Matrix *m, double tx, double ty);

/*
 * Premultiply the matrix by a 2D shear matrix parameterized by shx, shy
 */
void matrix_shear2D(Matrix *m, double shx, double shy);
 
// 3D matrix

/*
 * Premultiply the matrix by a translation matrix parameterized by tx,ty,tz
 */
void matrix_translate(Matrix *m, double tx, double ty, double tz);

/*
 * Premultiply the matrix by a scale matrix parameterized by sx,sy,sz
 */
void matrix_scale(Matrix *m, double sx, double sy, double sz);

/*
 * premultiply the matrix by a X-axis rotation matrix parameterized by
 * cos(t) and sin(t), where t is the angle of rotation about the x axis
 */
void matrix_rotateX(Matrix *m, double cth, double sth);

/*
 * premultiply the matrix by a Y-axis rotation matrix parameterized by
 * cos(t) and sin(t), where t is the angle of rotation about the y axis
 */
void matrix_rotateY(Matrix *m, double cth, double sth);

/*
 * premultiply the matrix by a XYZ-axis rotation matrix parameterized by
 * u,v,w where the three vectors represent an orthonormal 3D basis
 */
void matrix_rotateXYZ(Matrix *m, Vector *u, Vector *v, Vector *w);

/*
 * Premultiply the matrix by a shear Z matrix parameterized by shx,shy
 */
void matrix_shearZ(Matrix *m, double shx, double shy);

/*
 * premultiply the matrix by a perspective matrix parameterized by d
 */
void matrix_perspective(Matrix *m, double d);

/*
 * Sets vtm to be the view transformation defined by the 2DView structure.
 */
 void matrix_setView2D(Matrix *vtm, View2D *view);
 
/*
 * Implement the 3D perspective pipeline.
 * When the function returns, the vtm should contain the complete view matrix. 
 * Inside the function, begin by initializing VTM to the identity. 
 * Do not modify any of the values in the PerspectiveView structure inside the
 * function (no side-effects)
 */
 void matrix_setView3D(Matrix *vtm, View3D *view);

void view2D_set(View2D *view, Point *vrp, double dx, Vector *xaxis, int rows, int cols);

#endif
