
// morse.h
// morse code translator
// Jared Henry Oviatt

// FUNCTION HEADERS

#ifndef MORSE_H
#define MORSE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int checkArgs(int n, int argc);

int fileErrorCheck(FILE *aFile);

int checkModes(char *str);

int readFile(FILE *aFile, char *str);

int populateKey(char *str, char key[][8]);

int toMorse(char *str, FILE *aFile, char key[][8]);

#endif
