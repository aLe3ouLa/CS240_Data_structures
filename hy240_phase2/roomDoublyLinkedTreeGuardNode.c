
#include <stdio.h>
#include "roomDoublyLinkedTreeGuardNode.h"

ROOM * guardNode (){
	/* Create Guard node */

	ROOM  *newGuardNode = NULL;
	/* Allocate space for the Guard node */
	newGuardNode = malloc(sizeof(ROOM));
	newGuardNode->roomId = 0;
	newGuardNode->artP = NULL;
	newGuardNode->p = NULL;
	newGuardNode->lc = NULL;
	newGuardNode->rc = NULL;
	return newGuardNode;
}

void roomTreeInsert (int roomId,  ROOM ** roomTree, ROOM * guardNode){

	ROOM * tree = NULL;
	ROOM * prev = NULL;
	ROOM * newRoomNode = NULL;
	
	/* to tree deixnei sthn riza tou dentrou*/
	tree = *roomTree;

	if (tree == NULL && prev == NULL){
		newRoomNode = malloc (sizeof(ROOM));
		newRoomNode->roomId = roomId;
		newRoomNode->artP = NULL;
		newRoomNode->lc = guardNode;
		newRoomNode->rc = guardNode;
		newRoomNode->p = NULL;
		*roomTree = newRoomNode;
		return;
	}
	/*Oso den exoume ftasei ton kombo frouro*/
	while (tree != guardNode){
	
		if (tree->roomId == roomId) {
			return;
		}
		/*krata to prohgoumeno*/
		prev = tree;

		/*ama to kleidi einai mikrotero pigaine sto aristero upodentro, diaforetika sto de3i*/		
		if (roomId < tree->roomId)
			tree = tree->lc;
		else
			tree = tree->rc;

	}

	/*dhmiourgia neou kombou*/
	newRoomNode = malloc (sizeof(ROOM));
	newRoomNode->roomId = roomId;
	newRoomNode->artP = NULL;
	newRoomNode->lc = NULL;
	newRoomNode->rc = NULL;
	
	if (prev != guardNode && tree == guardNode){
		if (roomId <prev->roomId){
			prev->lc = newRoomNode;
			newRoomNode->lc = guardNode;
			newRoomNode->rc = guardNode;
			newRoomNode->p = prev;
		}
		else{
			prev->rc = newRoomNode;
			newRoomNode->lc = guardNode;
			newRoomNode->rc = guardNode;
			newRoomNode->p = prev;
		}
	}
	
		
}

static void visit_print(ROOM * roomList, ROOM * guard){
	ROOM * tmp = roomList;
	ROOM * left = tmp->lc;
	ROOM * right = tmp->rc;

	if (left == guard && right == guard){
		printf("\t\t%d 0 0\n", tmp->roomId);
	}else if (left != guard && right == guard){
		printf("\t\t%d  %d 0\n", tmp->roomId, tmp->lc->roomId);
	}
	else if(right!= guard && left == guard){
		printf("\t\t%d  0 %d\n", tmp->roomId, tmp->rc->roomId);
	}else{
		printf("\t\t%d  %d %d\n", tmp->roomId, tmp->lc->roomId,tmp->rc->roomId);
	}
	
		
}

void roomTreePrint(ROOM * roomList, ROOM * guard){
	

	if (roomList == guard) return;

	roomTreePrint(roomList->lc, guard);
	visit_print(roomList, guard);
	roomTreePrint(roomList->rc, guard);

}


static ROOM * minValue(ROOM* node, ROOM ** father) {
  ROOM * current = node;

  /* loop down to find the leftmost leaf */
  while (current->lc != NULL) {
		*father = current;
		current = current->lc;
  }
  return current;
}

static ROOM * inOrderFindNext(ROOM * node, ROOM * root, ROOM ** father){
		*father = node;
	if( node->rc != NULL )
        return minValue(node->rc, father);
 
	
}


void roomTreeDelete (int roomId, ROOM ** roomList, ROOM * guardNode){

		ROOM * child = NULL,  *parent = NULL, *del_node = NULL;
	ROOM * current = *roomList;
	ROOM * x = NULL;
	ROOM * root = *roomList;


	/*Ama den uparxei o kombos mh sunexiseis thn diagrafh*/
	if(roomTreeLookUp(roomId, *roomList, guardNode)==NULL) return;

	while (current != guardNode){

			if (current->roomId == roomId){
			del_node = current;

			if (del_node->lc == guardNode && del_node->rc == guardNode){
				/* o kombos den exei paidia */


				if (parent == guardNode){
					*roomList = guardNode;
					del_node = guardNode;
					return;
				}

				if (parent->lc == del_node)
					/*an o kombos einai aristero paidi tou patera tou kane to NULL */
						parent->lc = guardNode;
				else
					parent->rc = guardNode;
				
				/* diegrapse ton */
				free (del_node);
				return;
			}
			else if ((del_node->lc == guardNode) || (del_node->rc == guardNode)){
				/* o kombos exei ena paidi*/

				/*apothikeuoume se mia metablhth to paidi tou kombou*/
				if (del_node->lc != guardNode)
					child = del_node->lc;
				else
					child = del_node->rc;

				/*ama o kombos pou theloume na diagrapsoume einai aristero paidi tou patera tou tote bale sth thesh tou to paidi tou*/
				if (parent == guardNode){
					//free(del_node); /*apodesmeuse th mnhmh tou kombou */
					del_node = child;
					*roomList = child;
					
					return;
				}
				else if (parent->lc == del_node)
					parent->lc = child;
				else 
					parent->rc = child;

				
				free(del_node); /*apodesmeuse th mnhmh tou kombou */
				return;

			}
			else{
				/*o kombos exei 2 paidia*/
				
				/*bres ton epomeno kombo sthn endodiatetagmenh*/
				ROOM * temp_father = NULL; /* o pateras tou epomenou sthn endodiatetagmenh*/
				ROOM * next = inOrderFindNext(del_node,root, &temp_father);

				ROOM * child = NULL;
			
					/*tha exei mono ena paidi to else, diaforetika epomenos ths endodiatetagmenhs tha htan to most lc */
				if(next->lc != guardNode)
						child = next->lc;
					else
						child = next->rc;

				/*antegrapse ta stoixeia tou next sto kombo pou theloume na svhsoume */
					del_node->roomId =  next->roomId;

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
		if (roomId < current->roomId){
			current = current->lc;
		}
		else
			current = current->rc;

	}

}

void roomRemoveAll (ROOM *roomTree, ROOM * guardNode){

	if( roomTree == guardNode )
        return;
	if( roomTree->lc != guardNode )
		roomRemoveAll( roomTree->lc, guardNode );
    if( roomTree->rc != NULL )
		roomRemoveAll( roomTree->rc,guardNode );
     
   free(roomTree);
    
   return;

}


ROOM * roomTreeLookUp(int roomId, ROOM * roomList, ROOM * guardNode){

	ROOM * tmp = roomList;
	while (tmp != guardNode){
		/* ama breis to stoixeio epestrepse to */
		
		if (roomId == tmp->roomId){
			return tmp;
		}	
		
		/*ama einai megalutero apo to roomId tou tmp, pigaine sto de3i paidi tou tmp diaforetika sto aristero */
		if (roomId > tmp->roomId)
			tmp = tmp->rc;
		else
			tmp = tmp->lc;
	}

	/* ama de to breis epestrepse Null */
	return NULL;
}