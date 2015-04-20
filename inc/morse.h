
// morse.h
// morse code translator
// Jared Henry Oviatt

// A 'wut' error is an error that should be impossible - mostly used for debugging


#ifndef MORSE_H
#define MORSE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// STRUCTS

struct Node {
  char ch;

  struct Node *Dot;
  struct Node *Dash;
};

// FUNCTION HEADERS

int checkArgs(int n, int argc);

int fileErrorCheck(FILE *aFile);

int checkModes(char *str);

int readFile(FILE *aFile, char **str);

// for -m
int populateKey(char *str, char key[][8]);

int toMorse(char *str, FILE *aFile, char key[][8]);

// for -t
struct Node *newNode();

struct Node *populateTree(char *str);

struct Node *asciiInit(char ch, char *str, struct Node *root);

int freeBT(struct Node *root);

int toText(char *str, FILE *aFile, struct Node *root);

char asciiGet(struct Node *root, char *str);

#endif
