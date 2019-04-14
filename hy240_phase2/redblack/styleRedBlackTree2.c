#include "styleRedBlackTree2.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

ArtStyleTree* RBTreeCreate(void) {
  ArtStyleTree* newTree;
  ARTSTYLE* temp;

  newTree=(ArtStyleTree*) malloc(sizeof(ArtStyleTree));
  temp=newTree->nil= (ARTSTYLE*) malloc(sizeof(ARTSTYLE));
  temp->parent=temp->left=temp->right=temp;
  temp->red=0;
  temp->key=0;
  temp=newTree->root= (ARTSTYLE*) malloc(sizeof(ARTSTYLE));
  temp->parent=temp->left=temp->right=newTree->nil;
  temp->key=0;
  temp->red=0;
  return(newTree);
}

void LeftRotate(ArtStyleTree* tree, ARTSTYLE* x) {
  ARTSTYLE* y;
  ARTSTYLE* nil=tree->nil;
  
  y=x->right;
  x->right=y->left;

  if (y->left != nil) y->left->parent=x; /* used to use sentinel here */
  /* and do an unconditional assignment instead of testing for nil */
  
  y->parent=x->parent;   

  /* instead of checking if x->parent is the root as in the book, we */
  /* count on the root sentinel to implicitly take care of this case */
  if( x == x->parent->left) {
    x->parent->left=y;
  } else {
    x->parent->right=y;
  }
  y->left=x;
  x->parent=y;
}

void RightRotate(ArtStyleTree* tree, ARTSTYLE* y) {
  ARTSTYLE* x;
  ARTSTYLE* nil=tree->nil;

  x=y->left;
  y->left=x->right;

  if (nil != x->right)  x->right->parent=y; 
  
  x->parent=y->parent;
  if( y == y->parent->left) {
    y->parent->left=x;
  } else {
    y->parent->right=x;
  }
  x->right=y;
  y->parent=x;
}

void TreeInsertHelp(ArtStyleTree* tree, ARTSTYLE* z) {
  /*  This function should only be called by InsertRBTree (see above) */
  ARTSTYLE* x;
  ARTSTYLE* y;
  ARTSTYLE* nil=tree->nil;
  
  z->left=z->right=nil;
  y=tree->root;
  x=tree->root->left;
  while( x != nil) {
    y=x;
    if (x->key > z->key) { /* x.key > z.key */
      x=x->left;
    } else { /* x,key <= z.key */
      x=x->right;
    }
  }
  z->parent=y;
  if ( (y == tree->root) ||
       (y->key > z->key)) { /* y.key > z.key */
    y->left=z;
  } else {
    y->right=z;
  }
}

ARTSTYLE * RBTreeInsert(ArtStyleTree* tree, int key, char *info) {
  ARTSTYLE * y;
  ARTSTYLE * x;
  ARTSTYLE * newNode;

  x=(ARTSTYLE*) malloc(sizeof(ARTSTYLE));
  x->key=key;
  strcpy(x->info, info);

  TreeInsertHelp(tree,x);
  newNode=x;
  x->red=1;
  while(x->parent->red) { /* use sentinel instead of checking for root */
    if (x->parent == x->parent->parent->left) {
      y=x->parent->parent->right;
      if (y->red) {
	x->parent->red=0;
	y->red=0;
	x->parent->parent->red=1;
	x=x->parent->parent;
      } else {
	if (x == x->parent->right) {
	  x=x->parent;
	  LeftRotate(tree,x);
	}
	x->parent->red=0;
	x->parent->parent->red=1;
	RightRotate(tree,x->parent->parent);
      } 
    } else { /* case for x->parent == x->parent->parent->right */
      y=x->parent->parent->left;
      if (y->red) {
	x->parent->red=0;
	y->red=0;
	x->parent->parent->red=1;
	x=x->parent->parent;
      } else {
	if (x == x->parent->left) {
	  x=x->parent;
	  RightRotate(tree,x);
	}
	x->parent->red=0;
	x->parent->parent->red=1;
	LeftRotate(tree,x->parent->parent);
      } 
    }
  }
  tree->root->left->red=0;
  return(newNode);
}

ARTSTYLE* TreeSuccessor(ArtStyleTree* tree,ARTSTYLE* x) { 
  ARTSTYLE* y;
  ARTSTYLE* nil=tree->nil;
  ARTSTYLE* root=tree->root;

  if (nil != (y = x->right)) { /* assignment to y is intentional */
    while(y->left != nil) { /* returns the minium of the right subtree of x */
      y=y->left;
    }
    return(y);
  } else {
    y=x->parent;
    while(x == y->right) { /* sentinel used instead of checking for nil */
      x=y;
      y=y->parent;
    }
    if (y == root) return(nil);
    return(y);
  }
}

ARTSTYLE* TreePredecessor(ArtStyleTree* tree, ARTSTYLE* x) {
  ARTSTYLE* y;
  ARTSTYLE* nil=tree->nil;
  ARTSTYLE* root=tree->root;

  if (nil != (y = x->left)) { /* assignment to y is intentional */
    while(y->right != nil) { /* returns the maximum of the left subtree of x */
      y=y->right;
    }
    return(y);
  } else {
    y=x->parent;
    while(x == y->left) { 
      if (y == root) return(nil); 
      x=y;
      y=y->parent;
    }
    return(y);
  }
}

