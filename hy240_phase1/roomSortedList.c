#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "roomSortedList.h"
#include "roomPaintingSortedList.h"



void roomInsert(int roomId, ROOM ** R){
	/*Insert a new room in the rooms list. The rooms list is sorted.*/
    ROOM * newRoom = NULL;
    ROOM * temp = NULL;
	ROOM * pq = NULL;

	temp = *R;

    newRoom = (ROOM *) malloc(sizeof(ROOM));
	if (newRoom == NULL){
		fprintf(stderr, "failed to allocate memory.\n");
		exit(0);
	}

    newRoom->roomId = roomId;
	newRoom->artPtr = NULL;

    while (temp!=NULL && temp->roomId < roomId ){ /* find the place for the insertion of the node*/
			pq = temp;
            temp = temp->next;
    }

	if (temp != NULL && temp->roomId == roomId) return; /* if there is the node again dont insert it*/

	/* fix the connections of the lists */
	newRoom->next = temp;
	if (pq == NULL)
		*R = newRoom;
	else
		pq->next = newRoom;
}

void roomDelete (int roomId, ROOM **R){

	/* Delete an element from the list with specific roomId*/
	ROOM * current = NULL;
	ROOM * previous = NULL;

    current = *R;
    previous = *R;
    while(current!=NULL){
		if (current->roomId == roomId){
            if (current == previous && previous == *R){
                *R = current ->next;
            }
            previous->next = current->next;
            free(current);
            break;
        }

        previous = current;
        current = current->next;

	}
}

ROOM * roomLookUp(int roomId, ROOM * R){

	/* Search for a ROOM with a specific id*/
	ROOM * foundStruct = NULL;
    while (R!=NULL){
		if (R->roomId == roomId){
            foundStruct = R;
            break;
        }

        R = R-> next;
    }
    return foundStruct;

}

void roomRemoveAll(ROOM ** R){

	/* Remove all the nodes from the list */

	ROOM * delete_elem = NULL;
	if (!*R) return;

	delete_elem = *R;

    while (delete_elem){
        ROOM * n= delete_elem->next;
        free(delete_elem);
        delete_elem = n;
    }
    *R = NULL;

}

void roomPrint(ROOM * l){

	/* Print Null if there isn't any room in the list or the roomId */

	if (l==NULL){
		printf("\t\tNULL\n");
		return;
	}
	while (l!=NULL){
		printf("\t\t%d\n",l->roomId);
		l = l->next;
	}

}


