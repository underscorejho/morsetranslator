
// main.c
// morse code translator
// Jared Henry Oviatt
//
//



#include "morse.h"



int main()
{

// initialize *FILEs and other vars
  FILE *inFile = NULL;
  FILE *outFile = NULL;
  FILE *keyFile = NULL;
  
  char keyArray[36][8];
  char userinput[50];
  
  char ch;
  char inFileName[20];
  char outFileName[20];
  char mode[3];

  int i = 0;

// read in key file
  keyFile = fopen("keyfile.txt", "r");
  fileErrorCheck(keyFile);
  
  readKeyFile(keyFile, keyArray);//////////////////// SEG FAULT HERE I THINK
  
  // TEST readKeyFile() // TEST
  //for (i = 0; i < 36; i++)
  //  printf("%s", keyArray[i]);
  // END TEST

// set up interface
//   infile outfile -mode

  printf("Please input your input file, your output file,\n and the mode you wold like to use.\n modes: \n   to morse -m\n   to text  -t\n\n  ex. input.txt output.txt -m\n:");
  scanf("%s", &userinput);
  printf("\n");
  
// read in user input

  i = 0;
  
  while(!isspace(userinput[i]))
  {
    inFileName[i] = userinput[i]
    i++;
  }
  
  i++;
  
  while(!isspace(userinput[i]))
  {
    outFileName[i - (strlen(inFileName) + 1)] = userinput[i]
    i++;
  }

  while(!isspace(userinput[i]))
  {
    mode[i - (strlen(inFileName) + 1 + strlen(outFileName) + 1)] = userinput[i]
    i++;
  }

  if(!strcmp(mode, "-m"))
  {
// text to morse : lookup array [use indicies of shifted ascii values]
  }
  else if(!strcmp(mode, "-t"))
  {
// morse to text : binary search tree
  }
  else
    printf("Sorry, that is not a valid mode\n");

  return 0;

}
