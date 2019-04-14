#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "events.h"



void S (int artStyleId, char * styleName, ARTSTYLE ** L ){
	/* Insert a new artStyle in the list, and print the artstyle list */
	artStyleInsert(artStyleId, styleName, L);
	printf("S %d %s DONE\n", artStyleId, styleName);
	printf(" List of Art Styles: \n");
	artStylesPrint(*L);
}

void A (int artistId, char * artistName, int YearOfBirth, int YearOfDeath, int artStyleId, ARTIST ** artist, ARTSTYLE ** L, ARTIST *G){
	/* Insert a new artist in the list and print the artist list */
	artistInsert(artistId, artistName, YearOfBirth, YearOfDeath, artStyleId, artist,L);
	printf("A %d %s %d %d %d DONE\n", artistId, artistName, YearOfBirth, YearOfDeath, artStyleId);
	printf(" List of Artists: \n");
	artistPrint(*artist, G);
}

void M(MUSEUM ** m, int museumId, char *museumName, char * museumAddress, int f , unsigned int ** p, unsigned int * roomNum){
	/* Insert a new museum in the list and then prints the museum List */

	museumInsert(m,museumId,museumName, museumAddress, p,f, roomNum);
	printf("M %d %s %s DONE\n", museumId,museumName,museumAddress);
	printf(" List Of Museum:\n");
	museumPrint(*m);

}

void O(MUSEUM ** m, unsigned int museumId, unsigned int r, unsigned int * roomsIds){

	/* Adds a new floor in the museum with r rooms */
	MUSEUM * temp = *m;
	MUSEUM * found_museum = NULL;
	unsigned int i = 0, j = 0;
	int empty_room = -1;

	found_museum = museumLookUp(temp,museumId); /* Find the museum */

	for (;j < MAX_FLOOR_NUM; j++){ /* Check if there is space for a floor to add. There is space when is MAX_ROOMS some floors are NULL.*/
		if (found_museum->FL[j] == NULL){
			empty_room = j;
			break;
		}
	}

	if (empty_room == -1) return;

	for (;i < r; i++){
		roomInsert(roomsIds[i],&found_museum->FL[empty_room]); /* Inserts the rooms */
	}

	printf("O  %d %d",museumId,r);
	for ( i = 0; i<r;i++){
		printf("%d ",roomsIds[i]);
	}
	printf(" DONE\n");
	printf(" List Of Museum:\n");
	museumSinglePrint(found_museum);

}

void N(int paintingId, char * paintingName, int artistId, int museumId,int floorNum,int roomId, PAINTING ** p, MUSEUM ** m, ARTIST ** a,ARTIST ** G){

	/* Adds a new painting in the paintingList and in a specific room. Then prints the list of paintings*/
	ROOM * ptr = NULL;
	MUSEUM * temp = *m;

	paintingInsert(p,paintingId,paintingName,artistId,museumId,roomId,a,m,*G,floorNum);

	while(temp){
		if(temp->museumId == museumId){
			if (ptr = roomLookUp(roomId,temp->FL[floorNum])){
				roomPaintingInsert(paintingId,&ptr->artPtr);
				break;
			}
		}
		temp = temp->next;
	}

	printf("N  <%d> %s %d %d <%d> %d DONE\n",paintingId,paintingName, artistId , museumId, floorNum, roomId);
	printf(" List Of Paintings:\n");
	paintingPrint(*p, "   ");
}

void V(int paintingId, int museumId,int floorNum, int roomId, int museumIddest, int floordest, int roomIddest, MUSEUM ** m, PAINTING ** p){
	/* Move a painting from roomId to roomIddest */
	PAINTING * found_painting = NULL;
	PAINTING * temp = *p;
	ROOM * ptr = NULL;
	ROOM * ptrdel = NULL;
	MUSEUM * tempdel = *m;
	MUSEUM * tempins = *m;
	ROOMPAINTING *rptemp = NULL;

	/* find the painting that we're going to move */
	found_painting = paintingLookUp (temp,paintingId);

	/* find the room we're going to delete it from */
	ptrdel = roomLookUp(roomId, museumLookUp(*m, museumId)->FL[floorNum]);
	/* delete it */
	roomPaintingDelete(paintingId, &found_painting->roomPtr->artPtr);

	/* find the museum we're going to put the painting to */
	tempins = museumLookUp(*m, museumIddest);
	/* find the room in the museum we're going to put it */
	ptr = roomLookUp(roomIddest, tempins->FL[floordest]);
	/* insert it there */
	roomPaintingInsert(paintingId, &ptr->artPtr);
	/* fix the pointers */
	found_painting->roomPtr = ptr;
	found_painting->museumPtr = tempins;

	printf("V  %d %d %d %d %d %d %d DONE\n",paintingId,museumId, floorNum, roomId, museumIddest, floordest, roomIddest);

	printf(" List Of Paintings of %d:\n", roomId);

	rptemp = ptrdel->artPtr;
	while(rptemp != NULL){
		paintingsIdprint(*p,rptemp->paintingId, "   ");
		rptemp = rptemp->next;
	}

	printf(" List Of Paintings of %d:\n", roomIddest);

	rptemp = ptr->artPtr;
	while(rptemp != NULL){
		paintingsIdprint(*p,rptemp->paintingId, "   ");
		rptemp = rptemp->next;
	}
}

