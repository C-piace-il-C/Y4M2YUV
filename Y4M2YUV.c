#include "Y4M2YUV.h"

/*
 * convertY4M(const char* inputFilename, const char* outputFilename)
 * This function converts Y4M input file to a YUV output file.
 * Return value is 1 on success and 0 on failure.
 */
int
convertY4M(const char* inputFilename, const char* outputFilename)
{
  // Open input and output
  FILE * input, * output;
  if ((input = fopen(inputFilename, "rb")) == NULL)
  {
    perror("Error occurred while opening input.");
    return(0);
  }
  if ((output = fopen(outputFilename, "wb")) == NULL)
  {
    fclose(input);
    perror("Error occurred while opening output");
    return(0);
  }

  char buffer [BUFFER_SIZE];
  char chunk  [BUFFER_SIZE];

  size_t bytesRead;
  int firstBlock = 1;
  int bufferNumber = 0;
  do
  {
    bufferNumber++;
    bytesRead = fread(buffer, 1, BUFFER_SIZE, input);

    size_t _ii = 0, _if = bytesRead - 1;

    size_t bytesCopied = 0;
    size_t bytesToCopy = 0;

    int C;
    if(bytesRead > 6)
      for (C = 0; C < bytesRead - 6; C++)
      {
        // "FRAME0x0A" block found
        if (buffer[C    ] == 'F' && buffer[C + 1] == 'R' && buffer[C + 2] == 'A' &&
            buffer[C + 3] == 'M' && buffer[C + 4] == 'E' && buffer[C + 5] == 0x0A)
        {
          switch (firstBlock)
          {
            case 1:
              // Header + block found
              _ii = C + 6;
              firstBlock = 0;
              break;
            case 0:
              _if = C - 1;
              // Copy the part between two blocks to chunk
              bytesToCopy = _if - _ii + 1;
              memcpy(chunk + bytesCopied, buffer + _ii, bytesToCopy);
              bytesCopied += bytesToCopy;
              _ii = C + 6;
              break;
          }
          C += 5;
        }
      }
    _if = BUFFER_SIZE - 1;
    bytesToCopy = _if - _ii + 1;
    memcpy(chunk + bytesCopied, buffer + _ii, bytesToCopy);
    bytesCopied += bytesToCopy;
    // Write chunk to file
    fwrite(chunk, bytesCopied, 1, output);
  }
  while (bytesRead == BUFFER_SIZE);

  fclose(input);
  fclose(output);

  return 1;
}

void
doHelp()
{
  printf(
      "%s help\n"
      "The correct command takes two arguments, the input and output filename.\n"
      "Example: %s input.y4m output.yuv\n",
      PROGRAM_NAME,
      PROGRAM_NAME
  );
}

int
convertY4MO(const char* inputFilename, const char* outputFilename)
{
   // Open input and output
   FILE * input, * output;
   if ((input = fopen(inputFilename, "rb")) == NULL)
   {
      perror("Error occurred while opening input.");
      return(0);
   }
   if ((output = fopen(outputFilename, "wb")) == NULL)
   {
      fclose(input);
      perror("Error occurred while opening output");
      return(0);
   }

   char* buffer = (char*)malloc(BUFFER_SIZE);
   char* chunk  = (char*)malloc(BUFFER_SIZE);

   size_t bytesRead;
   int blockNumber  = 0;
   int bufferNumber = 0;
   int frameSize    = 0;
   int posi = 0, posf = 0;
   int i = 0;

   // Calculate frameSize by searching for the position where it starts
   // and the position where it ends (posi and posf)
   do
   {
      bufferNumber++;
      bytesRead = fread(buffer, 1, BUFFER_SIZE, input);
      int C;
      if(bytesRead > 6)
      for (C = 0; C < bytesRead - 6; C++)
      {
         if (buffer[C    ] == 'F' && buffer[C + 1] == 'R' && buffer[C + 2] == 'A'
          && buffer[C + 3] == 'M' && buffer[C + 4] == 'E' && buffer[C + 5] == 0x0A)
         {
            switch(blockNumber)
            {
            case(0):
               posi = i + C + 6;
               break;
            case(1):
               posf = i + C - 1;
               break;
            }
            blockNumber++;
            C += 5;
         }
      }
      i += bytesRead;
   } while ( (bytesRead == BUFFER_SIZE) && (posf == 0) );

   // Reset input file and read/write only the frames
   frameSize = posf - posi + 1;
   fseek(input,posi,SEEK_SET);
   free(buffer);
   free(chunk);
   buffer = (char*)malloc(frameSize);
   do
   {
      bytesRead = fread(buffer, 1, frameSize, input);
      fwrite(buffer, frameSize, 1, output);
      fseek(input, 6, SEEK_CUR);
   }while(bytesRead == frameSize);

   fclose(input);
   fclose(output);

   return(1);
}
