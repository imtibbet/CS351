/*
Author: Ian Tibbetts (Bruce Maxwell)
Date: 9/14/2014

The images structure function implementations
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ppmIO.h"
#include "images.h"

#define USECPP 0

// Constructors and destructors:
/*
 * Allocates an Image structure and initializes the top level fields to 
 * appropriate values. Allocates space for an image of the specified size, 
 * unless either rows or cols is 0. Returns a pointer to the allocated Image
 * structure. Returns a NULL pointer if the operation fails.
 */
Image *image_create(int rows, int cols){

	int i;
	Image *src = NULL;

	// use malloc to reserve memory for image, returning NULL on failure
	src = (Image *)malloc(sizeof(Image)); 
	if(!src){
		return(NULL);
	}
	src->data = (FPixel **)malloc(sizeof(FPixel *) * rows); 
	if(!src->data){
		return(NULL);
	}
	src->data[0] = (FPixel *)malloc(sizeof(FPixel) * rows * cols);
	if(!src->data[0]){
		return(NULL);
	}

	// assign all row pointers
	for(i=1;i<rows-1;i++){
		src->data[i] = &(src->data[0][i * cols]);
	}

	// assign image data fields to parameter and return pointer to image
	src->rows = rows;
	src->cols = cols;
	return(src);
	
} // end image_create

/*
 *  de-allocates image data and frees the Image structure.
 */
void image_free(Image *src){

	free(src);

} // end image_free

/*
 * given an uninitialized Image structure, sets the rows and cols fields 
 * to zero and the data field to NULL.
 */
void image_init(Image *src){

	src->data = NULL;
	src->rows = src->cols = 0;

} // end image_init

/*
 * allocates space for the image data given rows and columns and initializes the
 * image data to appropriate values, such as 0.0 for RGBA and 1.0 for Z. 
 * Returns 0 if the operation is successful. Returns a non-zero value if the
 * operation fails. This function should probably free existing memory if rows 
 * and cols are both non-zero.
 */
int image_alloc(Image *src, int rows, int cols){

	int i, j;
	
	// free existing memory if rows and cols are both non-zero.
	if(src->rows != 0 and src->cols != 0){
		free(src->data);
	}

	// malloc new memory spave for data and return non-zero on failure
	src->data = (FPixel **)malloc(sizeof(FPixel *) * rows); 
	if(!src->data){return(1);}
	src->data[0] = (FPixel *)malloc(sizeof(FPixel) * rows * cols);
	if(!src->data[0]){return(1);}

	// assign all row pointers
	for(i=0;i<rows;i++){
		src->data[i] = &(src->data[0][i * cols]);

		// initialize data to appropriate values
		for(j=0;j<cols;i++){
			src->data[i][j].rgb[0] = 
			src->data[i][j].rgb[1] = 
			src->data[i][j].rgb[2] = 
			src->data[i][j].a = 0.0;
			src->data[i][j].z = 1.0;
		}
	}
	return(0);
	
} // end image_alloc

/*
 * de-allocates image data and resets the Image structure fields. 
 * The function does not free the Image structure.
 */
void image_dealloc(Image *src){

	free(src->data[0])
	free(src->data)
	src->rows = src->cols = 0;

} // end image_dealloc

// I/O functions:

/*
 * reads a PPM image from the given filename. 
 * An optional extension is to determine the image type from the filename and 
 * permit the use of different file types. 
 * Initializes the alpha channel to 1.0 and the z channel to 1.0. 
 * Returns a NULL pointer if the operation fails.
 */
Image *image_read(char *filename){

	Image *src;
	Pixel *readData;
	int i, rows, cols, colors;

	readData = readPPM(&rows, &cols, &colors, filename);
	if(!readData){
		return(NULL);
	}
	src = image_create(rows, cols);
	for(i=0;i<rows*cols;i++){
		src->data[0][i].rgb[0] = (float)readData[i].r;
		src->data[0][i].rgb[1] = (float)readData[i].g;
		src->data[0][i].rgb[2] = (float)readData[i].b;
		src->data[0][i].a = src->data[0][i].z = 1.0;
	}
	return(src);
	
} // end image_read

