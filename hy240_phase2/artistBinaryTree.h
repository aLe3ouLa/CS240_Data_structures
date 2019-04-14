#ifndef STYLEREDBLACKTREE
#define STYLEREDBLACKTREE

#include "styleBinaryTree.h"

typedef struct Artist {

	int artistId;
	char artistName[100];
	int yearOfBirth;
	int yearOfDeath;
	ARTSTYLE * artStylePtr;
	struct Artist * p;
	struct Artist *lc;
	struct Artist *rc;
}ARTIST;


void artistTreeInsert (int artistId, char * artistName, int yearOfBirth, int yearOfDeath,int styleId, ARTSTYLE * styleList, ARTSTYLE * guardNode, ARTIST ** artistList);
void artistTreeDelete (int artistId, ARTIST ** artistList);
ARTIST * artistTreeLookUp(int artistId, ARTIST * artistList);
void artistTreePrint(ARTIST * artistList);

#endif