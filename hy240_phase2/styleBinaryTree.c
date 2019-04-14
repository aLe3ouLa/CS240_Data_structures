#include "styleBinaryTree.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>


void artStyleInsert (int styleId, char * styleName, ARTSTYLE ** styleTree, ARTSTYLE * guardNode){
	ARTSTYLE * tmp = *styleTree;
	ARTSTYLE * newStyle= NULL, * parent = NULL;
	ARTSTYLE * found = NULL;

	if (tmp == NULL){
		newStyle = malloc (sizeof(ARTSTYLE));
		newStyle->artStyleId = styleId;
		strcpy(newStyle->styleName, styleName);
		newStyle->lc = NULL;
		newStyle->rc = NULL;
		*styleTree = newStyle;
		return;
	}

	while (tmp != NULL ){
		
		if (tmp->artStyleId == styleId) return;
		parent = tmp;
		if (tmp->artStyleId > styleId)
			tmp = tmp->lc;
		else 
			tmp = tmp->rc;
	
	}

	newStyle = malloc (sizeof(ARTSTYLE));
	
		newStyle->artStyleId = styleId;
		strcpy(newStyle->styleName, styleName);
		newStyle->lc = NULL;
		newStyle->rc = NULL;
		//newArtist->artStylePtr = artStyleLookUp(styleId, styleTree, guardNode);

		if (parent != NULL && tmp == NULL){
			if (styleId < parent->artStyleId){
				parent->lc = newStyle;
				newStyle->lc = NULL;
				newStyle->rc = NULL;
			}
			else{
				parent->rc = newStyle;
				newStyle->lc = NULL;
				newStyle->rc = NULL;
		}
	}

}

static ARTSTYLE * minValue(ARTSTYLE* node, ARTSTYLE ** father) {
	ARTSTYLE * current = node;

  /* loop down to find the leftmost leaf */
  while (current->lc != NULL) {
		*father = current;
		current = current->lc;
  }
  return current;
}


static ARTSTYLE * inOrderFindNext(ARTSTYLE * node, ARTSTYLE* root, ARTSTYLE ** father){
	*father = node;
	if( node->rc != NULL )
        return minValue(node->rc, father);


	return NULL;
}

void artStylesDelete (int styleId, ARTSTYLE ** styleTree, ARTSTYLE * guard){
	ARTSTYLE * child = NULL,  *parent = NULL, *del_node = NULL;
	ARTSTYLE * current = *styleTree;
	ARTSTYLE * x = NULL;
	ARTSTYLE * root = *styleTree;


	/*Ama den uparxei o kombos mh sunexiseis thn diagrafh*/
	if(artStyleLookUp(styleId, *styleTree, guard)==NULL) return;

		while (current != NULL){

			if (current->artStyleId == styleId){
			del_node = current;

			if (del_node->lc == NULL && del_node->rc == NULL){
				/* o kombos den exei paidia */
				if (parent->lc == del_node)
					/*an o kombos einai aristero paidi tou patera tou kane to NULL */
					parent->lc = NULL;
				else
					parent->rc = NULL;
				
				/* diegrapse ton */
				free (del_node);
				return;
			}
			else if ((del_node->lc == NULL) || (del_node->rc == NULL)){
				/* o kombos exei ena paidi*/

				/*apothikeuoume se mia metablhth to paidi tou kombou*/
				if (del_node->lc != NULL)
					child = del_node->lc;
				else
					child = del_node->rc;

				/*ama o kombos pou theloume na diagrapsoume einai aristero paidi tou patera tou tote bale sth thesh tou to paidi tou*/
				if (parent->lc == del_node)
					parent->lc = child;
				else 
					parent->rc = child;

				
				free(del_node); /*apodesmeuse th mnhmh tou kombou */
				return;

			}
			else{
				/*o kombos exei 2 paidia*/
				
				/*bres ton epomeno kombo sthn endodiatetagmenh*/
				ARTSTYLE * temp_father = NULL; /* o pateras tou epomenou sthn endodiatetagmenh*/
				ARTSTYLE * next = inOrderFindNext(del_node,root, &temp_father);

				ARTSTYLE * child = NULL;
			
					/*tha exei mono ena paidi to else, diaforetika epomenos ths endodiatetagmenhs tha htan to most lc */
					if(next->lc != NULL)
						child = next->lc;
					else
						child = next->rc;

				
				

				/*antegrapse ta stoixeia tou next sto kombo pou theloume na svhsoume */
					del_node->artStyleId =  next->artStyleId;

				/*ftiaxe ton deikth tou patera tou epomenou sthn endodiatetagmenh */
				if (temp_father->lc == next)
					temp_father->lc = child;
				else
					temp_father->rc = child;

				free(next);
				return;
			
	
			}

		}

		parent = current;
		if (styleId	 < current->artStyleId){
			current = current->lc;
		}
		else
			current = current->rc;

	}

}


ARTSTYLE * artStyleLookUp(int styleId, ARTSTYLE * styleList, ARTSTYLE * guard){
	ARTSTYLE * tmp = styleList;

	while (tmp!=NULL){
	
		if (tmp->artStyleId == styleId){
			return tmp;
		}
		if (styleId > tmp->artStyleId)
			tmp = tmp->rc;
		else
			tmp = tmp->lc;
	
	}

	return NULL;

}




static void visit_print(ARTSTYLE * styleList){
	ARTSTYLE * tmp = styleList;

	ARTSTYLE * left = tmp->lc;
	ARTSTYLE * right = tmp->rc;

	if (left == NULL && right == NULL){
		printf("\t%d %s 0 0\n", tmp->artStyleId, tmp->styleName);
	}else if (left != NULL && right == NULL){
		printf("\t%d %s %d 0\n", tmp->artStyleId, tmp->styleName,  tmp->lc->artStyleId);
	}
	else if(right!= NULL && left == NULL){
		printf("\t%d %s 0 %d\n", tmp->artStyleId, tmp->styleName, tmp->rc->artStyleId);
	}else{
		printf("\t%d %s %d %d\n", tmp->artStyleId, tmp->styleName,  tmp->lc->artStyleId, tmp->rc->artStyleId);
	}
	
}

void artStylesPrint(ARTSTYLE * styleList, ARTSTYLE * guard){
	if (styleList == NULL) return;
	
	artStylesPrint(styleList->lc, guard);
	visit_print(styleList);
	artStylesPrint(styleList->rc, guard);
	
}