#include "styleRedBlackTree.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


 ARTSTYLE * artguardNode (){
	/* Create Guard node */

	ARTSTYLE  *newGuardNode = NULL;
	/* Allocate space for the Guard node */
	newGuardNode = malloc(sizeof(ARTSTYLE));
	strcpy(newGuardNode->styleName, " ");
	newGuardNode->c = black;
	newGuardNode->artStyleId = 0;
	newGuardNode->p = NULL;
	newGuardNode->lc = NULL;
	newGuardNode->rc = NULL;
	return newGuardNode;
}


 static void rotateLeft(ARTSTYLE *x, ARTSTYLE ** root, ARTSTYLE * guardNode) {

    // rotate node x to left
	 ARTSTYLE * tmp = *root;

	ARTSTYLE *y = x->rc;

    // establish x->right link
    x->rc = y->rc;
	if (y->lc != NULL) y->lc->p = x;

    // establish y->parent link
     y->p = x->p;
    if (x->p == NULL) {
       
		tmp = y;
    }
	else if (x == x->p->lc)
            x->p->lc = y;
        else
            x->p->rc = y;

    // link x and y
    y->lc = x;
	x->p = y;

}

 static void rotateRight(ARTSTYLE *x, ARTSTYLE ** root, ARTSTYLE * guardNode) {

    // rotate node x to right
	  ARTSTYLE * tmp = *root;
	ARTSTYLE *y = x->lc;

    // establish x->left link
    x->lc = y->rc;
	if (y->rc != NULL) y->rc->p = x;

    // establish y->parent link
     y->p= x->p;
    if (x->p == NULL) {
       tmp = y;
    }
	else if (x == x->p->rc)
            x->p->rc = y;
        else
            x->p->lc = y;

    // link x and y
    y->rc = x;
	x->p = y;
	
}

static void ColorPropertiesInsert(ARTSTYLE ** styleTree, ARTSTYLE * newStyle, ARTSTYLE * guardNode){
	ARTSTYLE * y = NULL;
	ARTSTYLE * tempStyle = newStyle;
	ARTSTYLE * root = *styleTree;

	if (tempStyle->p == NULL){
		tempStyle->c = black;
		return;
	}


	while (tempStyle->artStyleId != root->artStyleId && tempStyle->p->c == red){
	
		if(tempStyle->p == tempStyle->p->p->lc){
			y = tempStyle->p->p->rc;
			if(y->c == red){
				tempStyle->p->c = black;
				y->c = black;
				tempStyle->p->p->c = red;
				tempStyle = tempStyle->p->p;
			}
			else {
				ARTSTYLE *x = NULL;
				if(tempStyle == tempStyle->p->rc){
					tempStyle = tempStyle->p;
					rotateLeft(tempStyle,&root, guardNode);
				}
				tempStyle->p->c = black;
				tempStyle->p->p->c = red;
				x= tempStyle->p->p;
				rotateRight(x, &root, guardNode);
			
			}
		
		}
		else{
			y = tempStyle->p->p->lc;
			if(y->c == red){
				tempStyle->p->c = black;
				y->c = black;
				tempStyle->p->p->c = red;
				tempStyle = tempStyle->p->p;
			}
			else {
				ARTSTYLE *x = NULL;
				if(tempStyle == tempStyle->p->lc){
					tempStyle = tempStyle->p;
					rotateRight(tempStyle,&root, guardNode);
				}
				tempStyle->p->c = black;
				tempStyle->p->p->c = red;
				x= tempStyle->p->p;
				rotateLeft(x, &root, guardNode);
				
			}
		
		
		}
	

	}

	(*styleTree)->c = black;
}

void artStyleInsert(int ID, char * Name, ARTSTYLE ** styleTree, ARTSTYLE * guardNode){
	ARTSTYLE * tmp = * styleTree;
	ARTSTYLE * newStyle = NULL;
	ARTSTYLE * found = NULL;
	ARTSTYLE * y = NULL;

	if (tmp == NULL && y == NULL){
		/*Bazoume thn riza*/
		newStyle = malloc (sizeof(ARTSTYLE));
		newStyle->c = red;
		 newStyle->artStyleId = ID;
		 strcpy(newStyle->styleName, Name);
		 newStyle->lc = guardNode;
		 newStyle->rc = guardNode;
		 newStyle->p = NULL;
		 *styleTree =  newStyle;
		 ColorPropertiesInsert(&tmp, newStyle, guardNode);
		 return;
	}
	
	/*psaxe na deis an uparxei to stoixeio me auto to ID, sto dentro*/
	found = artStyleLookUp(ID,*styleTree, guardNode);

	if(found!=NULL){
		/* Ama uparxei 3ana to stoixeio antikatesthse to Name (mporei na mhn einai allagmeno)*/
		strcpy(found->styleName, Name);
		return;
	}

	while (tmp != guardNode){
		y = tmp;
		if(ID<tmp->artStyleId)
			tmp = tmp->lc;
		else 
			tmp = tmp->rc;
	
	}

		newStyle = malloc (sizeof(ARTSTYLE));
		newStyle->c = red;
		newStyle->artStyleId = ID;
		newStyle->p = NULL;
		strcpy(newStyle->styleName, Name);
		newStyle->lc = guardNode;
		newStyle->rc = guardNode;

		newStyle->p = y;

		if(y!=guardNode){
		//Kane to newStyle riza tou dendrou
			if(newStyle->artStyleId < y->artStyleId) 
				y->lc = newStyle;
			else
				y->rc = newStyle;
		}
		else{
			*styleTree = newStyle;
		}
		ColorPropertiesInsert(styleTree, newStyle, guardNode);

}


ARTSTYLE * artStyleLookUp(int styleId, ARTSTYLE * styleTree, ARTSTYLE * guardNode){

	ARTSTYLE * tmp = styleTree;
	while (tmp != guardNode){
		/* ama breis to stoixeio epestrepse to */
		if (styleId == tmp->artStyleId){
			return tmp;
		}	
		
		/*ama einai megalutero apo to roomId tou tmp, pigaine sto de3i paidi tou tmp diaforetika sto aristero */
		if (styleId > tmp->artStyleId)
			tmp = tmp->rc;
		else
			tmp = tmp->lc;
	}

	/* ama de to breis epestrepse Null */
	return NULL;
}

static void visit_print(ARTSTYLE * styleList){
	ARTSTYLE * tmp = styleList;
	printf("%d %s\n", tmp->artStyleId, tmp->styleName);
}

void artStylesPrint(ARTSTYLE * styleList, ARTSTYLE * guardNode){
	
	if (styleList == guardNode) return;
	
	artStylesPrint(styleList->lc, guardNode);
	visit_print(styleList);
	artStylesPrint(styleList->rc, guardNode);
	
	
}