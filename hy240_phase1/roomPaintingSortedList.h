#ifndef ROOM_PAINTING_H
#define ROOM_PAINTING_H

typedef struct RoomPainting{
    int paintingId;
    struct RoomPainting *next;
}ROOMPAINTING;

/*Insert a node in a sorted list */
void roomPaintingInsert(int paintingId, ROOMPAINTING ** R);

/* Delete a node with the specific id*/
void roomPaintingDelete (int paintingId, ROOMPAINTING **R);

/* Print all the roomPaintings */
void roomPaintingPrint(ROOMPAINTING * l);

/* Remove all the nodes of the list */
void roomPaintingRemoveAll(ROOMPAINTING ** R);

/*Search the roomPainting with the specific paintingId*/
ROOMPAINTING * roomPaintingLookUp(int paintingId, ROOMPAINTING * R);

/*Insert at start of the list, for better complexity*/
void roomPaintingInsert_start(ROOMPAINTING **R, int paintingId);

/* Returns how many nodes the list has */
int roomPaintingGetLength(ROOMPAINTING **R);

#endif