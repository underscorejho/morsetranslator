
// main.c
// morse code translator
// Jared Henry Oviatt
//
//



#include "../inc/morse.h"

// argv[0] // program name (always is)
// argv[1] // file one // input file
// argv[2] // file two // output file
// argv[3] // mode // -m or -t // to morse or to text

int main(int argc, char *argv[])
{

/////////////////////////////// initialize variables //////////////////////////////////

  FILE *inFile = NULL;
  FILE *outFile = NULL;
  FILE *keyFile = NULL;

  char *keyStr = NULL;
  char *inStr = NULL;
  
  char keyArr[36][8];

/////////////////////////////// handle command line args //////////////////////////////

  // check number of command line args
  if(checkArgs(4, argc))
    return 1;

  // check argv[3] is a valid mode
  if(checkModes(argv[3]))
    return 1;

//////////////////////////////// handle files /////////////////////////////////////////

  // handle key file
  keyFile = fopen("txt/key.txt", "r");
  fileErrorCheck(keyFile);
  
  readFile(keyFile, &keyStr);

  fclose(keyFile);

  // handle input file
  inFile = fopen(argv[1], "r");
  fileErrorCheck(inFile);
  
  readFile(inFile, &inStr);

  fclose(inFile);

  // open output file for write
  outFile = fopen(argv[2], "w");
  fileErrorCheck(outFile);

//////////////////////////////// translate inputs to outputs //////////////////////////

  if(!strcmp(argv[3], "-m"))
  {
    // text to morse : lookup array [use indicies of shifted ascii values]
    populateKey(keyStr, keyArr);    
    toMorse(inStr, outFile, keyArr);
  }
  else if(!strcmp(argv[3], "-t"))
  {
    // morse to text : binary search tree
  }
  else
    printf("ERROR: wut: invalid mode encountered\n");

//////////////////////////////// close files, free memory, be done ////////////////////

  fclose(outFile);

  free(keyStr);
  free(inStr);

  return 0;

}
