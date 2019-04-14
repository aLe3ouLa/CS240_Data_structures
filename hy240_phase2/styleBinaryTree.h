#ifndef STYLELINKEDLIST
#define STYLELINKEDLIST


typedef struct ArtStyle {
	int artStyleId;
	char styleName[100];
	struct ArtStyle *p;
	struct ArtStyle *lc;
	struct ArtStyle *rc;
} ARTSTYLE;

 ARTSTYLE * artguardNode ();
/* Insert an element in the list */
void artStyleInsert(int ID, char * Name, ARTSTYLE ** styleTree, ARTSTYLE * guard);

/* Delete an element from the list with a specific id */
void artStylesDelete (int styleId, ARTSTYLE ** styleTree, ARTSTYLE * guard);

/* Search and return a style with specific id*/
ARTSTYLE * artStyleLookUp(int styleId, ARTSTYLE * styleTree, ARTSTYLE * guard);


/*Print the elements from the list*/
void artStylesPrint(ARTSTYLE * styleList, ARTSTYLE * guard);

#endif