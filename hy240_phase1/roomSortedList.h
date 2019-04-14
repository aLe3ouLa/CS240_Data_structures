#ifndef ROOMSORTEDLIST_H_INCLUDED
#define ROOMSORTEDLIST_H_INCLUDED

#include "roomPaintingSortedList.h"

typedef struct Room{
    int roomId;
    ROOMPAINTING *artPtr;
    struct Room *next;
}ROOM;

/*Insert a new room in the rooms list. The rooms list is sorted.*/
void roomInsert(int roomId, ROOM ** R);

/* Deletes a room with a specific id*/
void roomDelete (int roomId, ROOM **R);

/* Print the elements of the room */
void roomPrint(ROOM * l);

/* Remove all the rooms from the list*/
void roomRemoveAll(ROOM ** R);

/* Search for a room with a specific id*/
ROOM * roomLookUp(int roomId, ROOM * R);

#endif
