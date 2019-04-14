#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "stack.h"
#include "events.h"



void S (int artStyleId, char * styleName, ARTSTYLE ** artStyleTree , ARTSTYLE * guard){
	/* Insert a new artStyle in the list, and print the artstyle list */
	//artStyleInsert(artStyleId, styleName, L);
	artStyleInsert(artStyleId,styleName, artStyleTree,guard);
	printf("S %d %s DONE\n", artStyleId, styleName);
	printf(" Tree of Art Styles: \n");
	//artStylesPrint(*L);
	artStylesPrint(*artStyleTree,guard);
}

void A (int artistId, char * artistName, int YearOfBirth, int YearOfDeath, int artStyleId, ARTIST ** artist, ARTSTYLE ** L, ARTSTYLE *G){
	/* Insert a new artist in the list and print the artist list */
	artistTreeInsert(artistId,artistName,YearOfBirth,YearOfDeath,artStyleId,*L,G,artist);
	printf("A %d %s %d %d %d DONE\n", artistId, artistName, YearOfBirth, YearOfDeath, artStyleId);
	printf(" Tree of Artists: \n");
	artistTreePrint(*artist);
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

	found_museum->G[empty_room] = guardNode();
	for (;i < r; i++){
		
		roomTreeInsert(roomsIds[i],&found_museum->FL[empty_room],found_museum->G[empty_room]); /* Inserts the rooms */
	}

	printf("O  %d %d ",museumId,r);
	for ( i = 0; i<r;i++){
		printf("%d ",roomsIds[i]);
	}
	printf(" DONE\n");
	printf(" List Of Museum:\n");
	museumSinglePrint(found_museum);

}

void N(int paintingId, char * paintingName, int artistId, int museumId,int floorNum,int roomId, MUSEUM ** m, ARTIST ** a, PAINTING ** PAINT, int num){

	/* Adds a new painting in the paintingList and in a specific room. Then prints the list of paintings*/
	ROOM * ptr = NULL;
	MUSEUM * temp = *m;
	
	paintingHTInsert(paintingId, paintingName, artistId,museumId,roomId,PAINT,num,*a,*m,floorNum);
	
	//paintingInsert(p,paintingId,paintingName,artistId,museumId,roomId,a,m,*G,floorNum);

	while(temp){
		if(temp->museumId == museumId){
			if (ptr = roomTreeLookUp(roomId,temp->FL[floorNum],temp->G[floorNum])){
				roomPaintingTreeInsert(paintingId,&ptr->artP);
				break;
			}
		}
		temp = temp->next;
	}

	printf("N  <%d> %s %d %d %d %d DONE\n",paintingId,paintingName, artistId , museumId, floorNum, roomId);
	printf(" Hash Table Of Paintings:\n");
	paintingHTPrint(PAINT,num, "   ");
}


static void visit(WORK * roomPaintingList, void * PAINT, int m){
	WORK * tmp = roomPaintingList;
	PAINTING * tmp_paint = paintingHTLookUp(tmp->paintingId, (PAINTING **)PAINT,m);

	printf("\t%d %s %d %s %d %s\n\t", tmp_paint->paintingId,
										tmp_paint->paintingName,
										tmp_paint->artistPtr->artistId, 
										tmp_paint->artistPtr->artistName, 
										tmp_paint->artistPtr->artStylePtr->artStyleId,
										tmp_paint->artistPtr->artStylePtr->styleName);
}

void V(int paintingId, int museumId,int floorNum, int roomId, int museumIddest, int floordest, int roomIddest, MUSEUM ** m, PAINTING ** PAINT, int num){
	/* Move a painting from roomId to roomIddest */
	PAINTING * found_painting = NULL;
	ROOM * ptr = NULL;
	ROOM * ptrdel = NULL;
	MUSEUM * tempdel = *m;
	MUSEUM * tempins = *m;
	WORK *rptemp = NULL;

	/* find the painting that we're going to move */
	found_painting = paintingHTLookUp(paintingId, PAINT, num);

	/* find the room we're going to delete it from */
	ptrdel = roomTreeLookUp(roomId, museumLookUp(*m, museumId)->FL[floorNum], museumLookUp(*m, museumId)->G[floorNum]);
	/* delete it */
	roomPaintingTreeDelete(paintingId, &found_painting->roomPtr->artP);

	/* find the museum we're going to put the painting to */
	tempins = museumLookUp(*m, museumIddest);
	/* find the room in the museum we're going to put it */
	ptr = roomTreeLookUp(roomIddest, tempins->FL[floordest], tempins->G[floordest]);
	/* insert it there */
	roomPaintingTreeInsert(paintingId, &ptr->artP);
	/* fix the pointers */
	found_painting->roomPtr = ptr;
	found_painting->museumPtr = tempins;

	printf("V  %d %d %d %d %d %d %d DONE\n",paintingId,museumId, floorNum, roomId, museumIddest, floordest, roomIddest);

	printf(" List Of Paintings of %d:\n", roomId);

	rptemp = ptrdel->artP;
	TreePrint(rptemp, visit, PAINT, num);
	//painting_TreePrint(rptemp,PAINT, num);
	printf(" List Of Paintings of %d:\n", roomIddest);

	rptemp = ptr->artP;
	TreePrint(rptemp, visit, PAINT, num);
	//painting_TreePrint(rptemp,PAINT, num);
}

