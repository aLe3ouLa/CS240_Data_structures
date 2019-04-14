#ifndef STYLELINKEDLIST
#define STYLELINKEDLIST

#define MAX_NAME_LENGTH 30


typedef struct ArtStyle {
	int artStyleId;
	char styleName[MAX_NAME_LENGTH];
	struct ArtStyle *p;
	struct ArtStyle *lc;
	struct ArtStyle *rc;
} ARTSTYLE;

/* Insert an element in the list */
void artStyleInsert(int ID, char * Name, ARTSTYLE ** L);

/* Delete an element from the list with a specific id */
void artStylesDelete(int ID, ARTSTYLE ** L);

/* Search and return a style with specific id*/
ARTSTYLE * artStyleLookUp(int ID, ARTSTYLE * L);


/*Print the elements from the list*/
void artStylesPrint(ARTSTYLE * L);

#endif