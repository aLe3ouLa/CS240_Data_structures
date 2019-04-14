#include "hashTablePaintings.h"
#include "paintingLinkedListSorted.h"
#include <stdlib.h>


int hashTableFunction(int paintingId, int m){

	return paintingId % m;

}


void paintingHTInsert(int paintingId , char * paintingName, int artistId, int museumId,int roomId, PAINTING ** PAINT, int num, ARTIST *  a, MUSEUM * m, int f){

	int pos  = hashTableFunction(paintingId,num);
	paintingInsert(paintingId, paintingName, artistId,museumId,roomId,a,m,f,&PAINT[pos]);

}

void paintingHTDelete(int paintingId, PAINTING ** PAINT, int m){

	int pos  = hashTableFunction(paintingId, m);
	paintingDelete(paintingId, &PAINT[pos]);

}

PAINTING * paintingHTLookUp(int paintingId, PAINTING ** PAINT, int m){

	int pos  = hashTableFunction(paintingId, m);
	PAINTING * temp = NULL;
	PAINTING * found = NULL;

	temp = (PAINTING *) PAINT[pos];

	found = paintingLookUp(paintingId,temp);

	return found;
}

void paintingHTPrint(PAINTING ** PAINT, int m, char * prefix){
	int i;
	for (i =0; i<m;i++){
		if (PAINT[i] != NULL){
			paintingPrint(PAINT[i], prefix);
	
		}
	}
}


void paintingHTIDprint(PAINTING ** PAINT, char * prefix, int m, int paintingId){

	int i;
	for (i =0; i<m;i++){
		if (PAINT[i] != NULL){
			paintingsIdprint(PAINT[i], paintingId,prefix);
	
		}
	}
}