void L(int museumId, int floorNum,int roomId, int museumId_dest, int floorId_dest, int roomId_dest, MUSEUM ** m , PAINTING ** p){

	/* Move all the paintings from roomId to roomId_dest */
	PAINTING * found_painting = NULL;
	PAINTING * temp = *p;
	MUSEUM * tempdel = *m;
	MUSEUM * tempins = museumLookUp(*m, museumId_dest);
	ROOM * ptr = roomLookUp(roomId_dest, tempins->FL[floorId_dest]);
	ROOM * ptrdel = roomLookUp(roomId, museumLookUp(*m, museumId)->FL[floorNum]);
	ROOMPAINTING *rptemp = NULL;

	while(ptrdel->artPtr != NULL) {
		/* find the painting that we're going to move */
		found_painting = paintingLookUp (temp,ptrdel->artPtr->paintingId);
		/* delete it */
		roomPaintingDelete(ptrdel->artPtr->paintingId, &ptrdel->artPtr);
		/* insert it there */
		roomPaintingInsert(found_painting->paintingId, &ptr->artPtr);
		/* fix the pointers */
		found_painting->roomPtr = ptr;
		found_painting->museumPtr = tempins;
	}

	printf("L   %d %d %d %d %d %d DONE\n",museumId, floorNum, roomId, museumId_dest, floorId_dest, roomId_dest);

	printf(" List Of Paintings:\n");
	paintingPrint(*p, "   ");

}

void G(int roomId, int roomId_dest, MUSEUM**m,PAINTING **p ){
	/* Merge rooms with complexity O(n1+n2). after we merge the rooms in a temp list we insert it in the room at start because they are already sorted.
	* then we delete the source list */
	MUSEUM * tempmuseum = *m;
	MUSEUM * tempmuseumdest = *m;
	ROOM * ptrroom = NULL;
	ROOM * ptrroomdest = NULL;
	ROOMPAINTING *source, *dest, *final;
	int museumId_source, floor_src;

	int i = 0;

	while(tempmuseum) {
		int f = findFloor(tempmuseum, roomId);

		if(f >= 0) {
			if(ptrroom = roomLookUp(roomId, tempmuseum->FL[f])) {
				break;
			}
		}
		tempmuseum = tempmuseum->next;
	}

	while(tempmuseumdest) {
		int f = findFloor(tempmuseumdest, roomId_dest);

		if(f >= 0) {
			if(ptrroomdest = roomLookUp(roomId_dest, tempmuseumdest->FL[f])) {
				break;
			}
		}
		tempmuseumdest = tempmuseumdest->next;
	}

	source = ptrroom->artPtr;
	dest = ptrroomdest->artPtr;
	final = NULL;

	while (source!= NULL && dest !=NULL){

		if (source->paintingId > dest->paintingId){
			roomPaintingInsert_start(&final, dest->paintingId);
			dest = dest->next;
		}
		else{
			roomPaintingInsert_start(&final,source->paintingId);
			source = source->next;
		}

	}

	/*In case one of the 2 lists has still elements */
	while (source!=NULL){
			roomPaintingInsert_start(&final, source->paintingId);
			source = source->next;
	}
	while(dest!=NULL){

			roomPaintingInsert_start(&final, dest->paintingId);
			dest = dest->next;
	}

	roomPaintingRemoveAll(&ptrroom->artPtr);
	roomPaintingRemoveAll(&ptrroomdest->artPtr);


	while(final != NULL){
		PAINTING *found_painting = paintingLookUp(*p, final->paintingId);
		found_painting->museumPtr = tempmuseumdest;
		found_painting->roomPtr = ptrroomdest;
		roomPaintingInsert_start(&ptrroomdest->artPtr, final->paintingId);
		final = final->next;
	}

	museumId_source = tempmuseum->museumId;
	floor_src = findFloor(tempmuseum,roomId);

	roomDelete(roomId,&tempmuseum->FL[findFloor(tempmuseum,roomId)]);
	printf("G   %d %d %d %d %d %d DONE\n",museumId_source, floor_src, roomId, tempmuseumdest->museumId, findFloor(tempmuseumdest,roomId_dest), roomId_dest);
	printf(" List of Paintings: \n");
	paintingPrint(*p, "   ");
}

