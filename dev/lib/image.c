/*
 * Author: Ian Tibbetts (Bruce Maxwell)
 * Date: 9/14/2014
 *
 * The images structure function implementations
*/

#include "graphics.h"

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
	src = malloc(sizeof(Image));
	if(!src){
		return(NULL);
	} 
	src->data = malloc(sizeof(FPixel *) * rows); 
	if(!src->data){
		free(src);
		return(NULL);
	} 
	src->data[0] = malloc(sizeof(FPixel) * rows * cols);
	if(!src->data[0]){
		free(src);
		free(src->data);
		return(NULL);
	}

	// assign all row pointers
	for(i=1;i<rows;i++){
		src->data[i] = &(src->data[0][i * cols]);
	}

	// assign image data fields to parameter and return pointer to image
	src->rows = rows;
	src->cols = cols;
	image_reset(src);
	
	// printf("image created\n");
	return(src);
	
} // end image_create

/*
 *  de-allocates image data and frees the Image structure.
 */
void image_free(Image *src){

	if(src){
		if(src->data){
			if(src->data[0]){
				free(src->data[0]);
			}
			free(src->data);
		}
		free(src);
	} else{
		printf("null image given to free\n");
		return;
	}
	// printf("image freed\n");

} // end image_free

/*
 * given an uninitialized Image structure, sets the rows and cols fields 
 * to zero and the data field to NULL.
 */
void image_init(Image *src){

	if(!src){
		printf("null image given to init\n");
		return;
	}
	src->data = NULL;
	src->rows = src->cols = 0;
	image_reset(src);
	// printf("image initted\n");

} // end image_init

/*
 * allocates space for the image data given rows and columns and initializes the
 * image data to appropriate values, such as 0.0 for RGBA and 1.0 for Z. 
 * Returns 0 if the operation is successful. Returns a non-zero value if the
 * operation fails. This function should probably free existing memory if rows 
 * and cols are both non-zero.
 */
int image_alloc(Image *src, int rows, int cols){

	int i;

	if(!src){
		printf("null image given to alloc\n");
		return(1);
	}

	// free existing memory
	if(src->data){
		if(src->data[0]){
			free(src->data[0]);
		}
		free(src->data);
	}

	// malloc new memory spave for data and return non-zero on failure
	src->data = (FPixel **)malloc(sizeof(FPixel *) * rows); 
	if(!src->data){
		return(1);
	}
	src->data[0] = (FPixel *)malloc(sizeof(FPixel) * rows * cols);
	if(!src->data[0]){
		free(src->data);
		return(1);
	}

	// assign all row pointers
	for(i=1;i<rows;i++){
		src->data[i] = &(src->data[0][i * cols]);
	}
	src->rows = rows;
	src->cols = cols;
	image_reset(src);
	// printf("image allocated\n");
	return(0);
	
} // end image_alloc

/*
 * de-allocates image data and resets the Image structure fields. 
 * The function does not free the Image structure.
 */
void image_dealloc(Image *src){

	if(!src){
		printf("null image given to dealloc\n");
		return;
	}

	if(src->data){
		if(src->data[0]){
			free(src->data[0]);
		}
		free(src->data);
	}
	src->rows = src->cols = 0;
	src->data = NULL;
	// printf("image deallocated\n");

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
		printf("readPPM failed, probably incorrect filename given.\n");
		return(NULL);
	}

	src = image_create(rows, cols);
	if(!src){
		free(readData);
		return(NULL);
	}
	
	// convert from Pixel to FPixel
	for(i=0;i<rows*cols;i++){
		src->data[0][i].rgb[0] = (float)(readData[i].r) / 255.0;
		src->data[0][i].rgb[1] = (float)(readData[i].g) / 255.0;
		src->data[0][i].rgb[2] = (float)(readData[i].b) / 255.0;
		src->data[0][i].a = src->data[0][i].z = 1.0;
	}
	free(readData);
	return(src);
	
} // end image_read

/*
 * writes a PPM image to the given filename.
 * Returns 0 on success. Optionally, you can look at the filename extension and 
 * write different file types.
 */
