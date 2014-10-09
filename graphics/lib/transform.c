/*
 * Author: Ian Tibbetts and Astrid Moore
 * Date: 10/5/14
 *
 * The transformation function implementations
 */

#include "graphics.h"

// vector

/*
 * Set the Vector to (x, y, z, 0.0)
 */
void vector_set(Vector *v, double x, double y, double z){
	v->val[0] = x;
	v->val[1] = y;
	v->val[2] = z;
	v->val[3] = 0.0;
}

/*
 * Print out the Vector to stream fp in a pretty form
 */
void vector_print(Vector *v, FILE *fp){
	fprintf(fp,"[%.3f, %.3f, %.3f, %.3f]\n",v->val[0],v->val[1],v->val[2],v->val[3]);
}

/*
 * Returns the Euclidean length of the vector, assuming the homogeneous coordinate is 1.0
 */
double vector_length(Vector *v){
	return sqrt( v->val[0]*v->val[0] + v->val[1]*v->val[1] + v->val[2]*v->val[2] );
}

/*
 * Normalize the Vector to unit length. Do not modify the homogeneous coordinate.
 */
void vector_normalize(Vector *v){
	float x = v->val[0];
	float y = v->val[1];
	float z = v->val[2];
	float vLength = sqrt( x*x + y*y + z*z );
	v->val[0] = x / vLength;
	v->val[1] = y / vLength;
	v->val[2] = z / vLength;
}

/*
 * Returns the scalar product of a and b
 */
double vector_dot(Vector *a, Vector *b){
	return(a->val[0]*b->val[0] + a->val[1]*b->val[1] + a->val[2]*b->val[2]);
}

/*
 * Calculates the the cross product (vector product) of a and b
 * and puts the result in c
 */
void vector_cross(Vector *a, Vector *b, Vector *c){
	c->val[0] = a->val[1]*b->val[2] - a->val[2]*b->val[1];
	c->val[1] = a->val[2]*b->val[0] - a->val[0]*b->val[2];
	c->val[2] = a->val[0]*b->val[1] - a->val[1]*b->val[0];
}

// 2D matrix

/*
 * Print out the matrix in a nice 4x4 arrangement with a blank line below.
 */
void matrix_print(Matrix *m, FILE *fp){
	fprintf(fp,	"|%.3f, %.3f, %.3f, %.3f|\n" 
				"|%.3f, %.3f, %.3f, %.3f|\n" 
				"|%.3f, %.3f, %.3f, %.3f|\n" 
				"|%.3f, %.3f, %.3f, %.3f|\n\n",
				m->m[0][0],m->m[0][1],m->m[0][2],m->m[0][3],
				m->m[1][0],m->m[1][1],m->m[1][2],m->m[1][3],
				m->m[2][0],m->m[2][1],m->m[2][2],m->m[2][3],
				m->m[3][0],m->m[3][1],m->m[3][2],m->m[3][3]);
}

/*
 * Set the matrix to all zeros.
 */
void matrix_clear(Matrix *m){
	m->m[0][0] = m->m[0][1] = m->m[0][2] = m->m[0][3] = 
	m->m[1][0] = m->m[1][1] = m->m[1][2] = m->m[1][3] = 
	m->m[2][0] = m->m[2][1] = m->m[2][2] = m->m[2][3] = 
	m->m[3][0] = m->m[3][1] = m->m[3][2] = m->m[3][3] = 0.0;
}

/*
 * Set the matrix to the identity matrix
 */
void matrix_identity(Matrix *m){
	m->m[0][1] = m->m[0][2] = m->m[0][3] = 
	m->m[1][0] = m->m[1][2] = m->m[1][3] = 
	m->m[2][0] = m->m[2][1] = m->m[2][3] = 
	m->m[3][0] = m->m[3][1] = m->m[3][2] =  0.0;
	m->m[0][0] = m->m[1][1] = m->m[2][2] = m->m[3][3] = 1.0;
}
 
/*
 * Return the element of the matrix at row r, column c. 
 */
double matrix_get(Matrix *m, int r, int c){
	return(m->m[r][c]);
}