void R(int museumId, int floorNum, int roomId, int roomId_src, int flag, MUSEUM ** m, PAINTING ** p){
	/* Adds a museum room and move paintings depanding on flag. If the flag >0 moves the paintings with artStyle == flag.
	If the flag == -1 moves the half paintings. */
	MUSEUM * museumdest = *m;
	MUSEUM * museumSource = *m;
	ROOM * sourceRoom = NULL;
	ROOM * destRoom = NULL;
	PAINTING * tempPaint = NULL;
	PAINTING * tempP = *p;
	PAINTING * delP = *p;
	ARTSTYLE * tempStyle= NULL;
	ROOMPAINTING * temp = NULL;
	ROOMPAINTING *rptemp  =NULL;
	ROOMPAINTING * source = NULL;
	int i = 0, length = 0;

	museumdest = museumLookUp(*m,museumId);
	roomInsert(roomId,&museumdest->FL[floorNum]);
	destRoom = roomLookUp(roomId, museumdest->FL[floorNum]);

	while(museumSource) {
		int f = findFloor(museumSource, roomId_src);

		if(f >= 0) {
			if(sourceRoom = roomLookUp(roomId_src, museumSource->FL[f])) {
				break;
			}
		}
		museumSource = museumSource->next;
	}


	temp = sourceRoom->artPtr;
	source = sourceRoom->artPtr;

	if (source!=NULL){
		if (flag >0){
			while (temp){
				ROOMPAINTING *ptr = temp->next;
				tempPaint = paintingLookUp(tempP,temp->paintingId);

				if (tempPaint->artistPtr->artStylePtr->artStyleId == flag){
					roomPaintingInsert(tempPaint->paintingId,&destRoom->artPtr);
					tempPaint->roomPtr = destRoom;
					tempPaint->museumPtr = museumdest;
					roomPaintingDelete(temp->paintingId, &sourceRoom->artPtr);
				}
				temp = ptr;
			}
		}
		else if (flag == -1){


			length = roomPaintingGetLength(&temp);
			length = length/2;
			printf ("length: %d\n",length);
			i = 0;
			while (temp && i<length){
				ROOMPAINTING *ptr = temp->next;
				tempPaint = paintingLookUp(tempP,temp->paintingId);
				roomPaintingInsert(tempPaint->paintingId,&destRoom->artPtr);
				tempPaint->roomPtr = destRoom;
				tempPaint->museumPtr = museumdest;
				roomPaintingDelete(temp->paintingId, &sourceRoom->artPtr);
				i++;
				temp = ptr;
			}

		}
	}

	printf("R  %d %d %d %d %d DONE\n",museumId, floorNum, roomId, roomId_src, flag);

	printf(" List Of Paintings of %d:\n", roomId_src);

	rptemp = sourceRoom->artPtr;
	while(rptemp != NULL){
		paintingsIdprint(*p,rptemp->paintingId, "   ");
		rptemp = rptemp->next;
	}

	printf(" List Of Paintings of %d:\n", roomId);

	rptemp = destRoom->artPtr;
	while(rptemp != NULL){
		paintingsIdprint(*p,rptemp->paintingId, "   ");
		rptemp = rptemp->next;
	}
}


void I (int artistId,int museumId_dest, int floorNum_dest, int roomId_dest, MUSEUM **m, PAINTING **p){
	/*Inserts in the roomId_dest all the paintings with artistId */
	MUSEUM * tempMuseum = *m;
	ROOM * tempRoom = NULL;
	ROOM * room = NULL;
	PAINTING * tempPaint = NULL;
	PAINTING * temp = *p;
	ROOMPAINTING * rpptr = NULL;
	ROOMPAINTING * rp = NULL;
	int i = 0;


	tempRoom = roomLookUp(roomId_dest,museumLookUp(tempMuseum, museumId_dest)->FL[floorNum_dest]);
	while (tempMuseum){
		for (i = 0;i<MAX_FLOOR_NUM;i++){
			room = tempMuseum->FL[i];
			while (room && room!=tempRoom){
				rpptr = room->artPtr;
				while (rpptr ){
					ROOMPAINTING * ptr = rpptr->next;
					tempPaint = paintingLookUp(temp,rpptr->paintingId);
					if (tempPaint->artistPtr->artistId == artistId){
						roomPaintingInsert(tempPaint->paintingId, &tempRoom->artPtr );
						tempPaint->roomPtr = tempRoom;
						tempPaint->museumPtr = museumLookUp(*m,museumId_dest);
						roomPaintingDelete(tempPaint ->paintingId, &room->artPtr);
					}
					rpptr = ptr;

				}
				room = room->next;
			}
		}
		tempMuseum = tempMuseum->next;
	}

	printf("I  <%d> %d %d <%d> DONE\n",artistId,museumId_dest, floorNum_dest , roomId_dest);

	paintingPrint(*p, "   ");

}

