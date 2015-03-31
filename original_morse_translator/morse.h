
#ifndef MORSE_H
#define MORSE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

// BT STRUCTS

typedef struct mtn{
	char ASCII;
	int isinit;
	struct mtn *dah;
	struct mtn *dit;
} MTN;

typedef struct tree{
	struct mtn *root;
} Tree;


// FUNCTION HEADERS

void fileErrorCheck(FILE *aFile);			// checks a file was opened properly (no longer initialized to NULL) 
void promptInput();							// prints a series of prompts for input
void checkInput(char *cspec, char *ifname, char *ofname);
											// makes sure input is valid
char toText(char *mchar, char key[][8]);	// accepts string of morse character, returns english character
void addNull(char *str);					// adds null to end of string


struct mtn* mtnNew();						// makes a new node for the tree
struct mtn *initializeTree(char ch, char *mch, struct mtn *root);
											// initializes nodes to values
char BTlookup(char *mch, struct mtn *root);	// look up a morse traslation using a binary tree
void freeMemory(struct mtn *root);			// free all malloc'd memory

void printtree(struct mtn *root);			// prints tree out of order	// uses freeMemory's model

#endif