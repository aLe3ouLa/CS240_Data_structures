#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "roomDoublyLinkedTreeGuardNode.h"
#include "museumList.h"


void museumInsert(MUSEUM ** m, int museumId, char *museumName, char * museumAddress, unsigned int ** p , int f, unsigned int * roomNum){

	/* Insert a new museum in the museum List */
	MUSEUM * newMuseum;
	int i = 0;
	unsigned int j = 0;


    newMuseum = (MUSEUM *) malloc(sizeof(MUSEUM));
	if (newMuseum == NULL){
		fprintf(stderr, "failed to allocate memory.\n");
		exit(0);
	}

	/*Insert the museum Infos */
	newMuseum->museumId = museumId;
	strcpy(newMuseum->museumName, museumName);
	strcpy(newMuseum->museumAddress, museumAddress);
	/*Initialize the floors with Null*/
	for (i = 0; i <MAX_FLOOR_NUM;i++){
		newMuseum->FL[i] = NULL;
	}

	for (i = 0; i <MAX_FLOOR_NUM;i++){
		newMuseum->G[i] = NULL;
	}

	/*Insert the rooms of the floors */
	for (i = 0; i<=f; i++){
		newMuseum->G[i] = guardNode(); 
		for (j = 0;j<roomNum[i];j++){
			roomTreeInsert(p[i][j],&newMuseum->FL[i], newMuseum->G[i]);
		}
	}

	/*fix the connections*/
	newMuseum -> next = *m;
	*m = newMuseum;

}

void museumDelete( MUSEUM ** m, int museumid){

	/*Delete a museum with a specific id from the museum list */
	MUSEUM * current = NULL;
    MUSEUM * previous = NULL;

	int i = 0;

    current = *m;
    previous = *m;
    while(current!=NULL){
		if (current->museumId == museumid){
            if (current == previous && previous == *m){
                *m = current ->next;
            }
            previous->next = current->next;
			/*Remove all the rooms of the museum */
			for (i = 0; i<MAX_FLOOR_NUM; i++){
				roomRemoveAll(current->FL[i], current->G[i]);

			}
            free(current);
            break;
        }

        previous = current;
        current = current->next;
    }

}

MUSEUM * museumLookUp(MUSEUM *m, int museumid){
	/*Search for a museum with a specific id */
	MUSEUM * found = 0;

    while (m != NULL){

		if (m->museumId == museumid){
            found = m;
        }
        m = m->next;
    }

    return found;
}

void museumPrint(MUSEUM * m){
	/*Print the museum list */
	int i = 0;

	 while (m != NULL){
		printf("\t<%d> <%s> <%s>\n",m->museumId,m->museumName, m->museumAddress);
		for (i = 0;i<MAX_FLOOR_NUM;i++){
			printf("\tFL[%d]:\n",i);
			roomTreePrint(m->FL[i],m->G[i]);
		}
        m = m->next;
    }

}

void museumSinglePrint(MUSEUM * m){
	/* Print a single museum */
	int i = 0;
	printf("\t<%d> <%s> <%s>\n",m->museumId,m->museumName, m->museumAddress);

	for (;i<MAX_FLOOR_NUM;i++){
		printf("\tFL[%d]:\n",i);
		roomTreePrint(m->FL[i], m->G[i]);
	}
}


int findFloor (MUSEUM *m, int roomId){
	/* Find the floor where the room with id roomId is*/
	int i = 0, floor = 0;
	ROOM * temp;

	for(i = 0; i< MAX_FLOOR_NUM; i++){
		temp = m->FL[i];
		if (temp != NULL){
		if (roomTreeLookUp(roomId,temp,m->G[i])!= NULL){
			return i;
		}
		}
		
	}
	return -1;
}