static void moveAll (ROOM * room, ROOM * roomdest, PAINTING ** paint, int num, MUSEUM * museumdest){

	PAINTING * found_painting = NULL;
	/* find the painting that we're going to move */
		found_painting = paintingHTLookUp (room->artP->paintingId,paint,num);
		/* delete it */
		roomPaintingTreeDelete(room->artP->paintingId, &room->artP);
		/* insert it there */
		roomPaintingTreeInsert(found_painting->paintingId, &roomdest->artP);
		/* fix the pointers */
		found_painting->roomPtr = roomdest;
		found_painting->museumPtr = museumdest;

}
static void InOrder(WORK *roomPainting,ROOM * room, ROOM * roomdest, PAINTING ** paint, int num, MUSEUM * museumdest ){
	
	if (roomPainting == NULL) return;
	InOrder(roomPainting->lc, room,roomdest,paint, num, museumdest);
	moveAll(room,roomdest,paint,num,museumdest);
	InOrder(roomPainting->rc, room,roomdest,paint, num,museumdest);
}
void L(int museumId, int floorNum,int roomId, int museumId_dest, int floorId_dest, int roomId_dest, MUSEUM ** m , PAINTING ** PAINT, int num){

	/* Move all the paintings from roomId to roomId_dest */
	PAINTING * found_painting = NULL;

	MUSEUM * tempdel = *m;
	MUSEUM * tempins = museumLookUp(*m, museumId_dest);
	ROOM * ptr = roomTreeLookUp(roomId_dest, tempins->FL[floorId_dest], tempins->G[floorId_dest]);
	ROOM * ptrdel = roomTreeLookUp(roomId, museumLookUp(*m, museumId)->FL[floorNum], museumLookUp(*m, museumId)->G[floorNum]);
	WORK *rptemp = NULL;
	WORK * roompaint = ptrdel->artP;

	InOrder(roompaint,ptrdel,ptr,PAINT,num,tempins);

	printf("L   %d %d %d %d %d %d DONE\n",museumId, floorNum, roomId, museumId_dest, floorId_dest, roomId_dest);

	printf(" List Of Paintings:\n");
	paintingHTPrint(PAINT, num, "   ");

}



void G(int roomId, int roomId_dest, MUSEUM**m,PAINTING **PAINT, int num ){
	/* Merge rooms with complexity O(n1+n2). after we merge the rooms in a temp list we insert it in the room at start because they are already sorted.
	* then we delete the source list */
	MUSEUM * tempmuseum = *m;
	MUSEUM * tempmuseumdest = *m;
	ROOM * ptrroom = NULL;
	ROOM * ptrroomdest = NULL;
	WORK *source, *dest, *final;
	int museumId_source, floor_src;

	int i = 0;

	/*Bres to source mouseio*/
	while(tempmuseum) {
		int f = findFloor(tempmuseum, roomId);

		if(f >= 0) {
			if(ptrroom = roomTreeLookUp(roomId, tempmuseum->FL[f], tempmuseum->G[f])) {
				break;
			}
		}
		tempmuseum = tempmuseum->next;
	}

	/*bres to dest mouseio */
	while(tempmuseumdest) {
		int f = findFloor(tempmuseumdest, roomId_dest);

		if(f >= 0) {
			if(ptrroomdest = roomTreeLookUp(roomId_dest, tempmuseumdest->FL[f],tempmuseum->G[f])) {
				break;
			}
		}
		tempmuseumdest = tempmuseumdest->next;
	}

	

	source = ptrroom->artP;
	dest = ptrroomdest->artP;
	final = NULL;

	/*metakinhse to mouseio apo to ptrroom sto ptrroomdest*/
	InOrder(source,ptrroom,ptrroomdest,PAINT,num,tempmuseumdest);

	/*diegrapse thn source aithousa */
	museumId_source = tempmuseum->museumId;
	floor_src = findFloor(tempmuseum,roomId);

	//roomTreeDelete(roomId,&tempmuseum->FL[findFloor(tempmuseum,roomId)],tempmuseum->G[findFloor(tempmuseum,roomId)] );
	printf("G   %d %d %d %d %d %d DONE\n",museumId_source, floor_src, roomId, tempmuseumdest->museumId, findFloor(tempmuseumdest,roomId_dest), roomId_dest);
	printf(" List of Paintings: \n");
	paintingHTPrint(PAINT, num,"   ");
}



