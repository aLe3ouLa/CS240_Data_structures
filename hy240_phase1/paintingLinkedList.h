#ifndef PAINTING_LIST_H
#define PAINTING_LIST_H

#include "ArtistLinkedList.h"
#include "museumList.h"
#include "roomSortedList.h"


typedef struct Painting {
	int paintingId;
	char paintingName[30];
	ARTIST *artistPtr;
	MUSEUM *museumPtr;
	ROOM *roomPtr;
	struct Painting *next;
	struct Painting *prev;
}PAINTING;

/*Insert in a doubly linked list */
void paintingInsert(PAINTING **p , int paintingId, char * paintingName, int artistId, int museumId,int roomId, ARTIST ** a, MUSEUM ** m, ARTIST * G, int f);

/* Delete a node with id "paintingId"*/
void paintingDelete (PAINTING **p, int paintingId);

/* Search for a node with id "paintingId"*/
PAINTING * paintingLookUp(PAINTING * p, int paintingId);

/*Print all the elements of the paintinglist */
void paintingPrint(PAINTING * p, char *prefix);

/*Prints an element from the list with paintingId */
void paintingsIdprint(PAINTING *p, int paintingId, char *prefix);

#endif
