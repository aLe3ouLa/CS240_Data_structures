#ifndef ROOMTREE
#define ROOMTREE

#include <stdlib.h>
#include "roomPaintingSortedBinaryTree.h"

typedef struct Room{
	int roomId;
	WORK *artP;
	struct Room *p;
	struct Room *lc;
	struct Room *rc;
}ROOM;

ROOM * guardNode ();
void roomTreeInsert (int roomId, ROOM ** roomList, ROOM * guardNode);
void roomTreeDelete (int roomId, ROOM ** roomList, ROOM * guardNode);
ROOM * roomTreeLookUp(int roomId, ROOM * roomList , ROOM * guardNode);
void roomRemoveAll (ROOM *roomTree, ROOM * guardNode);
void roomTreePrint(ROOM * roomList, ROOM * guard);

#endif
