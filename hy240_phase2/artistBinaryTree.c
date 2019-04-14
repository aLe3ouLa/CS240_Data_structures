
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "artistBinaryTree.h"

void artistTreeInsert (int artistId, char * artistName, int yearOfBirth, int yearOfDeath,int styleId, ARTSTYLE * styleTree, ARTSTYLE * guardNode, ARTIST ** artistList){
	ARTIST * tmp = *artistList;
	ARTIST * newArtist = NULL, * parent = NULL;
	ARTIST * found = NULL;

	if (tmp == NULL){
		newArtist = (ARTIST *) malloc (sizeof(ARTIST));

		newArtist->artistId = artistId;
		strcpy(newArtist->artistName, artistName);
		newArtist->yearOfBirth = yearOfBirth;
		newArtist->yearOfDeath = yearOfDeath;
		newArtist->lc = NULL;
		newArtist->rc = NULL;
		newArtist->artStylePtr = artStyleLookUp(styleId, styleTree, guardNode);
		*artistList = newArtist;
		return;
	}

	while (tmp != NULL ){
		
		if (tmp->artistId == artistId) return;
		parent = tmp;
		if (tmp->artistId > artistId)
			tmp = tmp->lc;
		else 
			tmp = tmp->rc;
	
	}

	newArtist = (ARTIST *)malloc (sizeof(ARTIST));

		newArtist->artistId = artistId;
		strcpy(newArtist->artistName, artistName);
		newArtist->yearOfBirth = yearOfBirth;
		newArtist->yearOfDeath = yearOfDeath;
		newArtist->lc = NULL;
		newArtist->rc = NULL;
		newArtist->artStylePtr = artStyleLookUp(styleId, styleTree, guardNode);

		if (parent != NULL && tmp == NULL){
			if (artistId < parent->artistId){
				parent->lc = newArtist;
				newArtist->lc = NULL;
				newArtist->rc = NULL;
			}
			else{
				parent->rc = newArtist;
				newArtist->lc = NULL;
				newArtist->rc = NULL;
		}
	}

}

static ARTIST * minValue(ARTIST* node, ARTIST ** father) {
  ARTIST * current = node;

  /* loop down to find the leftmost leaf */
  while (current->lc != NULL) {
		*father = current;
		current = current->lc;
  }
  return current;
}


static ARTIST * inOrderFindNext(ARTIST * node, ARTIST* root, ARTIST ** father){
	ARTIST * succ = NULL;
	*father = node;
	if( node->rc != NULL )
        return minValue(node->rc, father);


	return NULL;
}

void artistTreeDelete (int artistId, ARTIST ** artistList){
	ARTIST * child = NULL,  *parent = NULL, *del_node = NULL;
	ARTIST * current = *artistList;
	ARTIST * x = NULL;
	ARTIST * root = *artistList;


	/*Ama den uparxei o kombos mh sunexiseis thn diagrafh*/
	if(artistTreeLookUp(artistId, *artistList)==NULL) return;

		while (current != NULL){

		if (current->artistId == artistId){
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
				ARTIST * temp_father = NULL; /* o pateras tou epomenou sthn endodiatetagmenh*/
				ARTIST * next = inOrderFindNext(del_node,root, &temp_father);

				ARTIST * child = NULL;
			
					/*tha exei mono ena paidi to else, diaforetika epomenos ths endodiatetagmenhs tha htan to most lc */
					if(next->lc != NULL)
						child = next->lc;
					else
						child = next->rc;

				
				

				/*antegrapse ta stoixeia tou next sto kombo pou theloume na svhsoume */
					del_node->artistId =  next->artistId;

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
		if (artistId < current->artistId){
			current = current->lc;
		}
		else
			current = current->rc;

	}

}


ARTIST * artistTreeLookUp(int artistId, ARTIST * artistList){
	ARTIST * tmp = artistList;

	while (tmp!=NULL){
	
		if (tmp->artistId == artistId){
			return tmp;
		}
		if (artistId > tmp->artistId)
			tmp = tmp->rc;
		else
			tmp = tmp->lc;
	
	}

	return NULL;

}




static void visit_print(ARTIST * artistList){
	ARTIST * tmp = artistList;
	ARTIST * left = tmp->lc;
	ARTIST * right = tmp->rc;

	if (left == NULL && right == NULL){
		printf("\t%d %s %d %d %d %s 0 0\n", tmp->artistId, tmp->artistName, tmp->yearOfBirth, tmp->yearOfDeath, tmp->artStylePtr->artStyleId, 
		tmp->artStylePtr->styleName);
	}else if (left != NULL && right == NULL){
		printf("\t%d %s %d %d %d %s %d 0\n", tmp->artistId, tmp->artistName, tmp->yearOfBirth, tmp->yearOfDeath, tmp->artStylePtr->artStyleId, 
			tmp->artStylePtr->styleName, tmp->lc->artistId);
	}
	else if(right!= NULL && left == NULL){
		 printf("\t%d %s %d %d %d %s 0 %d\n", tmp->artistId, tmp->artistName, tmp->yearOfBirth, tmp->yearOfDeath, tmp->artStylePtr->artStyleId, 
			 tmp->artStylePtr->styleName,  tmp->rc->artistId);
	}else{
		printf("\t%d %s %d %d %d %s %d %d\n", tmp->artistId, tmp->artistName, tmp->yearOfBirth, tmp->yearOfDeath, tmp->artStylePtr->artStyleId, 
			tmp->artStylePtr->styleName, tmp->lc->artistId, tmp->rc->artistId);
	}
}

void artistTreePrint(ARTIST * artistList){
	if (artistList == NULL) return;
	
	artistTreePrint(artistList->lc);
	visit_print(artistList);
	artistTreePrint(artistList->rc);
	
}