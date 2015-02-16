
// morse.c
// morse code translator
// Jared Henry Oviatt

// FUNCTION DEFINITIONS

#include "morse.h"

int fileErrorCheck(FILE *aFile)
{
  if(aFile == NULL)
  {
    printf("ERROR: file not opened properly : *FILE == NULL\n");
    return 1;
  }
  return 0;
} 

int readKeyFile(FILE *aFile, char arr[36][8])
{
  char ch = '\0';
  int i = 0;
  int line = 0;
  
  for(line = 0; line < 36; line++) // initialize all to NULL
    for(i = 0; i < 8; i++)
      arr[line][i] = '\0';

  line = 0;
  i = 0;

  while(!feof(aFile))
  {
    ch = fgetc(aFile); // get letter // do nothing
    ch = fgetc(aFile); // get space  // do nothing
    i = 0;	       // make sure i = 0
    while(ch != '\n')  // newline gets included after morse in array
    {
      ch = tolower(fgetc(aFile));
      arr[line][i] = ch;
      i++;
    }
    line++;
  }

  return 0;
}
