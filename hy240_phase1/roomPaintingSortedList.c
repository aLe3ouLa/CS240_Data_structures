#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "roomPaintingSortedList.h"

void roomPaintingInsert_start(ROOMPAINTING **R, int paintingId){
	/* Insert an element in the front of the list for O(1) complexity.*/

	ROOMPAINTING * newRoomPainting = NULL;
	newRoomPainting = (ROOMPAINTING *) malloc(sizeof(ROOMPAINTING));
	if (newRoomPainting == NULL){
		fprintf(stderr, "failed to allocate memory.\n");
		exit(0);
	}
	/*Insert the infos of the roomPainting*/
	newRoomPainting->paintingId = paintingId;

	/*fix the connections */
	newRoomPainting-> next = *R;
    *R = newRoomPainting;
}

void roomPaintingInsert(int paintingId, ROOMPAINTING ** R){
	/* Insert in a sorted list */
    ROOMPAINTING * newRoomPainting = NULL;
    ROOMPAINTING * temp = *R;
	ROOMPAINTING * pq = NULL;
	
    newRoomPainting = (ROOMPAINTING *) malloc(sizeof(ROOMPAINTING));
	if (newRoomPainting == NULL){
		fprintf(stderr, "failed to allocate memory.\n");
		exit(0);
	}

	/*Insert infos of the roomPainting*/
	newRoomPainting->paintingId = paintingId;

	/*find where to insert the node*/

    while (temp!=NULL && temp->paintingId < paintingId ){
			pq = temp; 
            temp = temp->next;
    }
	/*if there is again a node with that id, dont insert it.*/
	if (temp != NULL && temp->paintingId == paintingId) return;

	/*fix the connections*/
	newRoomPainting->next = temp;
	if (pq == NULL) 
		*R = newRoomPainting;
	else 
		pq->next = newRoomPainting;
}

void roomPaintingDelete (int paintingId, ROOMPAINTING **R){

	/* Delete an element with specific paintingId*/
	ROOMPAINTING * current = NULL;
	ROOMPAINTING * previous = NULL;

    current = *R;
    previous = *R;
    while(current!=NULL){
		if (current->paintingId == paintingId){
            if (current == previous && previous == *R){
                *R = current ->next;
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


ROOMPAINTING * roomPaintingLookUp(int paintingId, ROOMPAINTING * R){

	/*Search for a roomPainting with a specific id*/

	ROOMPAINTING * foundStruct = NULL;
    while (R!=NULL){
		if (R->paintingId == paintingId){
            foundStruct = R;
            break;
        }

        R = R-> next;
    }
    return foundStruct;

}

void roomPaintingRemoveAll(ROOMPAINTING ** R){
	/*Remove all the elements of the list*/
	ROOMPAINTING * delete_elem = NULL;
	if (!*R) return;

	delete_elem = *R;

    while (delete_elem){
        ROOMPAINTING * n= delete_elem->next;
        free(delete_elem);
        delete_elem = n;
    }
    *R = NULL;

}
void roomPaintingPrint(ROOMPAINTING * l){
	/* Print all the elements of the list */
	while (l!=NULL){
		printf("Painting ID: %d Next: %p\n",l->paintingId, l->next);
		l = l->next;
	}

}


int roomPaintingGetLength(ROOMPAINTING **R){
	/* counts the number of nodes of the list */
	int counter = 0;
	ROOMPAINTING * temp = *R;

	while (temp){
		counter++;
		temp = temp->next;
	}
	return  counter;

}