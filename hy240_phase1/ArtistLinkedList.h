#ifndef ARTISTLINKED
#define ARTISTLINKED

#include "StyleLinkedList.h"

typedef struct Artist{
    int artistId;
    char artistName[32];
    int YearOfBirth;
    int YearOfDeath;
    ARTSTYLE * artStylePtr;
    struct Artist * next;
}ARTIST;

/*Create the guard Node and insert it in the list */
ARTIST * guardNode (ARTIST ** artistList);

/*Insert a new artist in the list */
void artistInsert(int, char *, int, int, int, ARTIST ** artistList,ARTSTYLE **);

/* Deletes an artist with a specific id from the list */
void artistDelete(int artistId, ARTIST ** artistList, ARTIST * guardNode );

/* Removes all the nodes of the list */
void artistRemoveAll(ARTIST ** artistList, ARTIST * guardNode);

/*Prints the elements of the artist List except guard Node.*/
void artistPrint(ARTIST * artistList, ARTIST * guardNode);

/*Search a node with specific artistId*/
ARTIST * artistLookUp(int artistId, ARTIST * artistList, ARTIST * guardNode);

#endif