void Y (int artStyleId,int museumId_dest, int floorNum_dest, int roomId_dest, MUSEUM **m, PAINTING **p){
	/*Inserts in the roomId_dest all the paintings with artStyleID */
	MUSEUM * tempMuseum = *m;
	ROOM * tempRoom = NULL;
	ROOM * room = NULL;
	PAINTING * tempPaint = NULL;
	PAINTING * temp = *p;
	ROOMPAINTING * rpptr = NULL;
	ROOMPAINTING * rp = NULL;
	int i = 0;


	tempRoom = roomLookUp(roomId_dest,museumLookUp(tempMuseum, museumId_dest)->FL[floorNum_dest]);
	while (tempMuseum){
		for (i = 0;i<MAX_FLOOR_NUM;i++){
			room = tempMuseum->FL[i];
			while (room && room!=tempRoom){
				rpptr = room->artPtr;
				while (rpptr ){
					ROOMPAINTING * ptr = rpptr->next;
					tempPaint = paintingLookUp(temp,rpptr->paintingId);
					if (tempPaint->artistPtr->artStylePtr->artStyleId == artStyleId){
						roomPaintingInsert(tempPaint->paintingId, &tempRoom->artPtr);
						tempPaint->roomPtr = tempRoom;
						tempPaint->museumPtr = museumLookUp(*m,museumId_dest);
						roomPaintingDelete(tempPaint ->paintingId, &room->artPtr);
					}
					rpptr = ptr;

				}
				room = room->next;
			}
		}
		tempMuseum = tempMuseum->next;
	}

	printf("Y  <%d> %d %d <%d> DONE\n",artStyleId,museumId_dest, floorNum_dest , roomId_dest);

	paintingPrint(*p, "   ");


}

void T (int museumId, int floorNum,int roomId, MUSEUM ** m, PAINTING ** p){
	/* Print the room Paintings, with complexity o(n)*/
	MUSEUM * tempM = *m;
	ROOM * temp = NULL;
	ROOMPAINTING * rp = NULL;
	PAINTING * tempPainting = NULL;

	tempPainting = *p;
	temp = roomLookUp(roomId, museumLookUp(tempM,museumId)->FL[floorNum]);
	rp = temp->artPtr;

	printf("T %d %d %d DONE\n", museumId, floorNum,roomId);
	printf (" List of Paintings\n");
	while(tempPainting) {
		if(tempPainting->roomPtr == temp) {
			printf("  %d %s %d %s\n",tempPainting->paintingId, tempPainting->paintingName,tempPainting->artistPtr->artistId, tempPainting->artistPtr->artistName);
		}
    tempPainting = tempPainting->next;
	}

}

static void _P(MUSEUM *m, PAINTING *p) {
	ROOM * room = NULL;
	ROOMPAINTING *rp = NULL;
	int flag = 1;
	int i = 0;

	/*recursive printing of the elements */
	if(m->next != NULL)
		_P(m->next, p);

	printf("  <%d> <%s> <%s>\n",m->museumId,m->museumName, m->museumAddress);

	for (i=0; i<MAX_FLOOR_NUM; i++){
		flag = 1;
		printf("\tFL[%d]:", i);
		room = m->FL[i];
		if (room == NULL){
			printf("\tNULL\n");
		}

		while(room){
			rp = room->artPtr;
			printf("%s%d\n", flag ? "\t" : "\t\t", room->roomId);
			flag = 0;
			while (rp){
				paintingsIdprint(p, rp->paintingId, "\t\t   ");
				rp = rp->next;
			}
			room = room->next;
		}
	}
}

void P(MUSEUM **m,PAINTING **p){

	/*Prints all the data structures */
	printf("P DONE\n");

	_P(*m, *p);
}