static void InorderWork(WORK *sourceTree, ROOM *sourceRoom, ROOM *destRoom, void (*f)(WORK *, ROOM *, ROOM *, PAINTING **, MUSEUM *, int, int, struct stack **), PAINTING **p, MUSEUM *m, struct stack **s, int flag, int buckets, int count, char mode){

	if (mode == 'i'){

		if(flag == -1) { 
			if(count == 0)
				return;
			else 
				--(count);
		}
	}
		
	if(sourceTree == NULL) 
		return;
	InorderWork(sourceTree->lc, sourceRoom, destRoom, f, p, m, s, flag, buckets, count, mode);
	f(sourceTree, sourceRoom, destRoom, p, m, flag, buckets, s);
	InorderWork(sourceTree->rc, sourceRoom, destRoom, f, p, m, s, flag, buckets, count, mode);

}

static void printPaintings(WORK *node, ROOM *sourceRoom, ROOM *destRoom, PAINTING **p, MUSEUM *m, int flag, int buckets, struct stack **s){
	int paintingId = node->paintingId;
	PAINTING *temp = paintingHTLookUp(paintingId, p, buckets);
	printf("%d %s %d %s %d %s\n",temp->paintingId, temp->paintingName,temp->artistPtr->artistId, temp->artistPtr->artistName, temp->artistPtr->artStylePtr->artStyleId,temp->artistPtr->artStylePtr->styleName );
}

static void movePaintings(WORK *node, ROOM *sourceRoom, ROOM *destRoom, PAINTING **p, MUSEUM *m, int flag, int buckets, struct stack **s) {
	int paintingId = node->paintingId;
	PAINTING *targetPainting = paintingHTLookUp(paintingId, p, buckets);
	int artStyle = 0;

	if(flag == -1) 
		artStyle = -1;
	else 
		artStyle = targetPainting->artistPtr->artStylePtr->artStyleId;

	if(node == NULL) 
		return;

	if (artStyle == flag){
		int *temp = (int *)malloc(sizeof(int)) ;	
		roomPaintingTreeInsert(paintingId, &destRoom->artP);
		targetPainting->museumPtr = m;
		targetPainting->roomPtr = destRoom;
		*temp = paintingId;
		push(s, temp);
		//roomPaintingTreeDelete(paintingId, &sourceRoom->artP);
	}

}

void R(int museumId, int floorNum, int roomId, int roomId_src, int flag, MUSEUM ** m, PAINTING ** p, int num){
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
	WORK *sourceWorkTree;
	struct stack *s = NULL;

	museumdest = museumLookUp(*m,museumId);
	roomTreeInsert(roomId,&museumdest->FL[floorNum], museumdest->G[floorNum]);
	destRoom = roomTreeLookUp(roomId, museumdest->FL[floorNum], museumdest->G[floorNum]);

	while(museumSource) {
		int f = findFloor(museumSource, roomId_src);

		if(f >= 0) {
			if(sourceRoom = roomTreeLookUp(roomId_src, museumSource->FL[f], museumSource->G[f])) {
				break;
			}
		}
		museumSource = museumSource->next;
	}


	//temp = sourceRoom->artP;
	sourceWorkTree = sourceRoom->artP;

	if(sourceWorkTree != NULL) { 
		if(flag > 0) { 
			InorderWork(sourceWorkTree, sourceRoom, destRoom, movePaintings, p, museumdest, &s, flag,num , NULL, 'i');
		} else if(flag == -1) { 
			int length = 0;
			length = getLength(sourceWorkTree);
			length = length/2;
			InorderWork(sourceWorkTree, sourceRoom, destRoom, movePaintings, p, museumdest, &s, flag, num, length, 'i');
		}
	}

	while(s != NULL) { 
		void *temp = pop(&s);
		roomPaintingTreeDelete(*(int *)temp, &sourceRoom->artP);
		free(temp);
	}

	printf("R  %d %d %d %d %d DONE\n",museumId, floorNum, roomId, roomId_src, flag);

	printf(" List Of Paintings of %d:\n", roomId_src);
	InorderWork(sourceRoom->artP, NULL, NULL, printPaintings, p, NULL, NULL, flag, num, NULL,'p');

	printf(" List Of Paintings of %d:\n", roomId);
	InorderWork(destRoom->artP, NULL, NULL, printPaintings, p, NULL, NULL, flag, num, NULL,'p');
}