/*
 * writes a PPM image to the given filename.
 * Returns 0 on success. Optionally, you can look at the filename extension and 
 * write different file types.
 */
int image_write(Image *src, char *filename){

	writePPM(src, src->rows, src->cols, 100 /* s/b 255 */, filename);
	return(0);

} // end image_write

// Access

/*
 * returns the FPixel at (r, c).
 */
FPixel image_getf(Image *src, int r, int c){
	return(src->data[r][c]);
} // end image_getf

/*
 * returns the value of band b at pixel (r, c).
 */
float image_getc(Image *src, int r, int c, int b){
	return(src->data[r][c][b]);
} // end image_getf

/*
 * returns the alpha value at pixel (r, c).
 */
float image_geta(Image *src, int r, int c){
	return(src->data[r][c].a);
} // end image_geta

/*
 * returns the depth value at pixel (r, c).
 */
float image_getz(Image *src, int r, int c){
	return(src->data[r][c].z);
} // end image_getz

/*
 * sets the values of pixel (r, c) to the FPixel val.
 */
void image_setf(Image *src, int r, int c, FPixel val){
	src->data[r][c] = val;
} // end image_setf

/*
 * sets the value of pixel (r, c) band b to val.
 */
void image_setc(Image *src, int r, int c, int b, float val){
	src->data[r][c][b] = val;

} // end image_setc

/*
 * sets the alpha value of pixel (r, c) to val.
 */
void image_seta(Image *src, int r, int c, float val){
	src->data[r][c].a = val;
} // end image_seta

/*
 * sets the depth value of pixel (r, c) to val.
 */
void image_setz(Image *src, int r, int c, float val){
	src->data[r][c].z = val;
} // end image_setz

// Utility

/*
 * resets every pixel to a default value (e.g. Black, alpha value of 1.0, 
 * z value of 1.0).
 */
void image_reset(Image *src){
	int i, j;
	for(i=0;i<src->rows;i++){
		for(j=0;j<src->cols;j++){
			src->data[i][j].rgb[0] = 
			src->data[i][j].rgb[1] = 
			src->data[i][j].rgb[2] = 0.0;
			src->data[i][j].a = 
			src->data[i][j].z = 1.0;
		}
	}
} // end image_reset

/*
 * sets every FPixel to the given value.
 */
void image_fill(Image *src, FPixel val){
	int i, j;
	for(i=0;i<src->rows;i++){
		for(j=0;j<src->cols;j++){
			src->data[i][j].rgb[0] = val.r;
			src->data[i][j].rgb[1] = val.g;
			src->data[i][j].rgb[2] = val.b;
		}
	}
} // end image_fill

/*
 * sets the (r, g, b) values of each pixel to the given color.
 */
void image_fillrgb(Image *src, float r, float g, float b){
	int i, j;
	for(i=0;i<src->rows;i++){
		for(j=0;j<src->cols;j++){
			src->data[i][j].rgb[0] = r;
			src->data[i][j].rgb[1] = g;
			src->data[i][j].rgb[2] = b;
		}
	}
} // end image_fillrgb

/*
 * sets the alpha value of each pixel to the given value.
 */
void image_filla(Image *src, float a){
	int i, j;
	for(i=0;i<src->rows;i++){
		for(j=0;j<src->cols;j++){
			src->data[i][j].a = a;
		}
	}
} // end image_filla

/*
 * sets the z value of each pixel to the given value.
 */
void image_fillz(Image *src, float z){
	int i, j;
	for(i=0;i<src->rows;i++){
		for(j=0;j<src->cols;j++){
			src->data[i][j].z = z;
		}
	}
} // end image_fillz