int image_write(Image *src, char *filename){

	Pixel *image;
	int i;

	if(!src){
		printf("null image given to write\n");
		return(1);
	}

	// convert from FPixel to Pixel
	image = (Pixel *)malloc(sizeof(Pixel) * src->rows * src->cols);
	if(!image){
		return(1);
	}
	for(i=0;i<src->rows*src->cols;i++){
		image[i].r = (int)(fminf(src->data[0][i].rgb[0] * 255.0, 255.0));
		image[i].g = (int)(fminf(src->data[0][i].rgb[1] * 255.0, 255.0));
		image[i].b = (int)(fminf(src->data[0][i].rgb[2] * 255.0, 255.0));
	}
	writePPM(image, src->rows, src->cols, 255 /* s/b 255 */, filename);
	free(image);
	// printf("image written\n");
	return(0);

} // end image_write

// Access

/*
 * returns the FPixel at (r, c).
 */
FPixel image_getf(Image *src, int r, int c){
	FPixel f;
	if( (r>=0) && (r<(src->rows)) &&
		(c>=0) && (c<(src->cols)) )
		return(src->data[r][c]);
	else
		return(f);
} // end image_getf

/*
 * returns the value of band b at pixel (r, c).
 */
float image_getc(Image *src, int r, int c, int b){
	if( (r>=0) && (r<(src->rows)) &&
		(c>=0) && (c<(src->cols)) )
		return(src->data[r][c].rgb[b]);
	else
		return(0.0);
} // end image_getf

/*
 * returns the alpha value at pixel (r, c).
 */
float image_geta(Image *src, int r, int c){
	if( (r>=0) && (r<(src->rows)) &&
		(c>=0) && (c<(src->cols)) )
		return(src->data[r][c].a);
	else
		return(0.0);
} // end image_geta

/*
 * returns the depth value at pixel (r, c).
 */
float image_getz(Image *src, int r, int c){
	if( (r>=0) && (r<(src->rows)) &&
		(c>=0) && (c<(src->cols)) )
		return(src->data[r][c].z);
	else
		return(0.0);
} // end image_getz

/*
 * sets the values of pixel (r, c) to the FPixel val.
 */
void image_setf(Image *src, int r, int c, FPixel val){
	if( (r>=0) && (r<(src->rows)) &&
		(c>=0) && (c<(src->cols)) )
		src->data[r][c] = val;
} // end image_setf

/*
 * sets the value of pixel (r, c) band b to val.
 */
void image_setc(Image *src, int r, int c, int b, float val){
	if( (r>=0) && (r<(src->rows)) &&
		(c>=0) && (c<(src->cols)) )
		src->data[r][c].rgb[b] = val;
} // end image_setc

/*
 * sets the alpha value of pixel (r, c) to val.
 */
void image_seta(Image *src, int r, int c, float val){
	if( (r>=0) && (r<(src->rows)) &&
		(c>=0) && (c<(src->cols)) )
		src->data[r][c].a = val;
} // end image_seta

/*
 * sets the depth value of pixel (r, c) to val.
 */
void image_setz(Image *src, int r, int c, float val){
	if( (r>=0) && (r<(src->rows)) &&
		(c>=0) && (c<(src->cols)) )
		src->data[r][c].z = val;
} // end image_setz

// Utility

/*
 * resets every pixel to a default value (e.g. Black, alpha value of 1.0, 
 * z value of 1.0).
 */
void image_reset(Image *src){

	int i, j;

	if(!src){
		printf("null src given to reset\n");
		return;
	}

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

	if(!src){
		printf("null src given to fill\n");
		return;
	}

	for(i=0;i<src->rows;i++){
		for(j=0;j<src->cols;j++){
			src->data[i][j] = val;
		}
	}

} // end image_fill

/*
 * sets the (r, g, b) values of each pixel to the given color.
 */
void image_fillrgb(Image *src, float r, float g, float b){

	int i, j;

	if(!src){
		printf("null src given to fillrgb\n");
		return;
	}

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

	if(!src){
		printf("null src given to filla\n");
		return;
	}

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

	if(!src){
		printf("null src given to fillz\n");
		return;
	}

	for(i=0;i<src->rows;i++){
		for(j=0;j<src->cols;j++){
			src->data[i][j].z = z;
		}
	}

} // end image_fillz

