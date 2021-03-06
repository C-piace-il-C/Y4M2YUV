/*
============================================================================
Name        : Y4M2YUV.c
Author      : Andrea Luzzati
Version     : 1.0
============================================================================
*/
#include "Y4M2YUV.h"

int
main(int argc, char ** argv)
{
  if(argc != 3)
  {
    doHelp();
    return(1);
  }

  int res = convertY4MO(argv[1], argv[2]);

  return(res);
}
