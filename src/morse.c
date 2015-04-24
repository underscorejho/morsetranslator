
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
    printf("ERROR: file not opened properly : FILE * == NULL\n");
    return 1;
  }
  return 0;
} 

int checkModes(char *str)
{
  if((strcmp(str, "-m")) && (strcmp(str, "-t"))) // if first is wrong && second is wrong
  {
    printf("ERROR: not a valid mode\n");
    return 1;
  }
  return 0;
}

int readFile(FILE *aFile, char **str) // puts a file into a string
{
  int fileSize = 0;
  int i = 0;
  
  // count the length of the file string
  while(fgetc(aFile) != EOF)
    fileSize++;
  
  // malloc enough space for the string
  *str = malloc(sizeof(char) * (fileSize + 1 + 1)); // one for null, one for extra space
  if(!(*(str)))
    printf("ERROR: *str == NULL\n");

  // rewind() to the start of the file
  rewind(aFile);
  
  // put the file into a string
  for(i = 0; i < fileSize; i++)
    *(*str + i) = fgetc(aFile);
  *(*str + i - 1) = '\0';

  return 0;
}

// for -m
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
      key[n][m] = '\0';
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
    if(isspace(ch))
      fputc('/', aFile);
    if(!isalnum(ch))
      continue;
    ch = toupper(ch);
    if(isalnum(ch))
    {
      fputs(key[((int)ch) - 48], aFile);
      fputc(255, aFile);
    }
    else
      printf("ERROR: wut: unexpected character to translate: %c\n", ch);
  }

  return 0;
}

// for -t
struct Node *newNode()
{
  struct Node *node = NULL;
  
  node = malloc(sizeof(struct Node));
  
  node->Dot = NULL;
  node->Dash = NULL;

  return node;
}

struct Node *populateTree(char *str)
{
  struct Node *root = NULL;
  
  int i = 0;
  int n = 0;

  char ch = '\0';

  char morseStr[8];
  char morsech = '\0';
  
  root = newNode();

  for(i = 0; str[i]; i++)
  {
    ch = str[i];
    
    if(ch == '\n')
    {
      morseStr[n] = '\0';

      root = asciiInit(morsech, morseStr, root);

      for(n = 0; n < 8; n++)
        morseStr[n] = '\0';  
      n = 0;
    }
    else if(isspace(ch))
      continue;

    if(isalnum(ch))
    {
      morsech = ch;
    }
    else if(ch == '.' || ch == '-')
    {
      morseStr[n] = ch;
      n++;
    }
  }

  root->ch = 255;

  return root;
}

struct Node *asciiInit(char ch, char *str, struct Node *root)
{
  struct Node *node = NULL;

  if(!(*str))
    root->ch = ch;
  else
  {
    if(*str == '.')
    {
      if(!(root->Dot))
        root->Dot = newNode();
      node = root->Dot;
    }
    else
    {
      if(!(root->Dash))
        root->Dash = newNode();
      node = root->Dash;
    }

    asciiInit(ch, (str+1), node);
  }

  return root;
}

int freeBT(struct Node *root)
{
  if((root->Dot) || (root->Dash))
  {
    if(root->Dot)
      freeBT(root->Dot);
    if(root->Dash)
      freeBT(root->Dash);
  }
  else
      free(root);
  return 0;
}

int toText(char *str, FILE *aFile, struct Node *root)
{
  int i = 0;
  char ch = '\0';

  for(i = 0; str[i]; i++)
  {
    ch = str[i];
    
    if(isspace(ch))
      continue;
    else if(ch == '/')
      fputc(255, aFile);
    else if(ch == '.' || ch == '-')
    {
      fputc(asciiGet(root, (str+i)), aFile);
      while(!isspace(str[i]) && str[i])
        ++i;
    }
    else
    {
      printf("ERROR: non-morse character ('-', '.', '/') encountered.\n");
      return 1;
    }
  }

  return 0;
}

char asciiGet(struct Node *root, char *str)
{
  char ch = *str;

  if((*(str + 1)) != '.' && (*(str + 1)) != '-')
    return root->ch;
  else if(ch == '.')
    return asciiGet(root->Dot, (str+1));
  else if(ch == '-')
    return asciiGet(root->Dash, (str+1));

  printf("ERROR: wut\n");
  return -1;
}