// Procedural texture

/*
 * An adaptation of Worley noise, which create cell or stone like noise
 * on the given image structure according to the given density, which
 * must be an integer no less than 2.
 */
void image_noise(Image *src, int density){
	
	int i, j, k;
	int **featurePoints;
	float dist, dist1, dist2, closest, closest2, colorVal;

	// because of the way i implement the algorithm this is a precondition
	if(density < 2){
		printf("must be denser than 2 feature points\n");
		return;
	} else if(!src){
		printf("null src given to noise\n");
		return;
	}

	// initialize a 2D array of integers, which will be an array of
	// (row, col) pairs for the feature points
	featurePoints = malloc(sizeof(FPoint) * density);
	if(!featurePoints){
		printf("image_noise failed to malloc feaute point space, returning\n");
		return;
	}
	
	// initialize the seed of the random function with the current time
	srand(time(NULL));
	
	// randomly select density number of feature points from the image region
	for(i=0;i<density;i++){
		featurePoints[i][0] = rand() % src->rows;
		featurePoints[i][1] = rand() % src->cols;
		printf("feature at row:%d col:%d\n",
				featurePoints[i][0],featurePoints[i][1]);
	}

	// loop over entire image, using feature points to color each FPixel
	for(i=0;i<src->rows;i++){
		for(j=0;j<src->cols;j++){

			// initialize the closest and second closest feature from the
			// first two feature points (method prerequisite of at least 2)
			dist1 = sqrt(	(i-featurePoints[0][0])*(i-featurePoints[0][0]) +
							(j-featurePoints[0][1])*(j-featurePoints[0][1]));
			dist2 = sqrt(	(i-featurePoints[1][0])*(i-featurePoints[1][0]) +
							(j-featurePoints[1][1])*(j-featurePoints[1][1]));
			if(dist1 < dist2){
				closest = dist1;
				closest2 = dist2;
			} else {
				closest = dist2;
				closest2 = dist1;
			}

			// loop over feature points and find the closest and second closest
			for(k=0;k<density;k++){
				dist = sqrt((i-featurePoints[k][0])*(i-featurePoints[k][0]) +
							(j-featurePoints[k][1])*(j-featurePoints[k][1]));
				if(dist < closest){
					closest2 = closest;
					closest = dist;
				} else if(dist < closest2){
					closest2 = dist;
				}
			}

			// the color of the FPixel must be in {0.0,1.0}
			colorVal = closest / closest2;
			//printf("%f, %f\n",closest,closest2);
			src->data[i][j].rgb[0] *= colorVal;
			src->data[i][j].rgb[1] *= colorVal;
			src->data[i][j].rgb[2] *= colorVal;
		}
	}
	
	// prevent memory leak (thanks Bruce)
	free(featurePoints);
}

// Colors

// copies the Color data to the proper pixel.
void image_setColor( Image *src, int r, int c, Color val ){
	if( (r>=0) && (r<(src->rows)) &&
		(c>=0) && (c<(src->cols)) ){
		src->data[r][c].rgb[0] = val.c[0];
		src->data[r][c].rgb[1] = val.c[1];
		src->data[r][c].rgb[2] = val.c[2];
	}
}

// returns a Color structure built from the pixel values
Color image_getColor( Image *src, int r, int c ){
	Color val;
	if( (r>=0) && (r<(src->rows)) &&
		(c>=0) && (c<(src->cols)) ){
		val.c[0] = src->data[r][c].rgb[0];
		val.c[1] = src->data[r][c].rgb[1];
		val.c[2] = src->data[r][c].rgb[2];
	}
	return(val);
}

/*
 * sets the (r, g, b) values of each pixel to the given color.
 */
void image_fillColor(Image *src, Color c){

	int i, j;

	if(!src){
		printf("null src given to fillrgb\n");
		return;
	}

	for(i=0;i<src->rows;i++){
		for(j=0;j<src->cols;j++){
			src->data[i][j].rgb[0] = c.c[0];
			src->data[i][j].rgb[1] = c.c[1];
			src->data[i][j].rgb[2] = c.c[2];
		}
	}

} // end image_fillColor



