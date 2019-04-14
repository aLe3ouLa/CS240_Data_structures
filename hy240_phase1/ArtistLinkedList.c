#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ArtistLinkedList.h"

ARTIST * guardNode (ARTIST ** artistList){
	/* Create the Guard node. The Guard Node, will be the last node of the list, with no values in it.
	* The guard node helps in search and delete of an element. */
	ARTIST * newGuard  = NULL;
	newGuard = malloc (sizeof (ARTIST));
	if (newGuard == NULL){
		fprintf(stderr, "failed to allocate memory.\n");
		exit(0);
	}

	/* Initialize Guard node with 0.*/
	newGuard->artistId=0;
	strcpy(newGuard-> artistName, " ");
	newGuard->YearOfBirth = 0;
	newGuard->YearOfDeath = 0;
	newGuard->artStylePtr = NULL;
	newGuard->next = NULL;

	/* Insert it in the list */
	*artistList = newGuard;
	return newGuard; 
}

void artistInsert(int artistId, char * Name, int YearOfBirth, int YearOfDeath, int artStyleId, ARTIST ** artistList,ARTSTYLE ** styleList){

	/* Inserts a new artist in ther artists list. The insertions are made in front of the list for complexity issues (O(1)).*/
	ARTIST * newArtist = NULL;
	newArtist = malloc(sizeof(ARTIST));
	if (newArtist == NULL){
		fprintf(stderr, "failed to allocate memory.\n");
		exit(0);
	}

	/* Insert the infos of the artist */
	newArtist->artistId = artistId;
	strcpy(newArtist-> artistName, Name);
	newArtist->YearOfBirth = YearOfBirth;
	newArtist->YearOfDeath = YearOfDeath;
	newArtist->artStylePtr = StyleLookUp(artStyleId, *styleList);

	/* Insert it in the list as the first element. */
	newArtist -> next = *artistList;
	*artistList = newArtist;

}

void artistDelete(int ID, ARTIST ** artistList, ARTIST * guardNode ){
	/* Deletes an artist from the list. Until we have not reach the Guard node we search for the element we want to delete. 
	 * If we find the element we delete it from the list. */
	ARTIST * current = NULL;
	ARTIST * previous = NULL;

	current = *artistList; /* current points to the head of the list. */

	while(current!= guardNode){  /* while we have not reach the guard node*/
		if (current->artistId == ID){
			if (current == previous && previous == *artistList){ /* If the element is the only one in the list */
				*artistList = current ->next;
			}
			previous->next = current->next; /* General case of delete */
			free(current);	/*Delete the node*/
			break;
		}

		previous = current; 
		current = current->next;
	}

}

void artistRemoveAll(ARTIST ** artistList, ARTIST * guardNode){
	/* Removes all the nodes of the list */

	ARTIST * delete_elem = *artistList;

	while (delete_elem!=guardNode){ /* While we have not reach the guard node we delete the nodes*/
		ARTIST * next = delete_elem ->next; /* store the next of the node*/
		free(delete_elem);
		delete_elem = next; 
	}
	*artistList = NULL; /* Make the list points to Null, in case of garbage.*/

}
ARTIST * artistLookUp(int artistId, ARTIST * artistList, ARTIST * guardNode){
	/*Search a node with specific artistId*/
	ARTIST * foundStruct = NULL;
	guardNode->artistId = artistId;

	while (artistList){ /* While we have not reached the end of the list*/
		if (artistList->artistId == artistId && artistList!=guardNode){ /*if the id of the node is the artistId and we are not in guard node we found it.*/
			foundStruct = artistList;
			break;
		}
		artistList = artistList-> next;
	}

	return foundStruct;

}
void artistPrint(ARTIST * artistList, ARTIST * guardNode ){

	/*Prints the elements of the artist List except guard Node.*/

	while (artistList != guardNode){
		printf("\t%d %s %d %d %d\n", artistList->artistId, artistList->artistName,artistList->YearOfBirth, artistList->YearOfDeath, artistList->artStylePtr->artStyleId);
		artistList = artistList->next;
	}
}