/*
 * Set the element of the matrix at row r, column c to v.
 */
void matrix_set(Matrix *m, int r, int c, double v){
	m->m[r][c] = v;
}

/*
 * Copy the src matrix into the dest matrix.
 */
void matrix_copy(Matrix *dest, Matrix *src){
	int i, j;
	for(i=0;i<4;i++){
		for(j=0;j<4;j++){
			dest->m[i][j] = src->m[i][j];
		}
	}
}

/*
 * Transpose the matrix m in place.
 */
void matrix_transpose(Matrix *m){
	int i, j;
	float temp;
	for(i=0;i<4;i++){
		for(j=0;j<i;j++){
			if(i!=j){
				temp = m->m[i][j];
				m->m[i][j] = m->m[j][i];
				m->m[j][i] = temp;
			}
		}
	}
}

/*
 * Multiply left and right and put the result in m
 * Make sure that the function is written so that the result matrix 
 * can also be the left or right matrix
 */
void matrix_multiply(Matrix *left, Matrix *right, Matrix *m){
	int i, j;
	Matrix temp; // use a temp matrix so the destination can also be an argument
	for(i=0;i<4;i++){
		for(j=0;j<4;j++){
			temp.m[i][j] = 	left->m[i][0] * right->m[0][j] +
							left->m[i][1] * right->m[1][j] + 
							left->m[i][2] * right->m[2][j] + 
							left->m[i][3] * right->m[3][j];
		}
	}

	// copy the temp matrix into the desination matrix
	for(i=0;i<4;i++){
		for(j=0;j<4;j++){
			m->m[i][j] = temp.m[i][j];
		}
	}
}

/*
 * Transform the point p by the matrix m and put the result in q. 
 * For this function, p and q need to be different variables.
 */
void matrix_xformPoint(Matrix *m, Point *p, Point *q){
	int i;
	for(i=0;i<4;i++){
		q->val[i] =	m->m[i][0] * p->val[0] +
					m->m[i][1] * p->val[1] + 
					m->m[i][2] * p->val[2] + 
					m->m[i][3] * p->val[3];
	}
}

/*
 * Transform the vector p by the matrix m and put the result in q. 
 * For this function, p and q need to be different variables.
 */
void matrix_xformVector(Matrix *m, Vector *p, Vector *q){
	int i;
	for(i=0;i<4;i++){
		q->val[i] =	m->m[i][0] * p->val[0] +
					m->m[i][1] * p->val[1] + 
					m->m[i][2] * p->val[2] + 
					m->m[i][3] * p->val[3];
	}
}

/*
 * Transform the points and surface normals (if they exist) 
 * in the Polygon p by the matrix m.
 */
void matrix_xformPolygon(Matrix *m, Polygon *p){
	int i;
	Point temp;
	for(i=0;i<p->nVertex;i++){
		matrix_xformPoint(m, &(p->vertex[i]), &temp);
		point_copy(&(p->vertex[i]), &temp);
	}
}

/*
 * Transform the points in the Polyline p by the matrix m.
 */
void matrix_xformPolyline(Matrix *m, Polyline *p){
	int i;
	Point temp;
	for(i=0;i<p->numVertex;i++){
		matrix_xformPoint(m, &(p->vertex[i]), &temp);
		point_copy(&(p->vertex[i]), &temp);
	}
}

/*
 * Transform the points in line by the matrix m.
 */
void matrix_xformLine(Matrix *m, Line *line){
	Point temp;
	matrix_xformPoint(m, &(line->a), &temp);
	point_copy(&(line->a), &temp);
	matrix_xformPoint(m, &(line->b), &temp);
	point_copy(&(line->b), &temp);
}

/*
 * Premultiply the matrix by a scale matrix parameterized by sx and sy
 */
void matrix_scale2D(Matrix *m, double sx, double sy){
	Matrix sm;
	matrix_identity(&sm);
	sm.m[0][0] = sx;
	sm.m[1][1] = sy;
	matrix_multiply(&sm, m, m);
}

