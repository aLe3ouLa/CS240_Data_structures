#ifndef STYLELINKEDLIST
#define STYLELINKEDLIST

#define MAX_NAME_LENGTH 30

typedef struct ArtStyle {
  int key;
  char info[MAX_NAME_LENGTH];
  int red; /* if red=0 then the node is black */
  struct ArtStyle* left;
  struct ArtStyle* right;
  struct ArtStyle* parent;
} ARTSTYLE;

typedef struct ArtStyleTree {
  ARTSTYLE* root;             
  ARTSTYLE* nil;              
} ArtStyleTree;

ArtStyleTree* RBTreeCreate(void);
ARTSTYLE * ArtStyleInsert(ArtStyleTree*, int key, char* info);
void RBTreePrint(ArtStyleTree*);
void RBDelete(ArtStyleTree* , ARTSTYLE* );
void RBTreeDestroy(ArtStyleTree*);
ARTSTYLE* TreePredecessor(ArtStyleTree*,ARTSTYLE*);
ARTSTYLE* TreeSuccessor(ArtStyleTree*,ARTSTYLE*);
ARTSTYLE* RBExactQuery(ArtStyleTree*, int);

#endif