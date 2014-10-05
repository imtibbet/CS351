/*
 * Author: Ian Tibbetts and Astrid Moore
 * Date: 10/5/14
 *
 * The transformation function implementations
 */

#include "graphics.h"

typedef struct {
	float m[4][4];
} Matrix;

typedef Point Vector;

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
	fprintf(fp,"[%f, %f, %f, %f]\n",v->val[0],v->val[1],v->val[2],v->val[3]);
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
	fprintf(fp,	"|%f, %f, %f, %f|\n" +
				"|%f, %f, %f, %f|\n" +
				"|%f, %f, %f, %f|\n" +
				"|%f, %f, %f, %f|\n\n",
				m->m[0][0],m->m[0][1],m->m[0][2],m->m[0][3],
				m->m[1][0],m->m[1][1],m->m[1][2],m->m[1][3],
				m->m[2][0],m->m[2][1],m->m[2][2],m->m[2][3],
				m->m[3][0],m->m[3][1],m->m[3][2],m->m[3][3]);
}

/*
 * Set the matrix to all zeros.
 */
void matrix_clear(Matrix *m){
	int i, j;
	for(i=0;i<4;i++){
		for(j=0;j<4;j++){
			m->m[i][j] = 0.0;
		}
	}
}

/*
 * Set the matrix to the identity matrix
 */
void matrix_identity(Matrix *m){
	int i, j;
	for(i=0;i<4;i++){
		for(j=0;j<4;j++){
			if(i==j){
				m->m[i][j] = 1.0;
			} else {
				m->m[i][j] = 0.0;
			}
		}
	}
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
			dest->m[i][j] = src->m[i][j]
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
		for(j=0;j<4;j++){
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
	int i, j, k, sum;
	for(i=0;i<4;i++){
		sum = 0;
		for(j=0;j<4;j++){
			for(k=0;k<4;k++){
				sum += left->m[i][k] * right->m[k][j];
			}
			m->m[i][j] = sum;
		}
	}
}

/*
 * Transform the point p by the matrix m and put the result in q. 
 * For this function, p and q need to be different variables.
 */
void matrix_xformPoint(Matrix *m, Point *p, Point *q){
	int i, j, k, sum;
	for(i=0;i<4;i++){
		sum = 0;
		for(j=0;j<4;j++){
			sum += m->m[i][j] * p->val[j];
		}
		q->val[i] = sum;
	}
}

/*
 * Transform the vector p by the matrix m and put the result in q. 
 * For this function, p and q need to be different variables.
 */
void matrix_xformVector(Matrix *m, Vector *p, Vector *q){
	int i, j, k, sum;
	for(i=0;i<4;i++){
		sum = 0;
		for(j=0;j<4;j++){
			sum += m->m[i][j] * p->val[j];
		}
		q->val[i] = sum;
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
		point_copy(&(p->vertex[i]), temp);
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
	matrix_xformPoint(m, &(l->a), &temp);
	point_copy(&(l->a), &temp);
	matrix_xformPoint(m, &(l->b), &temp);
	point_copy(&(l->b), &temp);
}

/*
 * Premultiply the matrix by a scale matrix parameterized by sx and sy
 */
void matrix_scale2D(Matrix *m, double sx, double sy){

}

/*
 * Premultiply the matrix by a Z-axis rotation matrix parameterized by
 * cos(t) and sin(t), where t is the angle of rotation about the Z-axis
 */
void matrix_rotateZ(Matrix *m, double cth, double sth){

}

/*
 * Premultiply the matrix by a 2D translation matrix parameterized by tx, ty
 */
void matrix_translate2D(Matrix *m, double tx, double ty){

}

/*
 * Premultiply the matrix by a 2D shear matrix parameterized by shx, shy
 */
void matrix_shear2D(Matrix *m, double shx, double shy){

}

// 3D matrix

/*
 * Premultiply the matrix by a translation matrix parameterized by tx,ty,tz
 */
void matrix_translate(Matrix *m, double tx, double ty, double tz){

}

/*
 * Premultiply the matrix by a scale matrix parameterized by sx,sy,sz
 */
void matrix_scale(Matrix *m, double sx, double sy, double sz){

}

/*
 * premultiply the matrix by a X-axis rotation matrix parameterized by
 * cos(t) and sin(t), where t is the angle of rotation about the x axis
 */
void matrix_rotateX(Matrix *m, double cth, double sth){

}

/*
 * premultiply the matrix by a Y-axis rotation matrix parameterized by
 * cos(t) and sin(t), where t is the angle of rotation about the y axis
 */
void matrix_rotateY(Matrix *m, double cth, double sth){

}

/*
 * premultiply the matrix by a XYZ-axis rotation matrix parameterized by
 * u,v,w where the three vectors represent an orthonormal 3D basis
 */
void matrix_rotateXYZ(Matrix *m, Vector *u, Vector *v, Vector *w){

}

/*
 * Premultiply the matrix by a shear Z matrix parameterized by shx,shy
 */
void matrix_shearZ(Matrix *m, double shx, double shy){

}

/*
 * premultiply the matrix by a perspective matrix parameterized by d
 */
void matrix_perspective(Matrix *m, double d){

}

