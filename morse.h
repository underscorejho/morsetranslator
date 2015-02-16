
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

int fileErrorCheck(FILE *aFile);

int readKeyFile(FILE *aFile, char arr[36][8]);

#endif
