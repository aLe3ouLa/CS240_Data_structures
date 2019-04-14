#ifndef ROOMPAINTING_TREE
#define ROOMPAINTING_TREE


typedef struct RoomPainting{
	int paintingId;
	int numOfChNodes;
	struct RoomPainting *lc;
	struct RoomPainting *rc;
}WORK;


void roomPaintingTreeInsert (int roomPaintingId, WORK** roomPaintingList);
void roomPaintingTreeDelete (int roomPaintingId, WORK ** roomPaintingList);
WORK * roomPaintingTreeLookUp(int roomPaintingId, WORK * roomPaintingList);
void roomPaintingTreePrint(WORK * roomPaintingList);
void TreePrint(WORK *, void (*visit)(WORK *, void *, int), void *, int );
int getLength (WORK * );
#endif