void T (int museumId, int floorNum,int roomId, MUSEUM ** m, PAINTING ** PAINT, int num){ 
	/* Print the room Paintings, with complexity o(n)*/
	MUSEUM * tempM = *m;
	ROOM * temp = NULL;
	WORK * rp = NULL;
	PAINTING * tempPainting = NULL;

	temp = roomTreeLookUp(roomId, museumLookUp(tempM,museumId)->FL[floorNum],museumLookUp(tempM,museumId)->G[floorNum]);
	rp = temp->artP;

	printf("T %d %d %d DONE\n", museumId, floorNum,roomId);
	printf (" List of Paintings\n");

	TreePrint(rp, visit, PAINT, num);

}

static void print_room(ROOM * room, PAINTING ** paint, int num, ROOM *  guardNode){

	ROOM * tmp = room;

	if (room!= guardNode){
		ROOM * left = room->lc;
		ROOM * right = room->rc;
		if (left == NULL && right == NULL)
			printf("%d 0 0\n\t", room->roomId);
		else if(left == NULL && right != NULL)
			printf("%d 0 %d\n\t", room->roomId, room->rc->roomId);
		else if (left != NULL && right == NULL)
			printf("%d %d 0\n\t", room->roomId, room->lc->roomId);
		else
			printf("%d %d %d\n\t", room->roomId,room->lc->roomId, room->lc->roomId);

		TreePrint(room->artP, visit, paint, num);
	}
	else
		printf("NULL");



}

static void Inorderroom(ROOM * roomTree, void (*print_room)(ROOM *, PAINTING **, int, ROOM *), PAINTING ** paint, int num , ROOM * guardNode){

	if(roomTree == guardNode) return;
	Inorderroom(roomTree->lc,print_room,paint,num, guardNode);
	print_room(roomTree,paint,num, guardNode);
	Inorderroom(roomTree->rc,print_room,paint,num, guardNode);
}

static void _P(MUSEUM *m, PAINTING **paint,int num) {
	ROOM * room = NULL;
	WORK *rp = NULL;
	int i = 0;
	int flag = 1;
	/*recursive printing of the elements */
	if(m->next != NULL)
		_P(m->next, paint,num);

	printf("  <%d> <%s> <%s>\n",m->museumId,m->museumName, m->museumAddress);

	for (i=0; i<MAX_FLOOR_NUM; i++){
		flag = 1;
		printf("\tFL[%d]: \n\t\t", i);
		flag = 0;
		room = m->FL[i];
		Inorderroom(room,print_room,paint,num,m->G[i]);
	}
}

void P(MUSEUM **m,PAINTING ** PAINT, int num){

	/*Prints all the data structures */
	printf("P DONE\n");

	_P(*m, PAINT, num);
}


static void eventI(WORK *node, ROOM *sourceRoom, ROOM *destRoom, PAINTING **p, MUSEUM *m, int artistId, int buckets, struct stack **s){
	int paintingId = node->paintingId;
	PAINTING *targetPainting = paintingHTLookUp(paintingId, p, buckets);

	if (artistId == targetPainting->artistPtr->artistId){
		int *temp = (int *)malloc(sizeof(int)) ;	
		roomPaintingTreeInsert(paintingId, &destRoom->artP);
		targetPainting->museumPtr = m;
		targetPainting->roomPtr = destRoom;
		*temp = paintingId;
		push(s, temp);
	}
}

