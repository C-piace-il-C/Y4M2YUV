#ifndef Y4M2YUV_H_
#define Y4M2YUV_H_

#define PROGRAM_NAME 				"y4m2yuv"
#define BUFFER_SIZE					1000

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

int convertY4m(const char* inputFilename, const char* outputFilename);
void doHelp();

#endif /* Y4M2YUV_H_ */
