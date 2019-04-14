#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "StyleLinkedList.h"

void artStyleInsert(int ID, char * Name, ARTSTYLE ** styleList){
	/* Inserts a new style in the style list. The insertions are made in front of the list for complexity issues (O(1)).*/

    ARTSTYLE * newStyle = NULL;
    newStyle = malloc(sizeof(ARTSTYLE));
	if (newStyle == NULL){
		fprintf(stderr, "failed to allocate memory.\n");
		exit(0);
	}

	/* Insert the infos of the style*/
    newStyle -> artStyleId = ID;
    strcpy(newStyle-> styleName, Name);

	/* Insert it in the list as the first element. */
    newStyle -> next = *styleList;
    *styleList = newStyle;
}



void artStylesDelete(int ID, ARTSTYLE ** styleList){
	/*Deletes a style from the list*/
	
	ARTSTYLE * current = NULL;
    ARTSTYLE * previous = NULL;

    current = *styleList;
    previous = *styleList;
    while(current!=NULL){
        if (current->artStyleId == ID){ /* when we found the element we fix the connections and free it.*/
            if (current == previous && previous == *styleList){
                *styleList = current ->next;
            }
            previous->next = current->next;
            free(current);
            break;
        }

        previous = current;
        current = current->next;
    }

}

ARTSTYLE * StyleLookUp(int ID, ARTSTYLE * styleList){
	/* Search for a style with specific id.*/

    ARTSTYLE * foundStruct = NULL;
    while (styleList!=NULL){
        if (styleList ->artStyleId == ID){
            foundStruct = styleList;
            break;
        }

        styleList = styleList-> next;
    }
    return foundStruct;
}

void removeAll(ARTSTYLE ** styleList){
	/* Removes all the nodes of the list */

    ARTSTYLE * delete_elem = *styleList;

    while (delete_elem){
        ARTSTYLE * next = delete_elem ->next;
        free(delete_elem);
        delete_elem = next;
    }
    *styleList = NULL;
}



void artStylesPrint(ARTSTYLE * styleList){
	/* Prints all the elements of the list */
    while (styleList != NULL){
        printf("\t%d %s\n", styleList->artStyleId,styleList->styleName, styleList->next);
        styleList = styleList->next;
    }
}
