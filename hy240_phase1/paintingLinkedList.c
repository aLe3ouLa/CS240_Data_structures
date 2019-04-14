#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "paintingLinkedList.h"

void paintingInsert(PAINTING ** p , int paintingId, char * paintingName, int artistId, int museumId,int roomId, ARTIST ** a, MUSEUM ** m, ARTIST * G, int f){

	/* Insert in a doubly linked list */
	PAINTING * newpainting = NULL;
	PAINTING * temp = NULL;
	PAINTING * current = NULL;
	PAINTING * previous = NULL;

	temp = *p;
	current = *p;
	previous = NULL;

	newpainting = (PAINTING *) malloc (sizeof(PAINTING));


	if (newpainting == NULL){
		printf("Can't allocate memory");
		exit(0);
	}

	/* Insert the infos of the list */
	newpainting->paintingId = paintingId;
	strcpy(newpainting->paintingName,paintingName);
	newpainting->artistPtr = artistLookUp(artistId,*a,G);
	newpainting->museumPtr = museumLookUp(*m,museumId);
	newpainting->roomPtr = roomLookUp(roomId,newpainting->museumPtr->FL[f]);

	/* Find where the node should be inserted in */
	while (current!=NULL && current->paintingId <paintingId){
		/* find where it should be placed*/
		previous = current;
		current = current->next;
	}

	/* If the list is empty*/
	if (temp == NULL){
		newpainting->next = NULL;
		newpainting->prev = NULL;
		*p = newpainting;
	}
	else {
		if (current == NULL && previous!= NULL){
		/*insert at the end*/
			newpainting->prev = previous;
			newpainting->next = NULL;
			previous->next= newpainting;

		}
		else if (previous == NULL&& current != NULL){
		/*insert at start*/
			newpainting->prev = NULL;
			newpainting->next = current;
			current->prev = newpainting;
			*p= newpainting;
		}
		else{
			/* General case */
			newpainting->prev = previous;
			newpainting->next = current;
			current->prev = newpainting;
			previous->next = newpainting;
		}
	}
}


void paintingDelete (PAINTING **p, int paintingId){
	/* Delete a painting with specific paintingId*/
	PAINTING * current = NULL;
	PAINTING * previous = NULL;

    current = *p;
    previous = NULL;
    while(current!=NULL){
		if (current->paintingId == paintingId){
			previous->next = current->next;
			(current->next)->prev = current->prev;
			free(current);
		}
		else{

        previous = current;
        current = current->next;
		}

	}
}

PAINTING * paintingLookUp(PAINTING * p, int paintingId){
	/* Search for a painting with specific id*/
	PAINTING * temp = p;

    while (temp!=NULL ){
		if (temp->paintingId == paintingId){
            return temp;
        }
        temp = temp-> next;
    }


}


void paintingPrint(PAINTING * p, char *prefix){
	/*Print all the paintings */
	PAINTING * temp = p;
	while (temp!=NULL){
		printf("%s%d %s %d %s %d %s %d %d\n",prefix,temp->paintingId, temp->paintingName,temp->artistPtr->artistId, temp->artistPtr->artistName, temp->museumPtr->museumId,temp->museumPtr->museumName,findFloor(temp->museumPtr, temp->roomPtr->roomId), temp->roomPtr->roomId );
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