void InorderTreePrint(ArtStyleTree* tree, ARTSTYLE* x) {
  ARTSTYLE* nil=tree->nil;
  ARTSTYLE* root=tree->root;
  if (x != tree->nil) {
    InorderTreePrint(tree,x->left);
    printf("info=%s", x->info);
    printf("  key=%d", x->key); 
    printf("  l->key=");
    if( x->left == nil) printf("NULL"); else printf("%d", x->left->key);
    printf("  r->key=");
    if( x->right == nil) printf("NULL"); else printf("%d", x->left->key);
    printf("  p->key=");
    if( x->parent == root) printf("NULL"); else printf("%d", x->left->key);
    printf("  red=%i\n",x->red);
    InorderTreePrint(tree,x->right);
  }
}

void TreeDestHelper(ArtStyleTree* tree, ARTSTYLE* x) {
  ARTSTYLE* nil=tree->nil;
  if (x != nil) {
    TreeDestHelper(tree,x->left);
    TreeDestHelper(tree,x->right);
    /*tree->DestroyKey(x->key);
    tree->DestroyInfo(x->info);
    free(x);*/
  }
}

void RBTreeDestroy(ArtStyleTree* tree) {
  TreeDestHelper(tree,tree->root->left);
  free(tree->root);
  free(tree->nil);
  free(tree);
}

void RBTreePrint(ArtStyleTree* tree) {
  InorderTreePrint(tree,tree->root->left);
}

ARTSTYLE* RBExactQuery(ArtStyleTree* tree, int q) {
  ARTSTYLE* x=tree->root->left;
  ARTSTYLE* nil=tree->nil;
  int compVal;
  if (x == nil) return(0);

  if(x->key > q) 
	  compVal = 1; 
  else if(x->key < q) 
	  compVal = -1;
  else 
	  compVal = 0;

  while(0 != compVal) {/*assignemnt*/
    if (1 == compVal) { /* x->key > q */
      x=x->left;
    } else {
      x=x->right;
    }
    if ( x == nil) return(0);

    if(x->key > q) 
	  compVal = 1; 
	else if(x->key < q) 
	  compVal = -1;
	else 
	  compVal = 0;
  }
  return(x);
}

void RBDeleteFixUp(ArtStyleTree* tree, ARTSTYLE* x) {
  ARTSTYLE* root=tree->root->left;
  ARTSTYLE* w;

  while( (!x->red) && (root != x)) {
    if (x == x->parent->left) {
      w=x->parent->right;
      if (w->red) {
	w->red=0;
	x->parent->red=1;
	LeftRotate(tree,x->parent);
	w=x->parent->right;
      }
      if ( (!w->right->red) && (!w->left->red) ) { 
	w->red=1;
	x=x->parent;
      } else {
	if (!w->right->red) {
	  w->left->red=0;
	  w->red=1;
	  RightRotate(tree,w);
	  w=x->parent->right;
	}
	w->red=x->parent->red;
	x->parent->red=0;
	w->right->red=0;
	LeftRotate(tree,x->parent);
	x=root; /* this is to exit while loop */
      }
    } else { /* the code below is has left and right switched from above */
      w=x->parent->left;
      if (w->red) {
	w->red=0;
	x->parent->red=1;
	RightRotate(tree,x->parent);
	w=x->parent->left;
      }
      if ( (!w->right->red) && (!w->left->red) ) { 
	w->red=1;
	x=x->parent;
      } else {
	if (!w->left->red) {
	  w->right->red=0;
	  w->red=1;
	  LeftRotate(tree,w);
	  w=x->parent->left;
	}
	w->red=x->parent->red;
	x->parent->red=0;
	w->left->red=0;
	RightRotate(tree,x->parent);
	x=root; /* this is to exit while loop */
      }
    }
  }
  x->red=0;
}

void RBDelete(ArtStyleTree* tree, ARTSTYLE* z){
  ARTSTYLE* y;
  ARTSTYLE* x;
  ARTSTYLE* nil=tree->nil;
  ARTSTYLE* root=tree->root;

  y= ((z->left == nil) || (z->right == nil)) ? z : TreeSuccessor(tree,z);
  x= (y->left == nil) ? y->right : y->left;
  if (root == (x->parent = y->parent)) { /* assignment of y->p to x->p is intentional */
    root->left=x;
  } else {
    if (y == y->parent->left) {
      y->parent->left=x;
    } else {
      y->parent->right=x;
    }
  }
  if (y != z) { /* y should not be nil in this case */
    /* y is the node to splice out and x is its child */

    if (!(y->red)) RBDeleteFixUp(tree,x);
  
    //tree->DestroyKey(z->key);
    //tree->DestroyInfo(z->info);
    y->left=z->left;
    y->right=z->right;
    y->parent=z->parent;
    y->red=z->red;
    z->left->parent=z->right->parent=y;
    if (z == z->parent->left) {
      z->parent->left=y; 
    } else {
      z->parent->right=y;
    }
    free(z); 
  } else {
    //tree->DestroyKey(y->key);
    //tree->DestroyInfo(y->info);
    if (!(y->red)) RBDeleteFixUp(tree,x);
    free(y);
  }
}
