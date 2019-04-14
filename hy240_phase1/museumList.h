#ifndef MUSEUM_LIST
#define MUSEUM_LIST


#define MAX_FLOOR_NUM 6

#include "roomSortedList.h"

typedef struct Museum{
	int museumId;
	char museumName[30];
	char museumAddress[30];
	ROOM * FL[MAX_FLOOR_NUM +1];
	struct Museum *next;
}MUSEUM;

/* Insert a new museum in the list */
void museumInsert(MUSEUM ** m, int museumId, char *museumName, char * museumAddress, unsigned int ** p , int f, unsigned int * roomNum);

/* Delete a museum with a specific Id from the list */
void museumDelete( MUSEUM ** m, int museumid);

/* Search for a museum with a specific Id */
MUSEUM * museumLookUp (MUSEUM *m, int museumid);

/* Print all the nodes of the list */
void museumPrint(MUSEUM * m);

/*Print a single museum*/
void museumSinglePrint(MUSEUM * m);

/*Find the floor of room with id roomId*/
int findFloor (MUSEUM *m, int roomId);



#endif
