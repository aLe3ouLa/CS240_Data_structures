#include "PostOrderDoublyLinkedTreeStyle.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

/* Insert an element in the list */
void artStyleInsert(int ID, char * Name, ARTSTYLE ** styleList){
	ARTSTYLE * tmp = *styleList;
	ARTSTYLE * newStyle = NULL;
	ARTSTYLE * found = NULL;

	if(tmp  == NULL){
		/*ama to dentro einai adeio */
		newStyle = malloc (sizeof(ARTSTYLE));
		newStyle->artStyleId = ID;
		newStyle->p = NULL;
		strcpy(newStyle->styleName, Name);
		newStyle->lc = NULL;
		newStyle->rc = NULL;
		*styleList = newStyle;
		return;
	}

	/*psaxe na deis an uparxei to stoixeio me auto to ID, sto dentro*/
	found = artStyleLookUp(ID,*styleList);

	if(found!=NULL){
		/* Ama uparxei 3ana to stoixeio antikatesthse to Name (mporei na mhn einai allagmeno)*/
		strcpy(found->styleName, Name);
		return;
	}

	if (ID > tmp->artStyleId){
		newStyle->artStyleId = ID;
		strcpy(newStyle->styleName, Name);
		newStyle->p = tmp->p;
		newStyle->lc = tmp;
		newStyle->rc = NULL;
		tmp->p = newStyle;
		return;

	}
	else if ( ID < tmp->lc->artStyleId){
		artStyleInsert(ID, Name,&tmp->lc); 
	}
	else{
		artStyleInsert(ID, Name,&tmp->rc); 
	}
}






/* Search and return a style with specific id*/
ARTSTYLE * artStyleLookUp(int ID, ARTSTYLE * styleList){

	ARTSTYLE * tmp = styleList;

	if(tmp == NULL) return NULL;
	if(ID == tmp->artStyleId) return tmp;
	if(tmp->lc == NULL && tmp->rc ==NULL) return NULL;
	if (ID <tmp->artStyleId) return NULL;
	if (tmp->lc!= NULL){
		if (ID < tmp->lc->artStyleId)
			return artStyleLookUp(ID, tmp->lc);

	}
	if (tmp->rc!= NULL){
		if (ID >= tmp->rc->artStyleId)
			return artStyleLookUp(ID, tmp->rc);

	}
	return NULL;
}

/*
ARTSTYLE * artStyleLookUp(int ID, ARTSTYLE * styleList){

	ARTSTYLE * tmp = styleList;

	if(tmp == NULL) return NULL;


	while (tmp!= NULL){

		if(ID == tmp->artStyleId) return tmp;
		if (ID <tmp->artStyleId) return NULL;
		if (tmp->lc!= NULL){
			if (ID < tmp->lc->artStyleId)
				tmp = tmp->lc;
			else tmp = tmp->rc;
		}
		else
			tmp = tmp->rc;

	}

}*/



static void visit_print(ARTSTYLE * styleList){
	ARTSTYLE * tmp = styleList;
	printf("%d %s\n", tmp->artStyleId, tmp->styleName);
}

void artStylesPrint(ARTSTYLE * styleList){
	if (styleList == NULL) return;
	artStylesPrint(styleList->lc);
	artStylesPrint(styleList->rc);
	visit_print(styleList);
}