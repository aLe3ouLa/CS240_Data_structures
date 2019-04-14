#ifndef STYLELINKEDLIST
#define STYLELINKEDLIST

#define MAX_NAME_LENGTH 30

typedef enum { red, black } colour;

typedef struct ArtStyle {
	colour c;
	int artStyleId;
	char styleName[MAX_NAME_LENGTH];
	struct ArtStyle *p;
	struct ArtStyle *lc;
	struct ArtStyle *rc;
} ARTSTYLE;

 ARTSTYLE * artguardNode ();
/* Insert an element in the list */
void artStyleInsert(int ID, char * Name, ARTSTYLE ** styleTree, ARTSTYLE * guardNode);

/* Delete an element from the list with a specific id */
void artStylesDelete(int ID, ARTSTYLE ** L);

/* Search and return a style with specific id*/
ARTSTYLE * artStyleLookUp(int styleId, ARTSTYLE * styleTree, ARTSTYLE * guardNode);


/*Print the elements from the list*/
void artStylesPrint(ARTSTYLE * styleList, ARTSTYLE * guardNode);

#endif