#ifndef STYLELINKEDLIST
#define STYLELINKEDLIST

#define MAX_NAME_LENGTH 30


typedef struct ArtStyle{

    unsigned int artStyleId;
	char  styleName[MAX_NAME_LENGTH];
    struct ArtStyle * next;

} ARTSTYLE;

/* Insert an element in the list */
void artStyleInsert(int ID, char * Name, ARTSTYLE ** L);

/* Delete an element from the list with a specific id */
void artStylesDelete(int ID, ARTSTYLE ** L);

/* Search and return a style with specific id*/
ARTSTYLE * StyleLookUp(int ID, ARTSTYLE * L);

/* Remove all the nodes from the list */
void removeAll(ARTSTYLE ** L);

/*Print the elements from the list*/
void artStylesPrint(ARTSTYLE * L);

#endif