/*
 * Premultiply the matrix by a Z-axis rotation matrix parameterized by
 * cos(t) and sin(t), where t is the angle of rotation about the Z-axis
 */
void matrix_rotateZ(Matrix *m, double cth, double sth){
	Matrix rm;
	matrix_identity(&rm);
	rm.m[0][0] = cth;
	rm.m[0][1] = -sth;
	rm.m[1][0] = sth;
	rm.m[1][1] = cth;
	matrix_multiply(&rm, m, m);
}

/*
 * Premultiply the matrix by a 2D translation matrix parameterized by tx, ty
 */
void matrix_translate2D(Matrix *m, double tx, double ty){
	Matrix tm;
	matrix_identity(&tm);
	tm.m[0][3] = tx;
	tm.m[1][3] = ty;
	matrix_multiply(&tm, m, m);
}

/*
 * Premultiply the matrix by a 2D shear matrix parameterized by shx, shy
 */
void matrix_shear2D(Matrix *m, double shx, double shy){
	Matrix shm;
	matrix_identity(&shm);
	shm.m[0][1] = shx;
	shm.m[1][0] = shy;
	matrix_multiply(&shm, m, m);
}

// 3D matrix

/*
 * Premultiply the matrix by a translation matrix parameterized by tx,ty,tz
 */
void matrix_translate(Matrix *m, double tx, double ty, double tz){
	Matrix tm;
	matrix_identity(&tm);
	tm.m[0][3] = tx;
	tm.m[1][3] = ty;
	tm.m[2][3] = tz;
	matrix_multiply(&tm, m, m);
}

/*
 * Premultiply the matrix by a scale matrix parameterized by sx,sy,sz
 */
void matrix_scale(Matrix *m, double sx, double sy, double sz){
	Matrix sm;
	matrix_identity(&sm);
	sm.m[0][0] = sx;
	sm.m[1][1] = sy;
	sm.m[2][2] = sz;
	matrix_multiply(&sm, m, m);
}

/*
 * premultiply the matrix by a X-axis rotation matrix parameterized by
 * cos(t) and sin(t), where t is the angle of rotation about the x axis
 */
void matrix_rotateX(Matrix *m, double cth, double sth){
	Matrix rm;
	matrix_identity(&rm);
	rm.m[1][1] = cth;
	rm.m[1][2] = -sth;
	rm.m[2][1] = sth;
	rm.m[2][2] = cth;
	matrix_multiply(&rm, m, m);
}

/*
 * premultiply the matrix by a Y-axis rotation matrix parameterized by
 * cos(t) and sin(t), where t is the angle of rotation about the y axis
 */
void matrix_rotateY(Matrix *m, double cth, double sth){
	Matrix rm;
	matrix_identity(&rm);
	rm.m[0][0] = cth;
	rm.m[0][2] = sth;
	rm.m[2][0] = -sth;
	rm.m[2][2] = cth;
	matrix_multiply(&rm, m, m);
}

/*
 * premultiply the matrix by a XYZ-axis rotation matrix parameterized by
 * u,v,w where the three vectors represent an orthonormal 3D basis
 */
void matrix_rotateXYZ(Matrix *m, Vector *u, Vector *v, Vector *w){
	int j;
	Matrix rm;
	matrix_identity(&rm);
	for(j=0;j<3;j++){
		rm.m[0][j] = u->val[j];
		rm.m[1][j] = v->val[j];
		rm.m[2][j] = w->val[j];
	}
	matrix_multiply(&rm, m, m);

}

/*
 * Premultiply the matrix by a shear Z matrix parameterized by shx,shy
 */
void matrix_shearZ(Matrix *m, double shx, double shy){
	Matrix shm;
	matrix_identity(&shm);
	shm.m[0][2] = shx;
	shm.m[1][2] = shy;
	matrix_multiply(&shm, m, m);
}

/*
 * premultiply the matrix by a perspective matrix parameterized by d
 */
void matrix_perspective(Matrix *m, double d){
	Matrix pm;
	matrix_identity(&pm);
	pm.m[3][2] = 1.0/d;
	matrix_multiply(&pm, m, m);
}





