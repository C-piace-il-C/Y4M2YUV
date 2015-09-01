#ifndef Y4M2YUV_H_
#define Y4M2YUV_H_

#if defined _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif /* _MSC_VER */

#define PROGRAM_NAME        "y4m2yuv"
#define BUFFER_SIZE         1000

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

uint_fast8_t convertY4M(const char * inputFilename, const char * outputFilename);
uint_fast8_t convertY4MO(const char * inputFilename, const char * outputFilename); // Optimized
void doHelp();

#endif /* Y4M2YUV_H_ */
