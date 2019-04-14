#ifndef PAINTING_H
#define PAINTING_H

#include "artistBinaryTree.h"
#include "museumList.h"
#include "roomDoublyLinkedTreeGuardNode.h"


typedef struct Painting {

	int paintingId;
	char paintingName[100];
	ARTIST * artistPtr;
	MUSEUM *museumPtr;
	ROOM * roomPtr;
	struct Painting * next;
} PAINTING;

/*Insert a node in a sorted list */
void paintingInsert(int paintingId, char * paintingName, int artistId, int museumId,int roomId,ARTIST *  a, MUSEUM * m, int f, PAINTING ** paintingList);

/* Delete a node with the specific id*/
void paintingDelete (int paintingId, PAINTING **paintingList);

/* Remove all the nodes of the list */
void paintingRemoveAll(PAINTING ** paintingList);

/*Search the roomPainting with the specific paintingId*/
PAINTING * paintingLookUp(int paintingId, PAINTING * paintingList);

/* Returns how many nodes the list has */
int paintingGetLength(PAINTING ** paintingList);

/* Print all the roomPaintings */
void paintingPrint(PAINTING * paintingList, char *prefix);

void paintingsIdprint(PAINTING *p, int paintingId, char *prefix);

#endif
	