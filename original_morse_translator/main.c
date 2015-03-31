
// Jared Henry Oviatt
// 11/26/2014
// 
// THIS PROGRAM converts morse code text into english plain text and vise-versa
// and uses both an array style table look-up and a binary tree look-up
//
// *** Lots of help from Travis Lane with the Binary Tree, though all code is my own. 
// 

#include "morse.h"

int main()
{

	int nconverted = 0, i = 0, n = 0, c = 0;
	char ch = '\0', buff = '\0', buffs[8];
	char conspec[8], inFileName[32], outFileName[32]; 
	char key[91][8];
	FILE *keyFile = NULL;
	FILE *BTkeyFile = NULL;
	FILE *iFile = NULL;
	FILE *oFile = NULL;
	Tree *myTree = (Tree *)malloc(sizeof(*myTree));

	// could have user choose mode and lookup mode earlier, and only initialize version to be used...

	for(i = 0; i < 91; i++)
		for(n = 0; n < 8; n++)
			key[i][n] = '\0';

	keyFile = fopen("key.txt", "r");
	fileErrorCheck(keyFile);

	for(i = 65; i < 91; i++)
	{
		fgets(key[i], 8, keyFile);
		addNull(key[i]);
	}

	for(i = 48; i < 58; i++)
	{
		fgets(key[i], 8, keyFile);
		addNull(key[i]);
	}
	fclose(keyFile);

	//LOAD BT
	BTkeyFile = fopen("btkey.txt", "r");
	fileErrorCheck(BTkeyFile);

	myTree->root = mtnNew();	// make sure there is root memory to build on top of

	while(1/*!feof(BTkeyFile) && ch != '9' /*<- kind of cheating here, feof wasn't working?*/)
	{
		i = 0;
		buff = fgetc(BTkeyFile);
		if(buff == EOF)
			break;		// while(!feof(BTkeyFile)) didn't work for while condition, not sure why. prefer this to alternate condition.
		ch = buff;
		for(i = 0; i < 8; i++)		// clear buffer
			buffs[i] = '\0';
		i = 0;
		while(buff != '\n')			// build morse string
		{
			buff = fgetc(BTkeyFile);
			buffs[i] = buff;
			i++;
		}
		myTree->root = initializeTree(ch, buffs, myTree->root);	// store char in tree
	}

	fclose(BTkeyFile);
	//BT LOADED

	//printtree(myTree->root);	//just checking its there	//pretty much same as freeMemory()

	//check array
	for(i = 65; i < 91; i++)
	{
		printf("%c ", i);
		printf("%s\n", key[i]);
	}

	for(i = 48; i < 58; i++)
	{
		printf("%c ", i);
		printf("%s\n", key[i]);
	}

	again:

	promptInput();
	scanf("%s%s%s", &conspec, &inFileName, &outFileName);
	checkInput(conspec, inFileName, outFileName);

	iFile = fopen(inFileName, "r");
	oFile = fopen(outFileName, "w");

	fileErrorCheck(iFile);
	fileErrorCheck(oFile);

	if(!strncmp(conspec, "-t\0", 3)) // convert to text
	{
		printf("\nChoose... Array Lookup<0> -OR- Binary Tree Lookup<1>\n");
		// I know, no error checking...
		scanf("%d", &c);

		if(!c)	// array lookup
		{
			while(!feof(iFile))
			{
				i = 0;
				for(n = 0; n < 8; n++)
					buffs[n] = '\0';
				buff = fgetc(iFile);
				while(buff == '-' || buff == '.')
				{
					buffs[i] = buff;
					i++;
					buff = fgetc(iFile);
				}
				if(i == 0)
					fputc(32, oFile);
				else
				{
					ch = toText(buffs, key);
					nconverted++;
					fputc(ch, oFile);
				}
			}
		}
		else if(c)	// binary lookup
		{
			while(!feof(iFile))
			{
				i = 0;
				for(n = 0; n < 8; n++)
					buffs[n] = '\0';
				buff = fgetc(iFile);
				while(buff == '-' || buff == '.')
				{
					buffs[i] = buff;
					i++;
					buff = fgetc(iFile);
				}
				if(i == 0)
					fputc(32, oFile);
				else
				{
					ch = BTlookup(buffs, myTree->root);
					nconverted++;
					fputc(ch, oFile);
				}
			}
		}
		else
			printf("ERROR: wut\n");	// wut error: error that should never happen
			
	}
	else if(!strncmp(conspec, "-m\0", 3)) // convert to morse
	{
		while(!feof(iFile))
		{
			buff = fgetc(iFile);
			if(!isspace(buff))
			{//convert
				if(isalpha(buff))
				fputs(key[toupper(buff)], oFile);
				fputc(32, oFile);	// space between letters
				nconverted++;
			}
			else if(buff == 32)		// / for spaces between words
				fputc('/', oFile);
			else
				fprintf(oFile, "%c", buff);
		}
	}
	else
		printf("ERROR: wut\n");

	printf("%d characters successfully converted\n\n", nconverted);

	printf("Convert more files? yes<1> no<0> \n");
	scanf("%d", &i);
	if(i)
		goto again;	// I know, shouldn't use goto... just a last minute repeat option.

	fclose(iFile);
	fclose(oFile);

	return 0;
}
