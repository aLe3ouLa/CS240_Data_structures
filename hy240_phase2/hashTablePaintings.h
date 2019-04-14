#ifndef HASH
#define HASH

#include "paintingLinkedListSorted.h"

int hashTableFunction(int paintingId, int m);
void paintingHTInsert(int paintingId , char * paintingName, int artistId, int museumId,int roomId, PAINTING ** PAINT, int num, ARTIST *  a, MUSEUM * m, int f);
void paintingHTDelete(int paintingId, PAINTING ** PAINT, int m);
PAINTING * paintingHTLookUp(int paintingId, PAINTING ** PAINT, int m);
void paintingHTPrint(PAINTING ** PAINT, int m, char * prefix);
void paintingHTIDprint(PAINTING ** PAINT, char * prefix, int m, int paintingId);

#endif