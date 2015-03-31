
#include "morse.h"

// FUNCTION DEFINITIONS

void fileErrorCheck(FILE *aFile)
{
	if(aFile == NULL)
		printf("ERROR: file(s) not opened properly");
}

void promptInput()
{
	printf("\n");
	printf("This is a program to translate morse code to and from english text...\n");
	printf("\n");
	printf("Please input conversion specifier, input file name, output file name\n");
	printf("Conversion Specifiers\t: '-m' To Morse Code\n");
	printf("\t\t\t: '-t' To English Text\n");
	return;
}

void checkInput(char *cspec, char *ifname, char *ofname)
{
	if(strncmp(cspec, "-m\0", 3) && strncmp(cspec, "-t\0", 3))	//if cspec is neither -m or -t
		printf("ERROR: conversion specifier invalid\n");
	// check for file type
	// maybe do something to try again?
	return;
}

char toText(char *mchar, char key[][8])
{
	char echar = '\0';
	int i;

	for(i = 65; i < 91; i++)
		if(!strcmp(mchar, key[i]))
		{
			echar = i;
			return echar;
		}

	for(i = 48; i < 58; i++)
		if(!strcmp(mchar, key[i]))
		{
			echar = i;
			return echar;
		}

	return echar;
}

void addNull(char *str)
{
	int i = 0;
	while(str[i] == '-' || str[i] == '.')
		i++;
	str[i] = '\0';

	return;
}


struct mtn* mtnNew()
{
	struct mtn *node;
	node = (struct mtn *)malloc(sizeof(struct mtn));
	node->ASCII = '\0';
	node->isinit = 0;
	node->dit = NULL;
	node->dah = NULL;
	return node;
}

struct mtn *initializeTree(char ch, char *mch, struct mtn *root)
{
	struct mtn *curr = NULL;

	int i = 0;

	curr = root;

	if(strlen(mch) == 1)
	{
		if(mch[i] == '-')
		{
			curr-> dah = mtnNew();
			curr-> dah-> ASCII = ch;
			curr-> dah-> isinit++;
		}
		else if(mch[i] == '.')
		{
			curr-> dit = mtnNew();
			curr-> dit-> ASCII = ch;
			curr-> dit-> isinit++;
		}
		else
			printf("wut");
	}

	
	while(mch[i] != '\n')
	{
		if(mch[i] == '-')
		{
			if(curr-> dah == NULL)
				curr-> dah = mtnNew();
			curr = curr-> dah;
			i++;
		}
		else if(mch[i] == '.')
		{
			if(curr-> dit == NULL)
				curr->dit = mtnNew();
			curr = curr->dit;
			i++;
		}
	}

	curr-> ASCII = ch;
	curr-> isinit++;

	return root;
}

char BTlookup(char *mch, struct mtn *root)
{
	struct mtn *curr = NULL;

	int i = 0;
	char ch = '\0';

	curr = root;

	if(strlen(mch) == 1)
	{
		if(mch[i] == '-')
		{
			if(curr-> dah-> isinit)
				ch = curr-> dah-> ASCII;
			else
				printf("ERROR: not initialized\n");
		}
		else if(mch[i] == '.')
		{
			if(curr-> dit-> isinit)
				ch = curr-> dit-> ASCII;
			else
				printf("ERROR: not initialized\n");
		}
		else
			printf("wut");
	}

	
	while(mch[i] != '\0')
	{
		if(mch[i] == '-')
		{
			curr = curr-> dah;
			i++;
		}
		else if(mch[i] == '.')
		{
			curr = curr-> dit;
			i++;
		}
	}

	if(curr-> isinit)
		ch = curr-> ASCII;
	else
		printf("ERROR: not initialized\n");

	return ch;
}

void freeMemory(struct mtn *root)
{
	if(root)
	{
		freeMemory(root->dah);
		freeMemory(root->dit);
		free(root);
	}

	return;
}

void printtree(struct mtn *root)
{
	if(root)
	{
		printtree(root->dah);
		printtree(root->dit);
		printf("%c\n", root->ASCII);
	}

	return;
}
