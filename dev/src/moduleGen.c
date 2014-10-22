/*
  Ian Tibbetts
  Fall 2014

  for easily generating modules
 */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "graphics.h"


int main(int argc, char *argv[]) {

  // grab command line argument to call module generate
  int success = 0;
  if( argc < 2 ) {
    printf("Usage: require input [and optionally output] filenames as command line parameters\n");
  } else if (argc == 2) {
    success = genModule( argv[1], "moduleGen_output.txt" );
  } else {
    success = genModule( argv[1], argv[2] );
  }

  if(!success){
    printf("genModule failed, verify file name given exists and is accessible\n");
  } else {
    printf("success!\n");
  }
  return(0);
}