void I (int artistId,int museumId_dest, int floorNum_dest, int roomId_dest, MUSEUM **m, PAINTING ** PAINT , int num){
	/*Inserts in the roomId_dest all the paintings with artistId */
	MUSEUM * sourceMuseum = *m;
	MUSEUM * destMuseum = museumLookUp(*m, museumId_dest);
	ROOM * destRoom = NULL;
	ROOM * sourceRoom = NULL;
	PAINTING * tempPaint = NULL;
	WORK * rpptr = NULL;
	WORK * rp = NULL;
	int i = 0;
	struct stack *s = NULL;
	struct stack *pointer = NULL;

	/*briskoume to dwmatio pou tha mpoun ola ta erga texhs tou kalhtexnh me anagnwristiko artistId*/
	destRoom = roomTreeLookUp(roomId_dest, destMuseum->FL[floorNum_dest], destMuseum->G[floorNum_dest]);

	/*Gia ola ta mouseia */
	while (sourceMuseum){
		/*Gia olous tous orofous */
		for (i = 0;i<MAX_FLOOR_NUM;i++){
			ROOM *guard = sourceMuseum->G[i];
			sourceRoom = sourceMuseum->FL[i];

			/*Gia ola ta dwmatia */
			if(sourceRoom != guard || pointer != NULL) { 
				if(sourceRoom != guard) { 
					push(&pointer, sourceRoom);
					sourceRoom = sourceRoom->lc;
				} else { 
					sourceRoom = (ROOM *)pop(&pointer);
					
					if(sourceRoom->artP!=NULL){
						rpptr = sourceRoom->artP;
						tempPaint = paintingLookUp(rpptr->paintingId,PAINT[i]);
						InorderWork(rpptr,sourceRoom,destRoom,eventI,PAINT, destMuseum,&s,artistId,num,0,' ');
					}

					while(s != NULL) { 
						void *temp = pop(&s);
						roomPaintingTreeDelete(*(int *)temp, &sourceRoom->artP);
						free(temp);
					}

					sourceRoom = sourceRoom->rc;
				}
			}
		}
		sourceMuseum = sourceMuseum->next;
	}

	printf("I  <%d> %d %d <%d> DONE\n",artistId,museumId_dest, floorNum_dest , roomId_dest);

	paintingHTPrint(PAINT, num, "   ");

}

static void eventY(WORK *node, ROOM *sourceRoom, ROOM *destRoom, PAINTING **p, MUSEUM *m, int artStyleId, int buckets, struct stack **s){
	int paintingId = node->paintingId;
	PAINTING *targetPainting = paintingHTLookUp(paintingId, p, buckets);

	if (artStyleId == targetPainting->artistPtr->artStylePtr->artStyleId){
		int *temp = (int *)malloc(sizeof(int));	
		roomPaintingTreeInsert(paintingId, &destRoom->artP);
		targetPainting->museumPtr = m;
		targetPainting->roomPtr = destRoom;
		*temp = paintingId;
		push(s, temp);
	}
}

void Y (int artStyleId,int museumId_dest, int floorNum_dest, int roomId_dest, MUSEUM **m, PAINTING **PAINT, int num){
	/*Inserts in the roomId_dest all the paintings with artStyleID */
	MUSEUM * sourceMuseum = *m;
	MUSEUM * destMuseum = museumLookUp(*m, museumId_dest);
	ROOM * destRoom = NULL;
	ROOM * sourceRoom = NULL;
	PAINTING * tempPaint = NULL;
	WORK * rpptr = NULL;
	WORK * rp = NULL;
	int i = 0;
	struct stack *s = NULL;
	struct stack *pointer = NULL;

	/*briskoume to dwmatio pou tha mpoun ola ta erga texhs tou kalhtexnh me anagnwristiko artistId*/
	destRoom = roomTreeLookUp(roomId_dest, destMuseum->FL[floorNum_dest], destMuseum->G[floorNum_dest]);

	/*Gia ola ta mouseia */
	while (sourceMuseum){
		/*Gia olous tous orofous */
		for (i = 0;i<MAX_FLOOR_NUM;i++){
			ROOM *guard = sourceMuseum->G[i];
			sourceRoom = sourceMuseum->FL[i];

			/*Gia ola ta dwmatia */
			if(sourceRoom != guard || pointer != NULL) { 
				if(sourceRoom != guard) { 
					push(&pointer, sourceRoom);
					sourceRoom = sourceRoom->lc;
				} else { 
					sourceRoom = (ROOM *)pop(&pointer);
					
					if(sourceRoom->artP!=NULL){
						rpptr = sourceRoom->artP;
						tempPaint = paintingLookUp(rpptr->paintingId,PAINT[i]);
						InorderWork(rpptr,sourceRoom,destRoom,eventI,PAINT, destMuseum,&s,artStyleId,num,0,' ');
					}

					while(s != NULL) { 
						void *temp = pop(&s);
						roomPaintingTreeDelete(*(int *)temp, &sourceRoom->artP);
						free(temp);
					}

					sourceRoom = sourceRoom->rc;
				}
			}
			
		}
		sourceMuseum = sourceMuseum->next;
	}



	printf("I  <%d> %d %d <%d> DONE\n",artStyleId,museumId_dest, floorNum_dest , roomId_dest);

	paintingHTPrint(PAINT, num, "   ");

}