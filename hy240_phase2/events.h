#ifndef EVENTS
#define EVENTS


#define MAX_FLOORS_NUM 5


#include "artistBinaryTree.h"
#include "styleBinaryTree.h"
#include "museumList.h"
#include"roomDoublyLinkedTreeGuardNode.h"
#include "roomPaintingSortedBinaryTree.h"
#include "paintingLinkedListSorted.h"
#include "hashTablePaintings.h"

/* Insert a new artStyle in the list, and print the artstyle tree */
void S (int artStyleId, char * styleName, ARTSTYLE ** artStyleTree , ARTSTYLE * guard);

/* Insert a new artist in the list and print the artist list */
void A (int artistId, char * artistName, int YearOfBirth, int YearOfDeath, int artStyleId, ARTIST ** artist, ARTSTYLE ** L, ARTSTYLE *G);

/* Insert a new museum in the list and then prints the museum List */
void M(MUSEUM ** m, int museumId, char *museumName, char * museumAddress, int f , unsigned int ** p, unsigned int * roomNum);

/* Adds a new floor in the museum with r rooms */
void O(MUSEUM ** m, unsigned int museumId, unsigned int r, unsigned int *roomsIds);

/* Adds a new painting in the paintingList and in a specific room. Then prints the list of paintings*/
void N(int paintingId, char * paintingName, int artistId, int museumId,int floorNum,int roomId, MUSEUM ** m, ARTIST ** a, PAINTING ** PAINT, int num);

/* Move a painting from roomId to roomIddest */
void V(int paintingId, int museumId,int floorNum, int roomId, int museumIddest, int floordest, int roomIddest, MUSEUM ** m, PAINTING ** p, int num);

/* Move all the paintings from roomId to roomId_dest */
void L(int museumId, int floorNum,int roomId, int museumId_dest, int floorId_dest, int roomId_dest, MUSEUM ** m , PAINTING ** p, int num);

/* Merge rooms and delete the source list */
void G(int roomId, int roomId_dest, MUSEUM**m,PAINTING **PAINT, int num );

/* Adds a museum room and move paintings depanding on flag.*/
void R(int museumId, int floorNum, int roomId, int roomId_src, int flag, MUSEUM ** m, PAINTING ** p, int num);

/*Inserts in the roomId_dest all the paintings with artistId */
void I (int artistId,int museumId_dest, int floorNum_dest, int roomId_dest, MUSEUM **m, PAINTING ** PAINT , int num);

/*Inserts in the roomId_dest all the paintings with artStyleID */
void Y (int artStyleId,int museumId_dest, int floorNum_dest, int roomId_dest, MUSEUM **m, PAINTING **PAINT, int num);

/* Print the room Paintings, with complexity o(n)*/
void T (int museumId, int floorNum,int roomId, MUSEUM ** m, PAINTING ** PAINT, int num);

/*Prints all the data structures */

void P(MUSEUM **m,PAINTING ** PAINT, int num);
#endif
