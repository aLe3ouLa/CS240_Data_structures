#include "paintingLinkedListSorted.h"
#include "museumList.h"
#include "artistBinaryTree.h"
#include "roomDoublyLinkedTreeGuardNode.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
/*Insert a node in a sorted list */
void paintingInsert(int paintingId, char * paintingName, int artistId, int museumId,int roomId,ARTIST *  a, MUSEUM * m, int f, PAINTING ** paintingList){

	/* Insert in a sorted list */
    PAINTING * newPainting = NULL;
    PAINTING * temp = *paintingList;
	PAINTING * pq = NULL;
	
    newPainting = (PAINTING *) malloc(sizeof(PAINTING));
	if (newPainting == NULL){
		fprintf(stderr, "failed to allocate memory.\n");
		exit(0);
	}

	/*Insert infos of the Painting*/
	newPainting->paintingId = paintingId;
	strcpy(newPainting->paintingName,paintingName);
	newPainting->artistPtr = artistTreeLookUp(artistId,a);
	newPainting->museumPtr = museumLookUp(m,museumId);
	newPainting->roomPtr = roomTreeLookUp(roomId,newPainting->museumPtr->FL[f],newPainting->museumPtr->G[f]);
	

	/*find where to insert the node*/

    while (temp!=NULL && temp->paintingId < paintingId ){
			pq = temp; 
            temp = temp->next;
    }
	/*if there is again a node with that id, dont insert it.*/
	if (temp != NULL && temp->paintingId == paintingId) return;

	/*fix the connections*/
	newPainting->next = temp;
	if (pq == NULL) 
		*paintingList = newPainting;
	else 
		pq->next = newPainting;


}

/* Delete a node with the specific id*/
void paintingDelete (int paintingId, PAINTING **paintingList){


/* Delete an element with specific paintingId*/
	PAINTING * current = NULL;
	PAINTING * previous = NULL;

	current = *paintingList;
	previous = *paintingList;
    while(current!=NULL){
		if (current->paintingId == paintingId){
            if (current == previous && previous == *paintingList){
				*paintingList = current ->next;
            } else { 
				previous->next = current->next;
			}
			free(current);
            break;
        }

        previous = current;
        current = current->next;

	}


}

/* Remove all the nodes of the list */
void paintingRemoveAll(PAINTING ** paintingList){

/*Remove all the elements of the list*/
	PAINTING * delete_elem = NULL;
	if (!*paintingList) return;

	delete_elem = *paintingList;

    while (delete_elem){
        PAINTING * n= delete_elem->next;
        free(delete_elem);
        delete_elem = n;
    }
    *paintingList = NULL;


}

/*Search the roomPainting with the specific paintingId*/
PAINTING * paintingLookUp(int paintingId, PAINTING * paintingList){

	/*Search for a Painting with a specific id*/

	PAINTING * foundStruct = NULL;
    while (paintingList!=NULL){
		if (paintingList->paintingId == paintingId){
            foundStruct = paintingList;
            break;
        }

		paintingList = paintingList-> next;
    }
    return foundStruct;


}


/* Print all the roomPaintings */
void paintingPrint(PAINTING * paintingList, char *prefix){

/*Print all the paintings */
	PAINTING * temp = paintingList;
	while (temp!=NULL){
		//printf("%d %s\n", temp->paintingId,temp->paintingName);
		int f = findFloor(temp->museumPtr, temp->roomPtr->roomId);
		printf("%s%d %s %d %s %d %s %d %d\n",prefix,temp->paintingId, temp->paintingName,temp->artistPtr->artistId, temp->artistPtr->artistName, temp->museumPtr->museumId,temp->museumPtr->museumName,f, temp->roomPtr->roomId );
		temp = temp->next;
	}

}


void paintingsIdprint(PAINTING *p, int paintingId, char *prefix){
	/* Print the painting with  specific id*/
	PAINTING * temp =  p;
	while (temp){
		if (temp->paintingId == paintingId){
			printf("%s%d %s %d %s %d %s\n",prefix,temp->paintingId, temp->paintingName,temp->artistPtr->artistId, temp->artistPtr->artistName, temp->artistPtr->artStylePtr->artStyleId,temp->artistPtr->artStylePtr->styleName );
			break;
		}
		temp=temp->next;
	}
}