
// morse.c
// morse code translator
// Jared Henry Oviatt

// FUNCTION DEFINITIONS

#include "../inc/morse.h"

int checkArgs(int n, int argc)
{
  if(n != argc)
  {
    printf("ERROR: wrong number of args\n");
    return 1;
  }
  return 0;
}

int fileErrorCheck(FILE *aFile)
{
  if(aFile == NULL)
  {
    printf("ERROR: file not opened properly : *FILE == NULL\n");
    return 1;
  }
  return 0;
} 

int checkModes(char *str)
{
  if((strcmp(str, "-m")) || (strcmp(str, "-t")))
  {
    printf("ERROR: not a valid mode\n");
    return 1;
  }
  return 0;
}

int readFile(FILE *aFile, char *str) // puts a file into a string
{
  int fileSize = 0;
  int i = 0;
  
  // count the length of the file string
  while(fgetc(aFile) != EOF)
    fileSize++;
  
  // malloc enough space for the string
  str = (char *)malloc(sizeof(char) * (fileSize + 1 + 1)); // one for null, one for extra space

  // rewind() to the start of the file
  rewind(aFile);
  
  // put the file into a string
  for(i = 0; i < fileSize; i++)
    *(str + i) = fgetc(aFile);
  *(str + i - 1) = '\0';

  return 0;
}

int populateKey(char *str, char key[][8])
{
  int i = 0;
  char ch = '\0';

  int n = 0, m = 0;

  for(i = 0; str[i]; i++)
  {
    ch = str[i];
    if(isspace(ch))
      continue;
    if(isalnum(ch))
    {
      n = (int)ch - 48;
      m = 0;
    }
    else if(ch == '.' || ch == '-')
    {
      key[n][m] = ch;
      m++;
    }
  }

  return 0;
}

int toMorse(char *str, FILE *aFile, char key[][8])
{
  int i = 0;
  char ch = '\0';

  for(i = 0; str[i]; i++)
  {
    ch = str[i];
    if(!isspace(ch))
      fputc('/', aFile);
    if(!isalnum(ch))
      continue;
    ch = toupper(ch);
    if(isalnum(ch))
    {
      fputs(key[((int)ch) - 48], aFile);
      fputc('/', aFile);
    }
    else
      printf("ERROR: wut: unexpected character to translate\n");
  }

  return 0;
}
