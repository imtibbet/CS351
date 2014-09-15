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
	
} // end image_create

/*
 *  de-allocates image data and frees the Image structure.
 */
void image_free(Image *src){

} // end image_free

/*
 * given an uninitialized Image structure, sets the rows and cols fields 
 * to zero and the data field to NULL.
 */
void image_init(Image *src){

} // end image_init

/*
 * allocates space for the image data given rows and columns and initializes the
 * image data to appropriate values, such as 0.0 for RGBA and 1.0 for Z. 
 * Returns 0 if the operation is successful. Returns a non-zero value if the
 * operation fails. This function should probably free existing memory if rows 
 * and cols are both non-zero.
 */
int image_alloc(Image *src, int rows, int cols){

} // end image_alloc

/*
 * de-allocates image data and resets the Image structure fields. 
 * The function does not free the Image structure.
 */
void image_dealloc(Image *src){

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

} // end image_read

/*
 * writes a PPM image to the given filename.
 * Returns 0 on success. Optionally, you can look at the filename extension and 
 * write different file types.
 */
int image_write(Image *src, char *filename){

} // end image_write

// Access

/*
 * returns the FPixel at (r, c).
 */
FPixel image_getf(Image *src, int r, int c){

} // end image_getf

/*
 * returns the value of band b at pixel (r, c).
 */
float image_getc(Image *src, int r, int c, int b){

} // end image_getf

/*
 * returns the alpha value at pixel (r, c).
 */
float image_geta(Image *src, int r, int c){

} // end image_geta

/*
 * returns the depth value at pixel (r, c).
 */
float image_getz(Image *src, int r, int c){

} // end image_getz

/*
 * sets the values of pixel (r, c) to the FPixel val.
 */
void image_setf(Image *src, int r, int c, FPixel val){

} // end image_setf

/*
 * sets the value of pixel (r, c) band b to val.
 */
void image_setc(Image *src, int r, int c, int b, float val){

} // end image_setc

/*
 * sets the alpha value of pixel (r, c) to val.
 */
void image_seta(Image *src, int r, int c, float val){

} // end image_seta

/*
 * sets the depth value of pixel (r, c) to val.
 */
void image_setz(Image *src, int r, int c, float val){

} // end image_setz

// Utility

/*
 * resets every pixel to a default value (e.g. Black, alpha value of 1.0, 
 * z value of 1.0).
 */
void image_reset(Image *src){

} // end image_reset

/*
 * sets every FPixel to the given value.
 */
void image_fill(Image *src, FPixel val){

} // end image_fill

/*
 * sets the (r, g, b) values of each pixel to the given color.
 */
void image_fillrgb(Image *src, float r, float g, float b){

} // end image_fillrgb

/*
 * sets the alpha value of each pixel to the given value.
 */
void image_filla(Image *src, float a){

} // end image_filla

/*
 * sets the z value of each pixel to the given value.
 */
void image_fillz(Image *src, float z){

} // end image_fillz

////////////////////////////////////////////////////////////////////////////////

// read in rgb values from the ppm file output by cqcam
Pixel *readPPM(int *rows, int *cols, int * colors, char *filename) {
   char tag[40];
   Pixel *image;
   FILE *fp;
   int read, num[3], curchar;

   if(filename != NULL && strlen(filename))
     fp = fopen(filename, "r");
   else
     fp = stdin;

   if(fp) {
     fscanf(fp, "%s\n", tag);

     // Read the "magic number" at the beginning of the ppm
     if (strncmp(tag, "P6", 40) != 0) {
       fprintf(stderr, "not a ppm!\n");
       exit(1);
     }
     
     // Read the rows, columns, and color depth output by cqcam
     // need to read in three numbers and skip any lines that start with a #
     read = 0;
     while(read < 3) {
       curchar = fgetc(fp);
       if((char)curchar == '#') { // skip this line
	 while(fgetc(fp) != '\n')
	   /* do nothing */;
       }
       else {
	 ungetc(curchar, fp);
	 fscanf(fp, "%d", &(num[read]));
	 read++;
       }
     }
     while(fgetc(fp) != '\n')
       /* pass the last newline character */;

     *cols = num[0];
     *rows = num[1];
     *colors = num[2];

     if(*cols > 0 && *rows > 0) {
#if USECPP
       image = new Pixel[(*rows) * (*cols)];
#else
       image = (Pixel *)malloc(sizeof(Pixel)* (*rows) * (*cols));
#endif
       if(image) {
	 // Read the data
	 fread(image, sizeof(Pixel), (*rows) * (*cols), fp);

	 if(fp != stdin)
	   fclose(fp);

	 return(image);
       }
     }

   }
   
   return(NULL);
     
} // end read_ppm

// Write the modified image out as a ppm in the correct format to be read by 
// read_ppm.  xv will read these properly.
void writePPM(Pixel *image, int rows, int cols, int colors, char *filename)
{
  FILE *fp;

  if(filename != NULL && strlen(filename))
    fp = fopen(filename, "w");
  else
    fp = stdout;

  if(fp) {
    fprintf(fp, "P6\n");
    fprintf(fp, "%d %d\n%d\n", cols, rows, colors);

    fwrite(image, sizeof(Pixel), rows * cols, fp);
  }

  fclose(fp);

} // end write_ppm 


// Write the modified image out as a pgm in the correct format
void writePGM(unsigned char *image, long rows, long cols, int intensities, char *filename)
{
  FILE *fp;

  if(filename != NULL && strlen(filename))
    fp = fopen(filename, "w");
  else
    fp = stdout;

  if(fp) {
    fprintf(fp, "P5\n");
    fprintf(fp, "%ld %ld\n%d\n", cols, rows, intensities);

    fwrite(image, sizeof(unsigned char), rows * cols, fp);
  }

  if(fp != stdout)
    fclose(fp);
} // end write_pgm 


// read in intensity values from the pgm file
unsigned char *readPGM(int *rows, int *cols, int *intensities, char *filename) {
   char tag[40];
   unsigned char *image;
   FILE *fp;
   int read, num[3], curchar;

   if(filename != NULL && strlen(filename))
     fp = fopen(filename, "r");
   else
     fp = stdin;

   if(fp) {
     fscanf(fp, "%s\n", tag);

     // Read the "magic number" at the beginning of the ppm
     if (strncmp(tag, "P5", 40) != 0) {
       fprintf(stderr, "not a ppm!\n");
       exit(1);
     }
     
     // Read the rows, columns, and color depth output by cqcam
     // need to read in three numbers and skip any lines that start with a #
     read = 0;
     while(read < 3) {
       curchar = fgetc(fp);
       if((char)curchar == '#') { // skip this line
	 while(fgetc(fp) != '\n')
	   /* do nothing */;
       }
       else {
	 ungetc(curchar, fp);
	 fscanf(fp, "%d", &(num[read]));
	 read++;
       }
     }
     while(fgetc(fp) != '\n')
       /* pass the last newline character */;

     *cols = num[0];
     *rows = num[1];
     *intensities = num[2];

     if(*intensities != 255) {
       printf("Unable to read this file correctly\n");
       return(NULL);
     }

     if(*cols > 0 && *rows > 0) {
#if USECPP
       image = new unsigned char[(*rows) * (*cols)];
#else
       image = (unsigned char *)malloc(sizeof(unsigned char) * (*rows) * (*cols));
#endif
       if(image) {
	 // Read the data
	 fread(image, sizeof(unsigned char), (*rows) * (*cols), fp);

	 if(fp != stdin)
	   fclose(fp);

	 return(image);
       }
     }

   }
   
   return(NULL);
     
} // end read_pgm

